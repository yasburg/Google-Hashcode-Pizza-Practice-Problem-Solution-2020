#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct Result {
	vector<int> indexes;
	int sum;
};

//returns index of found number - return -1 if cannot find.
int findUpper(vector<int>& vec, int num) {
	for (int i = vec.size() - 1; i >= 0; i--) {
		if (vec[i] <= num) {
			return i;
		}
	}
	return -1; //if we can not find it;
}

//returns index of a place where before of that point the sum of all numbers are smaller than the given number k
//return -2 if cannot find it
int findLower(vector<int>& vec, int num) {
	int sum = 0;
	for (int i = 0; i < vec.size(); i++) {
		sum += vec[i];
		if (sum > num) {
			return i;
		}
	}
	return -2;
}

void recursiveSearch(vector<int> vec, Result& lastOrder, int target, int globalTarget) {

	if (vec.size() != 0 && lastOrder.sum != globalTarget) {
		int upperIndex = findUpper(vec, target);
		if (upperIndex != -1) {
		int currentVal = vec[upperIndex];
		lastOrder.sum += currentVal;
		lastOrder.indexes.push_back(upperIndex);
		vec.resize(lastOrder.indexes.back());
		recursiveSearch(vec, lastOrder, target - currentVal, globalTarget);
		}
	}
}

vector<int> whatToOrder(vector<int> vec, int target, int typeCount) {

	int upperIndex = findUpper(vec, target);
	int lowerIndex = findLower(vec, target);

	vector<int> resultingIndexes;

	Result result;
	result.indexes = resultingIndexes;
	result.sum = 0;

	if (upperIndex == -1) {
		cout << "Problem with upperIndex";
		return resultingIndexes;
	}
	if (lowerIndex == -2) {
		cout << "Might have problem with lowerIndex";
		for (int i = 0; i < vec.size(); i++) {
			resultingIndexes.push_back(i);
		}
		return resultingIndexes;
	}

	for (int i = upperIndex; lowerIndex <= i; i--) {
		vector<int> tempResultingIndexes;
		Result tempResult;
		tempResult.indexes = tempResultingIndexes;
		tempResult.sum = 0;
		vec.resize(i+1);
		recursiveSearch(vec, tempResult, target, target);

		if (tempResult.sum > result.sum) {
            result.indexes.resize(0);
			for(int x : tempResult.indexes){
                result.indexes.push_back(x);
            }
			result.sum = tempResult.sum;
		}
	}

	return result.indexes;
}

int main() {
    vector<string> fileList{ "a_example", "b_small", "c_medium", "d_quite_big", "e_also_big" };
	for (string file : fileList) {
        ifstream myInputFile;
        string fileName = "C:\\Users\\yasin\\Desktop\\Hash Code Practice\\Input\\" + file + ".in";
        myInputFile.open(fileName);

        if (myInputFile.is_open()) {
            vector<int> allPizzas;
            string line;
            int target, typeCount, pizzaNum;

            myInputFile >> target >> typeCount;
            for (int i = 0; i < typeCount; i++) {
                myInputFile >> pizzaNum;
                allPizzas.push_back(pizzaNum);
            }
            myInputFile.close();

            ofstream myOutputFile;
            string outFileName = "C:\\Users\\yasin\\Desktop\\Hash Code Practice\\Output\\" + file + ".txt";
            myOutputFile.open(outFileName, ofstream::trunc);
            if (myOutputFile.is_open()) {
                vector<int> result = whatToOrder(allPizzas, target, typeCount);
                myOutputFile << result.size() << endl;
                cout << endl << "\nFile name: " << fileName;
                cout << endl << "The resulting vector size: " << result.size() << endl;
                int sum = 0;
                cout << "Indexes in file: ";
                for (int x : result) {
                    cout << x << " ";
                    sum += allPizzas[x];
                }
                cout << "\nTarget: " << target << " - Reached: " << sum;
                for (int x : result) {
                    myOutputFile << x << " ";
                }
                myOutputFile.close();
            }
            else {
                cout << "Cannot open the file: " + outFileName;
            }
        }
        else {
            cout << "Cannot open the file: " + fileName;
        }
    }
	return 0;
}
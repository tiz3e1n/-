#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

// Функція для розбиття рядку на числа та операції
void tokenize(const string& str, vector<int>& numbers, vector<char>& operations) {
    istringstream iss(str);
    int num;
    char op;

    while (iss >> num) {
        numbers.push_back(num);
        if (iss >> op) {
            operations.push_back(op);
        }
    }
}

// Функція для обчислення суми чисел у масиві
int calculateSum(const vector<int>& numbers) {
    int sum = 0;
    for (int num : numbers) {
        sum += num;
    }
    return sum;
}

// Функція для вставлення операцій додавання для виправлення рівняння
string insertAdditionOperations(const string& equation) {
    size_t equalPos = equation.find('=');
    string leftPart = equation.substr(0, equalPos);
    string rightPart = equation.substr(equalPos + 1);

    vector<int> numbers;
    vector<char> operations;

    tokenize(leftPart, numbers, operations);

    int targetSum = calculateSum(numbers);

    string resultEquation;

    for (size_t i = 0; i < numbers.size(); ++i) {
        resultEquation += to_string(numbers[i]);
        if (i < operations.size()) {
            resultEquation += operations[i];
        }

        // Вставляємо операції додавання між числами
        if (i < numbers.size() - 1) {
            int diff = targetSum - calculateSum(vector<int>(numbers.begin(), numbers.begin() + i + 1));
            resultEquation += " + " + to_string(diff);
        }
    }

    resultEquation += " = " + to_string(targetSum);

    return resultEquation;
}

int main() {
    string inputEquation;
    cout << "Введіть рівняння s=a (де s та a - різні числа): ";
    getline(cin, inputEquation);

    string resultEquation = insertAdditionOperations(inputEquation);

    cout << "Виправлене рівняння: " << resultEquation << endl;

    return 0;
}

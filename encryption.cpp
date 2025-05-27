#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string Vigenereencrypt(string plaintext, string key);
string Vigeneredecrypt(string encryptext, string key);
void encryptFile(string inputFileName, string outputFileName, string key);
void decryptFile(string inputFileName, string outputFileName, string key);
bool isAlphabetical(const string str);


bool isAlphabetical(const string str) {
    for (char c : str) {
        if (!isalpha(c)) {
            return false; // if not alphebetical
        }
    }
    return true;
}

int main() {
    int choice;
    string inputFile, outputFile, key;

    cout << "1. Encrypt a file\n";
    cout << "2. Decrypt a file\n";
    cout << "Enter your choice: ";
    cin >> choice;

    cout << "Enter the input file name: ";
    cin >> inputFile;
    cout << "Enter the output file name: ";
    cin >> outputFile;

    while (true) {
        cout << "Enter the encryption/decryption key (alphabetical only): ";
        cin >> key;

        if (isAlphabetical(key)) {
            break;
        } else {
            cout << "Invalid response, should be alphebetical.\n";
        }
    } // had to make sure it's alphabetical, will not encrypt numbers

    if (choice == 1) {
        encryptFile(inputFile, outputFile, key);
    } else if (choice == 2) {
        decryptFile(inputFile, outputFile, key);
    } else {
        cout << "Invalid choice.\n";
    }

    return 0;
}

string Vigenereencrypt(string plaintext, string key) {

    string ciphertext = "";
    int keyin = 0;

    // loops over each char in my plaintext
    for (char c : plaintext) {
        // checks if my char is a letter
        if (isalpha(c)) {
            // find if letter is upper or lower case
            char offset = isupper(c) ? 'A' : 'a';
            // converts plaintext char to uppercase and finds its corresponding key letter
            // then makes sure the key repeats, converting both plaintext and key characters into 
            // its placement on the alphabet and verifying that it's within the 26 letters then
            // converting it back into a character
            // homie came in clutch ngl
            ciphertext += char(((toupper(c) - 'A') + (toupper(key[keyin % key.length()]) - 'A')) % 26 + offset);
            keyin++;
        } else {
            ciphertext += c; // if not alphabetical then appended w/o change
        }
    }

    return ciphertext;
}

string Vigeneredecrypt(string encryptext, string key) {
    string decrypted = "";
    int keyin = 0;

    // same loop but goes over encrypted text
    for (char c : encryptext) {
        // check if char is letter
        if (isalpha(c)) {
            //determines upper/lowercase
            char offset = isupper(c) ? 'A' : 'a';
            // converts encrypted char to uppercase, matches it with key char that gets converted
            // to uppercase, reverses the shift by taking decrypted position of char by subtracting 
            // key char from encrypted char position, adds 26 in case we get a negative position, and 
            // ensures that everything is within the alphabet position.
            // encryption process took 3-4hours to create, the decryption took like 30 minutes
            decrypted += char((toupper(c) - 'A' - (toupper(key[keyin % key.length()]) - 'A') + 26) % 26 + offset);
            keyin++;
        } else {
            decrypted += c; //does not decrypt non-letter characters
        }
    }

    return decrypted;
}

void encryptFile(string inputFileName, string outputFileName, string key) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    string line;

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error opening file!\n";
        return;
    }

    if (inputFile.peek() == ifstream::traits_type::eof()) {
        cout << "Error: The input file is empty.\n";
        return;
}

    while (getline(inputFile, line)) {
        outputFile << Vigenereencrypt(line, key) << "\n";
    }

    inputFile.close();
    outputFile.close();
}

void decryptFile(string inputFileName, string outputFileName, string key) {
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    string line;

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error opening file!\n";
        return;
    }
    
    if (inputFile.peek() == ifstream::traits_type::eof()) {
    cerr << "Error: The input file is empty.\n";
    return;
    
    }
    while (getline(inputFile, line)) {
        outputFile << Vigeneredecrypt(line, key) << "\n";
    }

    inputFile.close();
    outputFile.close();
}
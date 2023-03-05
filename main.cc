/*  Project 3 | Typing Tutor by Irvin Ortiz
    Professor Hayes 9am Class */

/* Sorry for lack of edit history. I can't code everything on replit due to internet issues, but I need help knowing how to operate VS Code Git/Github stuff. Will probably reach out during class next week */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
using namespace std;

const int NMISP = 5;
const int RNG_RANGE = 100;

void display_header(const int ndict, const int nmiss)
{
    /* TODO: Print out the header, you can see an example of it
    in the write-up. Refer to Section "At Program Start".

    Parameters:
        int ndict -> the number of words in the full dictionary
        int nmiss -> the number of word pairs in the misspelled
                     dataset.
    */
    cout << "*** Typing Tutor" << endl;
    cout << "There are " << ndict << " words in the dictionary." << endl;
    cout << "There are " << nmiss << " commonly misspelled words." << endl;
}

void display_menu_options()
{
    /* This function prints out all the menu options, it is
    given to you as part of the starter code. If you change
    it,  you run the  risk of failing  an early test of the
    autograder.*/

    cout << endl
         << "*** Select a menu option:" << endl
         << "1. Spell commonly misspelled words" << endl
         << "2. Type random words from the full dictionary" << endl
         << "3. Display some words from one of the lists" << endl
         << "4. Use binary search to lookup a word in the dictionary" << endl
         << "5. Exit the program." << endl
         << "Your choice: ";
}

vector<int>
randn(const int n, const int max)
{
    /*  TODO: Create and return a vector that has n random numbers drawn
    from  between 0 and the value of the parameter max. This function is
    relevant to many sections, and is needed any time random numbers are
    needed. Check the example file rng.cc for hints.

    Parameters:
        int n -> the number of random numbers to generate
        int max -> the maximum random number, random numbers are drawn
                    from between [0, max]

    Returns:
        a vector that contains n random numbers between [0, max]
    */

    // placeholder statements so code compiles you can delete these
    vector<int> randVector;
    for (int i = 0; i < n; i++)
    {
        randVector.push_back(rand() % (max + 1));
    }
    return randVector;
    return randVector;
}

ifstream
open(const string &src_file)
{
    ifstream src{src_file};
    if (!src.is_open())
    {
        cout << "Could not find file " << src_file << "." << endl;
        exit(1);
    }
    return src;
}

void extract_dict(vector<string> &dst, const string &src_file)
{
    /* TODO: Read the data from the file, the file name is src_file,
    and store each line in the vector dst.

    Parameters:
        dst -> an empty vector (of strings), passed by reference,
               that  you  will  store  every line  of the file in
               (each line is one element in the file).

        src_file -> a string, passed by reference, that you are not
                    allowed to change  (const),  that is simply the
                    name of the file.
    Hints:
        Use the function (defined in this file) called open.
    */

    // string of dictionary pulled from file
    string plusWord;

    ifstream dictFile = open(src_file); // open file

    while (getline(dictFile, plusWord))
    {
        // push_back words into plusWord vector
        dst.push_back(plusWord);
    }
}

void extract_misspelled(vector<string> &misspelled, vector<string> &correct,
                        const string &src_file)
{
    /* TODO: Extract the word pairs (misspelled, correct) from the file
    and store them in their respective vectors.

    Parameters:
        misspelled -> an  empty vector (strings),  passed by reference,
                      that you will store the misspelled words in.

        correct -> an empty vector (strings), passed by reference, that
                   you will store the correct version of the words in.

        src_file -> a string, passed by reference, that you are not
                    allowed to change  (const),  that is simply the
                    name of the file.
    Hints:
        This function is very similar to extract_dict. Instead of simply
        storing the contents of the whole line as an element in dst, you
        have to process  the line into a misspelled word and the correct
        version. Each of those will be stored into separate vectors.  So
        you  should have  misspelled[i]  =  the ith misspelled  word and
        correct[i] = the ith correct word.
    */
    ifstream missFile;
    missFile.open(src_file);

    // misspelled words from file
    string addMiss;

    while (getline(missFile, addMiss))
    {
        stringstream line(addMiss);
        string wordCheck;
        // check if string is spaced, then store into vector
        getline(line, wordCheck, ' ');
        misspelled.push_back(wordCheck);
        getline(line, wordCheck, ' ');
        correct.push_back(wordCheck);
    }
}

void display_elems(const vector<string> &src, const vector<int> &positions)
{
    /* TODO: With the vector of indices (position), print out the elements
    in the vector src only at those indices,  with a space between each of
    the elements.  Don't print a space after the last element. See Section
    "Menu Option 1: Spelling Misspelled"

    Parameters:
        src -> a vector (strings), passed by reference, that is not
               allowed to be modified (const), which holds the data
               that is to be printed

        positions -> a vector (int), passed by reference, that is not
                     allowed to be modified (const),  which holds the
                     indices for elements in src to print.
    */
    // for loop to print out all elements in each position
    for (int i = 0; i < positions.size() - 1; i++)
    {
        cout << src[positions[i]] << " ";
    }
    // quick way to print last element with no space
    cout << src[positions[positions.size() - 1]];
}

void extract_spelling_answers(vector<string> &dst, const vector<string> &correct,
                              const vector<int> positions)
{
    /* TODO: Copy the elements at the indices, in the positions vector,
    from the correct vector, into the vector dst. See Section "Menu Op-
    tion 1: Spelling Misspelled".

    Parameters:
        dst -> an empty vector (of strings), passed by reference, that
               you will copy the specific elements from correct into.

        correct -> a vector (strings), passed by reference, that is not
                   allowed to be modified (const), which holds the data
                   that is to be copied over to dst

        positions -> a vector (int), passed by reference, that is not
                     allowed to be modified (const),  which holds the
                     indices of the elements in correct to copy over

    Hints:
        This is very similar to display_elems, except you are not printing
        out the elements but instead copying them over to dst.
    */

    /* Thanks for hint, literally just copy-pasted that over to here and chopped
       off the uneccessary parts */

    for (int i = 0; i < positions.size(); i++)
    {
        dst.push_back(correct[positions[i]]);
    }
}

void extract_spelling_mistakes(vector<string> &dst, const string &to_grade,
                               const vector<string> &correct)
{
    /* TODO: Populate the vector dst with all the spelling errors in the
    user's answer (to_grade).  See Section "Menu Option 1: Spelling Mis-
    spelled"

    Parameters:
        dst -> an empty vector (of strings), passed by reference, that you
        will fill with strings that represent spelling errors  (mispelling
        -> correct spelling) (see Hints)

        to_grade -> a string, passed  by reference,  that is not allowed to
                    be modified (const) that holds the user's typed answer.

        correct -> a vector (strings), passed by reference, that is not
                   allowed to be modified (const), which holds the correct
                   answers. (one vector element -> one word)

    Hints:
        First you need to extract the answer, the user gave, for each word.
        Once you have those, you can compare it with the associated correct
        answer  (answer ?= correct[i] for the ith word).  You then populate
        the vector dst with a string that described the error. For example,
        if the word is  "hello" and  the user types  "jello" then the error
        will be "jello -> hello".
    */

    // user inputs into vector userAnswers
    vector<string> userAnswers;

    // check for spaces, then seperate
    string tempString = "";
    for (int i = 0; i < to_grade.size(); i++)
    {
        if (to_grade[i] == ' ')
        {
            userAnswers.push_back(tempString);
            tempString.clear();
            continue;
        }
        tempString.push_back(to_grade[i]);
    }
    userAnswers.push_back(tempString);

    // extract userAnswers and check against correct, then add to dst
    for (int i = 0; i < userAnswers.size(); i++)
    {
        if (userAnswers[i] != correct[i])
        {
            dst.push_back(userAnswers[i] + " -> " + correct[i]);
        }
    }
}

void report_misspell_mistakes(const vector<string> &mistakes,
                              const int num_words)
{
    /*  TODO: Print out the spelling mistakes to the user. Following
    the format from the write-up. See Section "Menu Option 1: Spell-
    ing Misspelled".

    Parameters:
        mistakes -> a vector (strings), passed by reference, that is
                    not allowed  to be modified  (const),  and holds
                    the messages about  misspellings that we want to
                    report to the user.

        num_words -> an integer, that is not allowed to be modified
                     (const),  which is  the total number  of words
                     being tested
    */

    if (mistakes.size() != 0)
    {
        cout << "Misspelled words:" << endl;

        for (int i = 0; i < mistakes.size(); i++)
        {
            cout << "    " << mistakes[i] << endl;
        }
    }
    else if (mistakes.size() == 0)
    {
        cout << "No misspelled words!" << endl;
    }

    // Initialized two variables to tally correct and incorrect spelling

    int numCorrect;
    int numIncorrect;

    // assign the ammount of correct and incorrect spellings to the variables

    numIncorrect = mistakes.size();
    numCorrect = num_words - numIncorrect;

    // calculate the points for the user inputs: 3 points for correct spelling and -6 for incorrect spelling
    int score = (numCorrect * 3) - (numIncorrect * 6);

    // print out the scores with appropriate format
    cout << numCorrect * 3 << " points: " << numCorrect << " spelled correctly x 3 points for each." << endl;
    cout << numIncorrect * 6 << " point penalty: " << numIncorrect << " spelled incorrectly x -6 points for each." << endl;
    cout << "Score: " << score << endl;
}

void evaluate_user_misspells(const vector<string> &src, const vector<int> &positions)
{
    /*TODO: Read the users input for the typing test, and report
    back their performance. See Section "Menu Option 1: Spelling
    Misspelled".

    Parameters:
        src -> a vector (strings), passed by reference, that is not
               allowed to be modified (const), which holds the data
               that the user is being tested on.

        positions -> a vector (int), passed by reference, that is not
                     allowed to be modified (const),  which holds the
                     indices of the elements in correct to copy over

    Hints:
        Using getline to read in  the entire sequence might be a
        good idea. This function  should be easier to  write, if
        you have already completed the functions for calculating
        and  reporting  spelling mistakes.  Call those functions
        instead of duplicating the work.
    */

    vector<string> answers;
    vector<string> mistakes;

    string input;
    getline(cin, input);

    extract_spelling_answers(answers, src, positions);

    extract_spelling_mistakes(mistakes, input, answers);

    report_misspell_mistakes(mistakes, NMISP);
}

void misspelled(const vector<string> &mspelled, const vector<string> &correct)
{
    /*  TODO: Print out the starting message for option 1, display 5 random
    words from the dictionary, finally evaluate the user's input. See "Menu
    Option 1: Spelling Misspelled".

    Parameters:
        mspelled -> a vector (string) where each element is one
                    mispelled word from the data set

        correct -> a vector (string) where each element is a
                   correctly spelled word from the data set

    Hints:
        Do not try to write this function first.  The role of this function
        is to simply drive the whole procedure for menu option 1, it should
        be calling helper functions to handle the details of the sub tasks.
        Use randn, display_elems, and evaluate_user_misspells.
    */
    vector<int> position;
    position = randn(5, mspelled.size() - 1);

    cout << endl;
    cout << "*** Using commonly misspelled words." << endl;
    display_elems(mspelled, position);
    cout << endl;
    cout << "Type the words above with the correct spelling:" << endl;
    evaluate_user_misspells(correct, position);
}

void full_dict(const vector<string> &dict)
{
    /* TODO: Print out starting message for menu option 2, display five random
    words from the full dictionary, then evaluate the user's input. See Section
    "Menu Option 2: Typing From Dictionary"

    Parameters:
        dict -> a vector (string), passed by reference, where
                each element is one word from the full
                dictionary.

    Hints:
        Do not start by writing this function. It's role is to simply drive
        the whole procedure for menu option 2,  it should be calling helper
        functions to  handle the details  of the task.  You should be using
        randn, display_elems, and evaluate_user_misspells.
    */

    vector<int> position;

    position = randn(5, dict.size() - 1);
    cout << endl;
    cout << "*** Using full dictionary." << endl;
    display_elems(dict, position);
    cout << endl;
    cout << "Correctly type the words above:" << endl;
    evaluate_user_misspells(dict, position);
}

void display_words_prompt()
{
    // This displays the data set choices for menu option 3
    cout << endl
         << "*** Displaying word list entries." << endl
         << "Which words do you want to display?" << endl
         << "A. Dictionary of all words" << endl
         << "B. Commonly misspelled words (wrongly spelled)" << endl
         << "C. Commonly misspelled words (correctly spelled)" << endl
         << "Your choice: ";
}

void print_range(const vector<string> &data)
{
    /* TODO:  Display the starting  message for menu option 3,  read the
    users chosen range, verify that the indices are in range, then print
    out the  words in the index range.  See Section "Menu Option 3: Word
    Range"

    Parameters:
        data -> a vector (string),  passed by reference, that cannot be
                modified (const), which holds the all the data (and the
                user will print some of it in a range)

        Hints:
            You can determine the range of the data by checking the size
            of the vector. You need to make sure the  range is valid for
            the given dataset  (think about what  values  the user could
            give that would be invalid). Check the write-up to make sure
            you are printing the data in the expected format.
    */

    cout << "*** Enter the start and end indices between 0 and " << int(data.size() - 1) << ": ";

    // Initialize the start and end indices
    int starterPos;
    int finalPos;

    cin >> starterPos;
    cin >> finalPos;

    // Error case for if the start and end indices are out of range
    if (starterPos < 0 || starterPos > data.size() || finalPos < 0 || finalPos > data.size() || starterPos > finalPos)
    {
        cout << "The end index must come after the start, and the indices must be in range." << endl;
    }

    // else statement outputs number + word formatted
    else
    {
        for (int i = starterPos; i <= finalPos; i++)
        {
            cout << i << ". " << data[i] << endl;
        }
    }
}

void display_in_range(const vector<string> &dict, const vector<string> &mspelled,
                      const vector<string> &correct)
{
    /* TODO: Display the initial messages for menu option 3, read in
    the user's choice of dataset, and display the data in range. See
    Section "Menu Option 3: Word Range"

    Parameters:
        dict -> a vector (string),  passed by reference, that cannot be
                modified (const), which holds the all the data from the
                full dictionary

        mspelled -> a vector (string), passed by reference, that cannot
                    be modified (const),  which holds the all the miss-
                    pelled words

        correct -> a vector (string), passed by reference, that cannot
                   be modified (const),  which holds the all the words
                   with correct spelling

    Hints:
        First write  the function print_range, which will print data in a
        range (in general). This function should call print_range, but it
        will read in the user's  choice of data set and  call print_range
        with the user's choice.
    */
    display_words_prompt();

    // Initialize input character
    char inputLetter;

    // Take input from the user
    cin >> inputLetter;
    // Branch statement for user input and output data. Wanted to do a switch case, but got lazy
    if (inputLetter == 'A' || inputLetter == 'a')
    {
        print_range(dict);
    }
    else if (inputLetter == 'B' || inputLetter == 'b')
    {
        print_range(mspelled);
    }
    else if (inputLetter == 'C' || inputLetter == 'c')
    {
        print_range(correct);
    }
}

void bsearch(const vector<string> &data)
{
    /* TODO:  Read in the word to search for, from the user, and run the
    Binary Search Algorithm to search for the word. At every step of the
    algorithm,  print out the current word,  that is being compared with
    the target.

    Parameters:
        data -> a vector (string),  passed by reference, that cannot be
                modified (const), which holds the all the data from the
                full dictionary
    Hints:
        See our sample code to learn how the binary search algorithm works.
        Remember to  output the text in the same  format as you  see in the
        write-up.
    */
    // Initialize string to store search target, take input from the user
    string findTarget;
    cin >> findTarget;
    cout << "*** Enter word to search: ";

    // Created various variables for the search.
    int searchStart = 0;
    int searchMiddle;
    int searchEnd = data.size();
    string elem;
    int i = 0;

    do
    {
        searchMiddle = (searchStart + searchEnd) / 2;
        elem = data[searchMiddle];
        i++;

        // If else error checks for when out of target range
        if (elem < findTarget)
        {
            cout << setw(5);
            cout << i << ". Comparing to: " << elem << endl;
            searchStart = searchMiddle + 1;
        }

        else if (elem > findTarget)
        {
            cout << setw(5);
            cout << i << ". Comparing to: " << elem << endl;
            searchEnd = searchMiddle;
        }

        // Else case for where target is found
        else
        {
            cout << setw(5);
            cout << i << ". Comparing to: " << elem << endl;
            cout << elem << " was found." << endl;
            return;
        }
        // Erorr case for when target is not found
    } while (searchStart < searchEnd);
    cout << findTarget << " was NOT found." << endl;
}

void extract_all_data(vector<string> &dict, vector<string> &mspelled,
                      vector<string> &correct)
{
    extract_dict(dict, "dictionary.txt");
    extract_misspelled(mspelled, correct, "misspelled.txt");
}

int main()
{
    srand(1);
    vector<string> dict, mspelled, correct;
    extract_all_data(dict, mspelled, correct);
    display_header(dict.size(), correct.size());
    unsigned int choice;
    do
    {
        display_menu_options();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choice)
        {
        case 1:
            misspelled(mspelled, correct);
            break;
        case 2:
            full_dict(dict);
            break;
        case 3:
            display_in_range(dict, mspelled, correct);
            break;
        case 4:
            bsearch(dict);
            break;
        case 5:
            cout << "Exiting." << endl;
            break;
        default:
            cout << "No menu option " << choice << ". "
                 << "Please try again." << endl;
        }
    } while ((choice != 5) && !cin.eof());

    return 0;
}
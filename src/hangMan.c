/*
 ============================================================================
 Name        : learning.c
 Author      : ShyniFella
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : HangMan game
 ============================================================================
 */

#ifdef _WIN32
#include <windows.h>
#define SLEEP(milliseconds) Sleep(milliseconds)
#else
#include <unistd.h>
#define SLEEP(seconds) sleep(seconds)
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

void help(void);
void gameStart(const char *aiWord);

int main(void) {
    const char *aiWordArr[] = {
    		"apple", "banana", "orange", "grape", "kiwi", "melon", "peach", "pear", "plum", "berry",
    		"cat", "dog", "bird", "fish", "horse", "cow", "pig", "sheep", "chicken", "duck",
    		"red", "blue", "green", "yellow", "purple", "black", "white", "gray", "brown", "pink",
    		"one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten",
    		"sun", "moon", "star", "cloud", "rain", "snow", "wind", "tree", "flower", "grass",
    		"book", "pen", "paper", "desk", "chair", "table", "door", "window", "house", "room",
    		"car", "bus", "train", "plane", "boat", "ship", "bike", "road", "street", "city",
    		"happy", "sad", "angry", "tired", "excited", "bored", "hungry", "thirsty", "sleepy", "funny",
    		"big", "small", "tall", "short", "fast", "slow", "old", "new", "good", "bad",
    		"hot", "cold", "warm", "cool", "light", "dark", "loud", "quiet", "soft", "hard",
    		"yes", "no", "maybe", "please", "thank", "hello", "goodbye", "sorry", "excuse", "welcome",
    		"time", "day", "week", "month", "year", "hour", "minute", "second", "today", "tomorrow",
    		"water", "food", "fire", "earth", "air", "sky", "sea", "land", "mountain", "river",
    		"music", "art", "dance", "game", "movie", "sport", "science", "history", "math", "english",
    		"love", "hate", "fear", "joy", "hope", "dream", "life", "death", "world", "people",
    		"country", "state", "city", "town", "village", "school", "work", "home", "family", "friend",
    		"body", "head", "eye", "ear", "nose", "mouth", "hand", "foot", "leg", "arm",
    		"think", "know", "see", "hear", "feel", "say", "do", "go", "come", "take",
    		"make", "use", "find", "give", "get", "put", "keep", "let", "begin", "end",
    		"write", "read", "learn", "teach", "study", "work", "play", "eat", "drink", "sleep"
    };

    int numWords = sizeof(aiWordArr) / sizeof(aiWordArr[0]);

    srand(time(NULL));

    int randomIndex = rand() % numWords;
    const char *aiWord = aiWordArr[randomIndex];

    puts("Hello, fellow user. You may play the famous 'HangMan' game :3");
    puts("If you do not know the rules, I may teach you them!");

    puts("Type 'help' if you need help remembering the rules.");

    char uInput[100]; // Use a buffer to read input
    scanf("%99s", uInput); // Limit input to prevent buffer overflows

    if (strcmp(uInput, "help") == 0) {
        help();

    }

    puts("Type 'start' to start the game");
    scanf("%99s", uInput);

    if (strcmp(uInput, "start") == 0) {
        gameStart(aiWord);

    }

    return 0;
}

void help(void) {
    puts("HangMan Rules:");
    puts("Guess letters to reveal a hidden word.");
    puts("You have a limited number of incorrect guesses.");
}

void gameStart(const char *aiWord) {
    int wordLength = strlen(aiWord);
    char guessedLetters[26] = {0}; // Keep track of guessed letters
    int incorrectGuesses = 0;
    char displayWord[100]; // To display the partially revealed word
    for (int i = 0; i < wordLength; i++) {
        displayWord[i] = '_';
    }
    displayWord[wordLength] = '\0';

    printf("I've chosen a word. It has %d letters.\n", wordLength);

    while (incorrectGuesses < 11) {
        printf("Word: %s\n", displayWord);
        printf("Guesses left: %d\n", 11 - incorrectGuesses);
        printf("Enter your guess: ");

        char guess[2];

        scanf("%1s", guess); // Read only one character

        char lowerGuess = tolower(guess[0]);

        if (strchr(guessedLetters, lowerGuess) != NULL) {
            printf("You already guessed that letter.\n");
            continue;

        }

        guessedLetters[strlen(guessedLetters)] = lowerGuess;

        bool correctGuess = false;

        for (int i = 0; i < wordLength; i++) {
            if (tolower(aiWord[i]) == lowerGuess) {
                displayWord[i] = aiWord[i];
                correctGuess = true;

            }
        }

        if (strcmp(displayWord, aiWord) == 0) {
            printf("Congratulations! You guessed the word: %s\n", aiWord);
            SLEEP(10000);
            return;

        }

        if (!correctGuess) {
            incorrectGuesses++;
            printf("Incorrect guess.\n");

        }
    }

    printf("You ran out of guesses. The word was: %s\n", aiWord);
    SLEEP(10000);

}

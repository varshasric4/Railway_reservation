#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
struct User {
    char username[50];
    char password[50];
};
struct User current_user;
#define MAX_USERS 10
struct User users[MAX_USERS];
int userCount = 0; 
struct Train {
    char train_name[100];
    int available_seats[2];
    float ticket_price[2];
    int bookings[2];
    struct Train* next;
    char destination[50];
    char start[50];
};
struct Train* head = NULL;
void notifyWithBeep() {
    printf("\a");
}
void signup() {
    printf("Enter a new username: ");
    scanf("%s", current_user.username);

    printf("Enter a new password: ");
    scanf("%s", current_user.password);

    // Check if the maximum number of users has been reached
    if (userCount < MAX_USERS) {
        // Add the new user to the array
        strcpy(users[userCount].username, current_user.username);
        strcpy(users[userCount].password, current_user.password);

        // Increment the userCount
        userCount++;

        printf("Account created successfully!\n");
    } else {
        printf("Maximum number of users reached. Cannot create a new account.\n");
    }
}

bool authenticateUser() {
    // Check if the entered username exists and if the password matches
    for (int i = 0; i < userCount; ++i) {
        if (strcmp(current_user.username, users[i].username) == 0 &&
            strcmp(current_user.password, users[i].password) == 0) {
            return true; // Authentication successful
        }
    }

    return false; // Authentication failed
}

void login() {
    char choice;
    int loginAttempts = 3;

    do {
        printf("Do you have an account? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'n' || choice == 'N') {
            signup();
        }

        printf("Enter your username: ");
        scanf("%s", current_user.username);

        printf("Enter your password: ");
        scanf("%s", current_user.password);

        if (authenticateUser()) {
            printf("Login successful!\n");
            break; // Exit the loop on successful login
        } else {
            printf("Login failed. Invalid username or password. Remaining attempts: %d\n", --loginAttempts);
        }
    } while (loginAttempts > 0);

    if (loginAttempts == 0) {
        printf("Maximum login attempts reached. Exiting.\n");
        exit(EXIT_FAILURE);
    }
}






void initializeTrains() {
    // Train 1
    struct Train* train1 = (struct Train*)malloc(sizeof(struct Train));
    strcpy(train1->train_name, "Express1");
    strcpy(train1->start, "StationA");
    strcpy(train1->destination, "StationB");
    train1->available_seats[0] = 50;
    train1->ticket_price[0] = 10.5;
    train1->available_seats[1] = 50;  
    train1->ticket_price[1]=15.0;
    train1->next = NULL;

    // Train 2
    struct Train* train2 = (struct Train*)malloc(sizeof(struct Train));
    strcpy(train2->train_name, "Express2");
    strcpy(train2->start, "StationC");
    strcpy(train2->destination, "StationD");
    train2->available_seats[0] = 40;
    train2->ticket_price[0] = 12.0;
    train2->available_seats[1] = 40;
    train2->ticket_price[1] = 18.0;  
    train2->next = NULL;

    // Train 3
    struct Train* train3 = (struct Train*)malloc(sizeof(struct Train));
    strcpy(train3->train_name, "Express3");
    strcpy(train3->start, "StationE");
    strcpy(train3->destination, "StationF");
    train3->available_seats[0] = 30;
    train3->ticket_price[0] = 15.75;
    train3->available_seats[1] = 30;
    train3->ticket_price[1] = 20.5;  
    train3->next = NULL;
    train1->next = train2;
    train2->next = train3;
    head = train1;
}
void displayTrainDetails(struct Train* train) {
    printf("Train Name: %s\n", train->train_name);
    printf("Route: %s to %s\n", train->start, train->destination);
    printf("Available Seats (General): %d\n", train->available_seats[0]);
    printf("Ticket Price (General): $%.2f\n", train->ticket_price[0]);
    printf("Available Seats (Sleeper): %d\n", train->available_seats[1]);
    printf("Ticket Price (Sleeper): $%.2f\n", train->ticket_price[1]);
    printf("\n");
}


void book_tickets() {
        printf("Train Details:\n");

    struct Train* current = head;
    while (current != NULL) {
        displayTrainDetails(current);
        current = current->next;
    }
    
    char selected_train_name[50];
    int num_tickets, class_choice, seat_number;
initializeTrains();
    printf("Enter the name of the train you want to book tickets for: ");
    scanf("%s", selected_train_name);
    current=head;
   
    while (current != NULL) {
        int i;
        for (i = 0; selected_train_name[i] != '\0' && current->train_name[i] != '\0'; ++i) {
            if (selected_train_name[i] != current->train_name[i]) {
                break;
            }
        }

        if (selected_train_name[i] == '\0' && current->train_name[i] == '\0') {
            printf("Enter the class (0 for General, 1 for Sleeper): ");
            scanf("%d", &class_choice);

            printf("Enter the number of tickets to book: ");
            scanf("%d", &num_tickets);

            if (num_tickets > 0 && num_tickets <= current->available_seats[class_choice]) {
                printf("Available seats for class %d: %d\n", class_choice, current->available_seats[class_choice]);
                printf("Enter the seat number(s) to book (separated by spaces): ");
                
                for (int j = 0; j < num_tickets; ++j) {
                    scanf("%d", &seat_number);
if (seat_number >= 1 && seat_number <= current->available_seats[class_choice]) {
    
    if (current->available_seats[class_choice] - num_tickets >= 0) {
       
        for (int j = 0; j < num_tickets; ++j) {
            current->available_seats[class_choice]--;
            current->bookings[class_choice]++;
            printf("Booking successful! Seat %d booked.\n", seat_number + j);
        }
        printf("Total Price: %.2f\n", num_tickets * current->ticket_price[class_choice]);
        notifyWithBeep();
        return;
    } else {
        printf("Not enough available seats. Please choose fewer tickets or another class.\n");
        return;
    }
} else {
    printf("Invalid seat number. Please choose a valid seat.\n");
    return;
}

                }

                printf("Total Price: %f\n", num_tickets * current->ticket_price[class_choice]);
                notifyWithBeep();
                return;
            } else {
                printf("Invalid number of tickets\n");
                return;
            }
        }
        current = current->next;
    }

    printf("Train not found\n");
}
void generatePopularRoutesReport() {
    printf("Popular Routes Report:\n");

    struct Train* current = head;
    while (current != NULL) {
        printf("Route: %s to %s\n", current->start, current->destination);
        printf("  Bookings (General): %d\n", current->bookings[0]);
        printf("  Bookings (Sleeper): %d\n", current->bookings[1]);

        current = current->next;
    }
}
void cancel_tickets() {
    char cancel_train_name[50];
    int num_cancel_tickets;
    int class_choice;

    printf("Enter the name of the train you want to cancel tickets: ");
    scanf("%s", cancel_train_name);

    struct Train* current = head;
    while (current != NULL) {
        int i;
        for (i = 0; cancel_train_name[i] != '\0' && current->train_name[i] != '\0'; ++i) {
            if (cancel_train_name[i] != current->train_name[i]) {
                break;
            }
        }
        if (cancel_train_name[i] == '\0' && current->train_name[i] == '\0') {
            printf("Enter the class (0 for General, 1 for Sleeper): ");
            scanf("%d", &class_choice);

            printf("Enter the number of tickets to cancel: ");
            scanf("%d", &num_cancel_tickets);

            if (num_cancel_tickets > 0 && num_cancel_tickets <= current->bookings[class_choice]) {
                current->available_seats[class_choice] += num_cancel_tickets;
                current->bookings[class_choice] -= num_cancel_tickets;
                printf("Cancellation successful!\n");
                printf("Train: %s, Number of tickets cancelled: %d\n", current->train_name, num_cancel_tickets);
                return;
            } else {
                printf("Invalid number of tickets to cancel\n");
                return;
            }
        }

        current = current->next;
    }

    printf("Train not found\n");
}
void feedback() {
    char user_feedback[200];  

    printf("Enter your feedback: ");
    scanf(" %[^\n]", user_feedback);

    printf("Thank you for your feedback!\n");
}
void rating() {
    int user_rating;

    printf("Enter your rating (1 to 5): ");
    scanf("%d", &user_rating);

    
    if (user_rating >= 1 && user_rating <= 5) {
        printf("Thank you for your rating!\n");
    } else {
        printf("Invalid rating. Please enter a number between 1 and 5.\n");
    }
}


int main() {
    login();
    initializeTrains();
    int choice;
    while (choice != 10) {
        printf("Welcome To The Railway Booking Platform\n");
        printf("\n\n1. Book tickets\n2. Cancel tickets\n 3. Feedback\n 4. Rating\n 5. Report Generation\n 6.Exit\n");
        printf("Please enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            book_tickets();
            break;
        case 2:
            cancel_tickets();
            break;
        case 3:
            feedback();
            break;
        case 4:
            rating();
            break;
        case 5:            generatePopularRoutesReport();
            break;
        case 6:
            exit(0);
            printf("Thanks For visiting\n");
            break;
        default:
            printf("Please enter a valid choice\n");
        }
    }
    struct Train* current = head;
    while (current != NULL) {
        struct Train* next = current->next;
        free(current);
        current = next;
    }
    return 0;
}

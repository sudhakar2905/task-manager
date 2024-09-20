#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASKS 100
#define MAX_TASK_NAME_LENGTH 50

typedef struct {
    char name[MAX_TASK_NAME_LENGTH];
    int completed;
} Task;

Task taskList[MAX_TASKS];
int numTasks = 0;

void addTask(const char* name) {
    if (numTasks < MAX_TASKS) {
        strncpy(taskList[numTasks].name, name, MAX_TASK_NAME_LENGTH - 1);
        taskList[numTasks].completed = 0;
        numTasks++;
        printf("Task added successfully.\n");
    } else {
        printf("Task list is full. Cannot add more tasks.\n");
    }
}

void completeTask(int taskIndex) {
    if (taskIndex >= 0 && taskIndex < numTasks) {
        taskList[taskIndex].completed = 1;
        printf("Task marked as completed.\n");
    } else {
        printf("Invalid task index.\n");
    }
}

void displayTasks() {
    printf("Task List:\n");
    for (int i = 0; i < numTasks; i++) {
        printf("%d. [%s] %s\n", i + 1, taskList[i].completed ? "X" : " ", taskList[i].name);
    }
}

void saveTasksToFile(const char* filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < numTasks; i++) {
        fprintf(file, "%s %d\n", taskList[i].name, taskList[i].completed);
    }

    fclose(file);
}

void loadTasksFromFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    while (fscanf(file, "%s %d", taskList[numTasks].name, &taskList[numTasks].completed) == 2) {
        numTasks++;
        if (numTasks >= MAX_TASKS) {
            printf("Max task limit reached while loading from file.\n");
            break;
        }
    }

    fclose(file);
}

int main() {
    int choice;
    char taskName[MAX_TASK_NAME_LENGTH];
    const char* filename = "tasks.txt";

    loadTasksFromFile(filename);

    do {
        printf("\nTask Manager\n");
        printf("1. Add Task\n");
        printf("2. Complete Task\n");
        printf("3. Display Tasks\n");
        printf("4. Save Tasks to File\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter task name: ");
                scanf("%s", taskName);
                addTask(taskName);
                break;
            case 2:
                if (numTasks > 0) {
                    printf("Enter task index to mark as completed (1-%d): ", numTasks);
                    int index;
                    scanf("%d", &index);
                    completeTask(index - 1);
                } else {
                    printf("No tasks to complete.\n");
                }
                break;
            case 3:
                if (numTasks > 0) {
                    displayTasks();
                } else {
                    printf("No tasks added yet.\n");
                }
                break;
            case 4:
                saveTasksToFile(filename);
                printf("Tasks saved to file.\n");
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}

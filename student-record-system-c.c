#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function declarations
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n===== Student Record Management System =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search by Roll Number\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}

void addStudent() {
    struct Student s;
    FILE *fp = fopen("students.dat", "ab");

    printf("Enter Roll Number: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);  // To read full name with spaces
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

void viewStudents() {
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    printf("\n--- All Student Records ---\n");
    while (fread(&s, sizeof(s), 1, fp)) {
        printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

void searchStudent() {
    int roll, found = 0;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");

    printf("Enter Roll Number to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Record Found:\n");
            printf("Roll: %d | Name: %s | Marks: %.2f\n", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("No record found for Roll No: %d\n", roll);
    }
}

void updateStudent() {
    int roll, found = 0;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb+");

    printf("Enter Roll Number to update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR); // move back to overwrite
            fwrite(&s, sizeof(s), 1, fp);
            printf("Record updated successfully!\n");
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found) {
        printf("Record not found!\n");
    }
}

void deleteStudent() {
    int roll, found = 0;
    struct Student s;
    FILE *fp = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");

    printf("Enter Roll Number to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            continue; // skip the record to delete
        }
        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Record deleted successfully!\n");
    } else {
        printf("Record not found!\n");
    }
}

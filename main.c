
#include <stdio.h> 
  
// Defining process details 
struct process { 
    char name; 
    int arrival_time, burst_time, ct, waiting_time, turnaround_time; 
    int completed; 
    float normalized_turnaround_time; 
} process[10]; 
  
int no_of_process; 
  
// Sorting Processes by Arrival Time 
void sortByArrival() 
{ 
    struct process temp; 
    int i, j; 
  
    // Selection Sort applied 
    for (i = 0; i < no_of_process - 1; i++) { 
        for (j = i + 1; j < no_of_process; j++) { 
  
            // Check for lesser arrival time 
            if (process[i].arrival_time > process[j].arrival_time) { 
  
                // Swap earlier process to front 
                temp = process[i]; 
                process[i] = process[j]; 
                process[j] = temp; 
            } 
        } 
    } 
} 
  
void main() 
{ 
    int i, j, times, sum_bt = 0; 
    char c; 
    float average_waiting_time = 0, average_turnaround_time = 0; 
    printf("Enter total no of processes:\n");
    scanf("%d",&no_of_process);
    // predefined arrival times 
    int arriv[10];
    for(i=0;i<no_of_process;i++){
        printf("Enter arrival time for process:%d\n",i+1);
        scanf("%d",&arriv[i]);
    }
  
    // predefined burst times 
    int burst[10];
    for(i=0;i<no_of_process;i++){
        printf("Enter burst time for process:%d\n",i+1);
        scanf("%d",&burst[i]);
    }
  
    // Initializing the structure variables 
    for (i = 0, c = 'A'; i < no_of_process; i++, c++) { 
        process[i].name = c; 
        process[i].arrival_time = arriv[i]; 
        process[i].burst_time = burst[i]; 
  
        // Variable for Completion status 
        // Pending = 0 
        // Completed = 1 
        process[i].completed = 0; 
  
        // Variable for sum of all Burst Times 
        sum_bt += process[i].burst_time; 
    } 
  
    // Sorting the structure by arrival times 
    sortByArrival(); 
    printf("\nName\tArrival Time\tBurst Time\tWaiting Time"); 
    printf("\tTurnAround Time\t Normalized TT"); 
    for (times = process[0].arrival_time; times < sum_bt;) { 
  
        // Set lower limit to response ratio 
        float hrr = -9999; 
  
        // Response Ratio Variable 
        float temp; 
  
        // Variable to store next processs selected 
        int loc; 
        for (i = 0; i < no_of_process; i++) { 
  
            // Checking if process has arrived and is Incomplete 
            if (process[i].arrival_time <= times && process[i].completed != 1) { 
  
                // Calculating Response Ratio 
                temp = (process[i].burst_time + (times - process[i].arrival_time)) / process[i].burst_time; 
  
                // Checking for Highest Response Ratio 
                if (hrr < temp) { 
  
                    // Storing Response Ratio 
                    hrr = temp; 
  
                    // Storing Location 
                    loc = i; 
                } 
            } 
        } 
  
        // Updating time value 
        times += process[loc].burst_time; 
  
        // Calculation of waiting time 
        process[loc].waiting_time = times - process[loc].arrival_time - process[loc].burst_time; 
  
        // Calculation of Turn Around Time 
        process[loc].turnaround_time = times - process[loc].arrival_time; 
  
        // Sum Turn Around Time for average 
        average_turnaround_time += process[loc].turnaround_time; 
  
        // Calculation of Normalized Turn Around Time 
        process[loc].normalized_turnaround_time = ((float)process[loc].turnaround_time / process[loc].burst_time); 
  
        // Updating Completion Status 
        process[loc].completed = 1; 
  
        // Sum Waiting Time for average 
        average_waiting_time += process[loc].waiting_time; 
        printf("\n%c\t\t%d\t\t", process[loc].name, process[loc].arrival_time); 
        printf("%d\t\t%d\t", process[loc].burst_time, process[loc].waiting_time); 
        printf("%d\t\t%f", process[loc].turnaround_time, process[loc].normalized_turnaround_time); 
    } 
    printf("\nAverage waiting time:%f\n", average_waiting_time / no_of_process); 
    printf("Average Turn Around time:%f\n", average_turnaround_time / no_of_process); 
} 
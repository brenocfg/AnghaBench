#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 char** cpustate_names ; 
 int /*<<< orphan*/  cpustates_column ; 
 int /*<<< orphan*/  lastline ; 
 int /*<<< orphan*/  lcpustates ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int num_cpus ; 
 int num_cpustates ; 
 int printf (char*,...) ; 

void
i_cpustates(int *states)
{
    int i = 0;
    int value;
    const char * const *names;
    const char *thisname;
    int *hstates = states;
    int cpu;

for (cpu = 0; cpu < num_cpus; cpu++) {
    names = cpustate_names;

    /* print tag and bump lastline */
    if (num_cpus == 1)
	printf("\nCPU: ");
    else {
	value = printf("\nCPU %d: ", cpu);
	while (value++ <= cpustates_column)
		printf(" ");
    }
    lastline++;

    /* now walk thru the names and print the line */
    while ((thisname = *names++) != NULL)
    {
	if (*thisname != '\0')
	{
	    /* retrieve the value and remember it */
	    value = *states++;

	    /* if percentage is >= 1000, print it as 100% */
	    printf((value >= 1000 ? "%s%4.0f%% %s" : "%s%4.1f%% %s"),
		   (i++ % num_cpustates) == 0 ? "" : ", ",
		   ((float)value)/10.,
		   thisname);
	}
    }
}

    /* copy over values into "last" array */
    states = hstates;
    memcpy(lcpustates, states, num_cpustates * sizeof(int) * num_cpus);
}
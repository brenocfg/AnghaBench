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
 int* lcpustates ; 
 int num_cpus ; 
 int num_cpustates ; 
 int printf (char*,...) ; 

void
z_cpustates(void)
{
    int i = 0;
    const char * const *names;
    const char *thisname;
    int cpu, value;

    for (cpu = 0; cpu < num_cpus; cpu++) {
	    names = cpustate_names;

	    /* show tag and bump lastline */
	    if (num_cpus == 1)
		    printf("\nCPU: ");
	    else {
		    value = printf("\nCPU %d: ", cpu);
		    while (value++ <= cpustates_column)
			    printf(" ");
	    }
	    lastline++;

	    while ((thisname = *names++) != NULL)
	    {
		    if (*thisname != '\0')
		    {
			    printf("%s    %% %s", (i++ % num_cpustates) == 0 ? "" : ", ", thisname);
		    }
	    }
    }

    /* fill the "last" array with all -1s, to insure correct updating */
	for (i = 0; i < num_cpustates * num_cpus; ++i) {
		lcpustates[i] = -1;
    }
}
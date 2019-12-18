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
 int /*<<< orphan*/  Move_to (scalar_t__,scalar_t__) ; 
 int* cpustate_columns ; 
 char** cpustate_names ; 
 scalar_t__ cpustates_column ; 
 scalar_t__ lastline ; 
 int* lcpustates ; 
 int num_cpus ; 
 int num_cpustates ; 
 int /*<<< orphan*/  printf (char*,double) ; 
 scalar_t__ y_cpustates ; 

void
u_cpustates(int *states)
{
    int value;
    const char * const *names;
    const char *thisname;
    int *hstates = states;
    int *lp;
    int *colp;
    int cpu;

for (cpu = 0; cpu < num_cpus; cpu++) {
    names = cpustate_names;

    Move_to(cpustates_column, y_cpustates + cpu);
    lastline = y_cpustates + cpu;
    lp = lcpustates + (cpu * num_cpustates);
    colp = cpustate_columns;

    /* we could be much more optimal about this */
    while ((thisname = *names++) != NULL)
    {
	if (*thisname != '\0')
	{
	    /* did the value change since last time? */
	    if (*lp != *states)
	    {
		/* yes, move and change */
		Move_to(cpustates_column + *colp, y_cpustates + cpu);
		lastline = y_cpustates + cpu;

		/* retrieve value and remember it */
		value = *states;

		/* if percentage is >= 1000, print it as 100% */
		printf((value >= 1000 ? "%4.0f" : "%4.1f"),
		       ((double)value)/10.);

		/* remember it for next time */
		*lp = value;
	    }
	}

	/* increment and move on */
	lp++;
	states++;
	colp++;
    }
}

    states = hstates;
}
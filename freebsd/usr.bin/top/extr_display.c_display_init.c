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
struct statics {char** cpustate_names; int ncpus; int /*<<< orphan*/  carc_names; int /*<<< orphan*/  arc_names; int /*<<< orphan*/  memory_names; int /*<<< orphan*/  swap_names; int /*<<< orphan*/  procstate_names; } ;

/* Variables and functions */
 int CPUSTATES ; 
 int /*<<< orphan*/  arc_names ; 
 int /*<<< orphan*/  assert (int) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  carc_names ; 
 int* cpustate_columns ; 
 char** cpustate_names ; 
 int cpustate_total_length ; 
 int display_updatecpus (struct statics*) ; 
 void* lcpustates ; 
 void* lmemory ; 
 void* lprocstates ; 
 void* lswap ; 
 int /*<<< orphan*/  memory_names ; 
 int num_cpustates ; 
 int num_memory ; 
 int num_procstates ; 
 int num_swap ; 
 int /*<<< orphan*/  procstate_names ; 
 int strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_names ; 

int
display_init(struct statics * statics)
{
    int lines;
    const char * const *pp;
    int *ip;
    int i;

    lines = display_updatecpus(statics);

    /* only do the rest if we need to */
    if (lines > -1)
    {
	/* save pointers and allocate space for names */
	procstate_names = statics->procstate_names;
	num_procstates = 8;
	assert(num_procstates > 0);
	lprocstates = calloc(num_procstates, sizeof(int));

	cpustate_names = statics->cpustate_names;

	swap_names = statics->swap_names;
	num_swap = 7;
	assert(num_swap > 0);
	lswap = calloc(num_swap, sizeof(int));
	num_cpustates = CPUSTATES;
	assert(num_cpustates > 0);
	lcpustates = calloc(num_cpustates * sizeof(int), statics->ncpus);
	cpustate_columns = calloc(num_cpustates, sizeof(int));

	memory_names = statics->memory_names;
	num_memory = 7;
	assert(num_memory > 0);
	lmemory = calloc(num_memory, sizeof(int));

	arc_names = statics->arc_names;
	carc_names = statics->carc_names;

	/* calculate starting columns where needed */
	cpustate_total_length = 0;
	pp = cpustate_names;
	ip = cpustate_columns;
	while (*pp != NULL)
	{
	    *ip++ = cpustate_total_length;
	    if ((i = strlen(*pp++)) > 0)
	    {
		cpustate_total_length += i + 8;
	    }
	}
    }

    /* return number of lines available */
    return(lines);
}
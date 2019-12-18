#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  Move_to (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int digits (int) ; 
 int lastline ; 
 int /*<<< orphan*/  line_update (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lprocstates ; 
 int ltotal ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int num_procstates ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  procstate_names ; 
 int /*<<< orphan*/  procstates_buffer ; 
 TYPE_1__ ps ; 
 int /*<<< orphan*/  putchar (char) ; 
 char* setup_buffer (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  summary_format (char*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x_brkdn ; 
 scalar_t__ x_procstate ; 
 int /*<<< orphan*/  y_brkdn ; 
 int /*<<< orphan*/  y_procstate ; 

void
u_procstates(int total, int *brkdn)
{
    static char *new = NULL;
    int i;

    new = setup_buffer(new, 0);

    /* update number of processes only if it has changed */
    if (ltotal != total)
    {
	/* move and overwrite */
	if (x_procstate == 0) {
	    Move_to(x_procstate, y_procstate);
	}
	else {
	    /* cursor is already there...no motion needed */
	    assert(lastline == 1);
	}
	printf("%d", total);

	/* if number of digits differs, rewrite the label */
	if (digits(total) != digits(ltotal))
	{
	    printf(" %s:", ps.thread ? "threads" : "processes");
	    /* put out enough spaces to get to column 15 */
	    i = digits(total);
	    while (i++ < (ps.thread ? 6 : 4))
	    {
		putchar(' ');
	    }
	    /* cursor may end up right where we want it!!! */
	}

	/* save new total */
	ltotal = total;
    }

    /* see if any of the state numbers has changed */
    if (memcmp(lprocstates, brkdn, num_procstates * sizeof(int)) != 0)
    {
	/* format and update the line */
	summary_format(new, brkdn, procstate_names);
	line_update(procstates_buffer, new, x_brkdn, y_brkdn);
	memcpy(lprocstates, brkdn, num_procstates * sizeof(int));
    }
}
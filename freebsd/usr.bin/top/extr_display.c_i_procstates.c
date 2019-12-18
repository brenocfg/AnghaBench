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
 int digits (int) ; 
 int /*<<< orphan*/  fputs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lprocstates ; 
 int ltotal ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int num_procstates ; 
 int /*<<< orphan*/  printf (char*,int,char*) ; 
 int /*<<< orphan*/  procstate_names ; 
 int /*<<< orphan*/  procstates_buffer ; 
 TYPE_1__ ps ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  setup_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  summary_format (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 

void
i_procstates(int total, int *brkdn)
{
    int i;

    procstates_buffer = setup_buffer(procstates_buffer, 0);

    /* write current number of processes and remember the value */
    printf("%d %s:", total, ps.thread ? "threads" : "processes");
    ltotal = total;

    /* put out enough spaces to get to column 15 */
    i = digits(total);
    while (i++ < (ps.thread ? 6 : 4))
    {
	putchar(' ');
    }

    /* format and print the process state summary */
    summary_format(procstates_buffer, brkdn, procstate_names);
    fputs(procstates_buffer, stdout);

    /* save the numbers for next time */
    memcpy(lprocstates, brkdn, num_procstates * sizeof(int));
}
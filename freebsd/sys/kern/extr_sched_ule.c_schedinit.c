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
struct td_sched {int /*<<< orphan*/  ts_cpu; scalar_t__ ts_slice; void* ts_ftick; void* ts_ltick; } ;

/* Variables and functions */
 int /*<<< orphan*/  curcpu ; 
 struct td_sched* td_get_sched (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread0 ; 
 void* ticks ; 

void
schedinit(void)
{
	struct td_sched *ts0;

	/*
	 * Set up the scheduler specific parts of thread0.
	 */
	ts0 = td_get_sched(&thread0);
	ts0->ts_ltick = ticks;
	ts0->ts_ftick = ticks;
	ts0->ts_slice = 0;
	ts0->ts_cpu = curcpu;	/* set valid CPU number */
}
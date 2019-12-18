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
typedef  int u_int ;
struct td_sched {int ts_ltick; int ts_ticks; int ts_ftick; } ;

/* Variables and functions */
 int SCHED_TICK_MAX ; 
 int SCHED_TICK_SHIFT ; 
 int SCHED_TICK_TARG ; 
 int ticks ; 

__attribute__((used)) static void
sched_pctcpu_update(struct td_sched *ts, int run)
{
	int t = ticks;

	/*
	 * The signed difference may be negative if the thread hasn't run for
	 * over half of the ticks rollover period.
	 */
	if ((u_int)(t - ts->ts_ltick) >= SCHED_TICK_TARG) {
		ts->ts_ticks = 0;
		ts->ts_ftick = t - SCHED_TICK_TARG;
	} else if (t - ts->ts_ftick >= SCHED_TICK_MAX) {
		ts->ts_ticks = (ts->ts_ticks / (ts->ts_ltick - ts->ts_ftick)) *
		    (ts->ts_ltick - (t - SCHED_TICK_TARG));
		ts->ts_ftick = t - SCHED_TICK_TARG;
	}
	if (run)
		ts->ts_ticks += (t - ts->ts_ltick) << SCHED_TICK_SHIFT;
	ts->ts_ltick = t;
}
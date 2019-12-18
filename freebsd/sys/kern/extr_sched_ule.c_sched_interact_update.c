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
struct thread {int dummy; } ;
struct td_sched {int ts_runtime; int ts_slptime; } ;

/* Variables and functions */
 int SCHED_SLP_RUN_MAX ; 
 struct td_sched* td_get_sched (struct thread*) ; 

__attribute__((used)) static void
sched_interact_update(struct thread *td)
{
	struct td_sched *ts;
	u_int sum;

	ts = td_get_sched(td);
	sum = ts->ts_runtime + ts->ts_slptime;
	if (sum < SCHED_SLP_RUN_MAX)
		return;
	/*
	 * This only happens from two places:
	 * 1) We have added an unusual amount of run time from fork_exit.
	 * 2) We have added an unusual amount of sleep time from sched_sleep().
	 */
	if (sum > SCHED_SLP_RUN_MAX * 2) {
		if (ts->ts_runtime > ts->ts_slptime) {
			ts->ts_runtime = SCHED_SLP_RUN_MAX;
			ts->ts_slptime = 1;
		} else {
			ts->ts_slptime = SCHED_SLP_RUN_MAX;
			ts->ts_runtime = 1;
		}
		return;
	}
	/*
	 * If we have exceeded by more than 1/5th then the algorithm below
	 * will not bring us back into range.  Dividing by two here forces
	 * us into the range of [4/5 * SCHED_INTERACT_MAX, SCHED_INTERACT_MAX]
	 */
	if (sum > (SCHED_SLP_RUN_MAX / 5) * 6) {
		ts->ts_runtime /= 2;
		ts->ts_slptime /= 2;
		return;
	}
	ts->ts_runtime = (ts->ts_runtime / 5) * 4;
	ts->ts_slptime = (ts->ts_slptime / 5) * 4;
}
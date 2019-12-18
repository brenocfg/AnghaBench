#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_proc; int /*<<< orphan*/  td_pri_class; } ;
struct TYPE_5__ {int /*<<< orphan*/  ts_ltick; int /*<<< orphan*/  ts_ftick; scalar_t__ ts_ticks; } ;
struct TYPE_4__ {scalar_t__ p_nice; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PRI_BASE (int /*<<< orphan*/ ) ; 
 int PRI_MAX_BATCH ; 
 int PRI_MAX_INTERACT ; 
 int PRI_MIN_BATCH ; 
 int PRI_MIN_INTERACT ; 
 scalar_t__ PRI_TIMESHARE ; 
 int SCHED_PRI_MIN ; 
 scalar_t__ SCHED_PRI_NICE (scalar_t__) ; 
 scalar_t__ SCHED_PRI_RANGE ; 
 int /*<<< orphan*/  SCHED_PRI_TICKS (TYPE_2__*) ; 
 int imax (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ min (int /*<<< orphan*/ ,scalar_t__) ; 
 int sched_interact ; 
 scalar_t__ sched_interact_score (struct thread*) ; 
 int /*<<< orphan*/  sched_user_prio (struct thread*,int) ; 
 TYPE_2__* td_get_sched (struct thread*) ; 

__attribute__((used)) static void
sched_priority(struct thread *td)
{
	int score;
	int pri;

	if (PRI_BASE(td->td_pri_class) != PRI_TIMESHARE)
		return;
	/*
	 * If the score is interactive we place the thread in the realtime
	 * queue with a priority that is less than kernel and interrupt
	 * priorities.  These threads are not subject to nice restrictions.
	 *
	 * Scores greater than this are placed on the normal timeshare queue
	 * where the priority is partially decided by the most recent cpu
	 * utilization and the rest is decided by nice value.
	 *
	 * The nice value of the process has a linear effect on the calculated
	 * score.  Negative nice values make it easier for a thread to be
	 * considered interactive.
	 */
	score = imax(0, sched_interact_score(td) + td->td_proc->p_nice);
	if (score < sched_interact) {
		pri = PRI_MIN_INTERACT;
		pri += ((PRI_MAX_INTERACT - PRI_MIN_INTERACT + 1) /
		    sched_interact) * score;
		KASSERT(pri >= PRI_MIN_INTERACT && pri <= PRI_MAX_INTERACT,
		    ("sched_priority: invalid interactive priority %d score %d",
		    pri, score));
	} else {
		pri = SCHED_PRI_MIN;
		if (td_get_sched(td)->ts_ticks)
			pri += min(SCHED_PRI_TICKS(td_get_sched(td)),
			    SCHED_PRI_RANGE - 1);
		pri += SCHED_PRI_NICE(td->td_proc->p_nice);
		KASSERT(pri >= PRI_MIN_BATCH && pri <= PRI_MAX_BATCH,
		    ("sched_priority: invalid priority %d: nice %d, " 
		    "ticks %d ftick %d ltick %d tick pri %d",
		    pri, td->td_proc->p_nice, td_get_sched(td)->ts_ticks,
		    td_get_sched(td)->ts_ftick, td_get_sched(td)->ts_ltick,
		    SCHED_PRI_TICKS(td_get_sched(td))));
	}
	sched_user_prio(td, pri);

	return;
}
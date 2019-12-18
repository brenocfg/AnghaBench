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
struct thread {int td_flags; } ;
typedef  scalar_t__ fixpt_t ;

/* Variables and functions */
#define  BOTH 130 
#define  ONLYA 129 
#define  ONLYB 128 
 int TDF_SINTR ; 
 int TD_IS_RUNNING (struct thread*) ; 
 int TD_ON_RUNQ (struct thread*) ; 
 int TESTAB (int,int) ; 
 scalar_t__ sched_pctcpu (struct thread*) ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 

__attribute__((used)) static int
thread_compare(struct thread *td, struct thread *td2)
{
	int runa, runb;
	int slpa, slpb;
	fixpt_t esta, estb;

	if (td == NULL)
		return (1);

	/*
	 * Fetch running stats, pctcpu usage, and interruptable flag.
	 */
	thread_lock(td);
	runa = TD_IS_RUNNING(td) | TD_ON_RUNQ(td);
	slpa = td->td_flags & TDF_SINTR;
	esta = sched_pctcpu(td);
	thread_unlock(td);
	thread_lock(td2);
	runb = TD_IS_RUNNING(td2) | TD_ON_RUNQ(td2);
	estb = sched_pctcpu(td2);
	slpb = td2->td_flags & TDF_SINTR;
	thread_unlock(td2);
	/*
	 * see if at least one of them is runnable
	 */
	switch (TESTAB(runa, runb)) {
	case ONLYA:
		return (0);
	case ONLYB:
		return (1);
	case BOTH:
		break;
	}
	/*
	 *  favor one with highest recent cpu utilization
	 */
	if (estb > esta)
		return (1);
	if (esta > estb)
		return (0);
	/*
	 * favor one sleeping in a non-interruptible sleep
	 */
	switch (TESTAB(slpa, slpb)) {
	case ONLYA:
		return (0);
	case ONLYB:
		return (1);
	case BOTH:
		break;
	}

	return (td < td2);
}
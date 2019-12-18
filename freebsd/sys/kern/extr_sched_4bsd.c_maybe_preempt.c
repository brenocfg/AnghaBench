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
struct thread {scalar_t__ td_inhibitors; int td_priority; int td_owepreempt; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR0 (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_PROC ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PRI_MAX_ITHD ; 
 int PRI_MIN_IDLE ; 
 scalar_t__ TD_IS_INHIBITED (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/ * panicstr ; 

int
maybe_preempt(struct thread *td)
{
#ifdef PREEMPTION
	struct thread *ctd;
	int cpri, pri;

	/*
	 * The new thread should not preempt the current thread if any of the
	 * following conditions are true:
	 *
	 *  - The kernel is in the throes of crashing (panicstr).
	 *  - The current thread has a higher (numerically lower) or
	 *    equivalent priority.  Note that this prevents curthread from
	 *    trying to preempt to itself.
	 *  - The current thread has an inhibitor set or is in the process of
	 *    exiting.  In this case, the current thread is about to switch
	 *    out anyways, so there's no point in preempting.  If we did,
	 *    the current thread would not be properly resumed as well, so
	 *    just avoid that whole landmine.
	 *  - If the new thread's priority is not a realtime priority and
	 *    the current thread's priority is not an idle priority and
	 *    FULL_PREEMPTION is disabled.
	 *
	 * If all of these conditions are false, but the current thread is in
	 * a nested critical section, then we have to defer the preemption
	 * until we exit the critical section.  Otherwise, switch immediately
	 * to the new thread.
	 */
	ctd = curthread;
	THREAD_LOCK_ASSERT(td, MA_OWNED);
	KASSERT((td->td_inhibitors == 0),
			("maybe_preempt: trying to run inhibited thread"));
	pri = td->td_priority;
	cpri = ctd->td_priority;
	if (panicstr != NULL || pri >= cpri /* || dumping */ ||
	    TD_IS_INHIBITED(ctd))
		return (0);
#ifndef FULL_PREEMPTION
	if (pri > PRI_MAX_ITHD && cpri < PRI_MIN_IDLE)
		return (0);
#endif

	CTR0(KTR_PROC, "maybe_preempt: scheduling preemption");
	ctd->td_owepreempt = 1;
	return (1);
#else
	return (0);
#endif
}
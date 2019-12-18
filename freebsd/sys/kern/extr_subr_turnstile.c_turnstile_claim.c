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
struct turnstile_chain {int /*<<< orphan*/  tc_lock; } ;
struct turnstile {int /*<<< orphan*/  ts_lock; int /*<<< orphan*/  ts_lockobj; } ;
struct thread {scalar_t__ td_priority; TYPE_1__* td_proc; struct turnstile* td_turnstile; } ;
struct TYPE_2__ {scalar_t__ p_magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ P_MAGIC ; 
 struct turnstile_chain* TC_LOOKUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THREAD_LOCKPTR_ASSERT (struct thread*,int /*<<< orphan*/ *) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_lend_prio (struct thread*,scalar_t__) ; 
 int /*<<< orphan*/  td_contested_lock ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 struct thread* turnstile_first_waiter (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_setowner (struct turnstile*,struct thread*) ; 

void
turnstile_claim(struct turnstile *ts)
{
	struct thread *td, *owner;
	struct turnstile_chain *tc;

	mtx_assert(&ts->ts_lock, MA_OWNED);
	MPASS(ts != curthread->td_turnstile);

	owner = curthread;
	mtx_lock_spin(&td_contested_lock);
	turnstile_setowner(ts, owner);
	mtx_unlock_spin(&td_contested_lock);

	td = turnstile_first_waiter(ts);
	MPASS(td != NULL);
	MPASS(td->td_proc->p_magic == P_MAGIC);
	THREAD_LOCKPTR_ASSERT(td, &ts->ts_lock);

	/*
	 * Update the priority of the new owner if needed.
	 */
	thread_lock(owner);
	if (td->td_priority < owner->td_priority)
		sched_lend_prio(owner, td->td_priority);
	thread_unlock(owner);
	tc = TC_LOOKUP(ts->ts_lockobj);
	mtx_unlock_spin(&ts->ts_lock);
	mtx_unlock_spin(&tc->tc_lock);
}
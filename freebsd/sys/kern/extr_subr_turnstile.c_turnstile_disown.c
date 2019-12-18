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
typedef  int /*<<< orphan*/  u_char ;
struct turnstile {int /*<<< orphan*/  ts_lock; struct thread* ts_owner; int /*<<< orphan*/ * ts_blocked; int /*<<< orphan*/  ts_pending; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct turnstile*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 size_t TS_EXCLUSIVE_QUEUE ; 
 size_t TS_SHARED_QUEUE ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_unlend_prio (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  td_contested_lock ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int /*<<< orphan*/  ts_link ; 
 int /*<<< orphan*/  turnstile_calc_unlend_prio_locked (struct thread*) ; 

void
turnstile_disown(struct turnstile *ts)
{
	struct thread *td;
	u_char pri;

	MPASS(ts != NULL);
	mtx_assert(&ts->ts_lock, MA_OWNED);
	MPASS(ts->ts_owner == curthread);
	MPASS(TAILQ_EMPTY(&ts->ts_pending));
	MPASS(!TAILQ_EMPTY(&ts->ts_blocked[TS_EXCLUSIVE_QUEUE]) ||
	    !TAILQ_EMPTY(&ts->ts_blocked[TS_SHARED_QUEUE]));

	/*
	 * Remove the turnstile from this thread's list of contested locks
	 * since this thread doesn't own it anymore.  New threads will
	 * not be blocking on the turnstile until it is claimed by a new
	 * owner.
	 */
	mtx_lock_spin(&td_contested_lock);
	ts->ts_owner = NULL;
	LIST_REMOVE(ts, ts_link);
	mtx_unlock_spin(&td_contested_lock);

	/*
	 * Adjust the priority of curthread based on other contested
	 * locks it owns.  Don't lower the priority below the base
	 * priority however.
	 */
	td = curthread;
	thread_lock(td);
	mtx_unlock_spin(&ts->ts_lock);
	mtx_lock_spin(&td_contested_lock);
	pri = turnstile_calc_unlend_prio_locked(td);
	mtx_unlock_spin(&td_contested_lock);
	sched_unlend_prio(td, pri);
	thread_unlock(td);
}
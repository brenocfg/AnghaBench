#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct turnstile {int /*<<< orphan*/  ts_lock; TYPE_2__* ts_lockobj; struct thread* ts_owner; } ;
struct thread {int td_priority; int td_tid; struct turnstile* td_blocked; int /*<<< orphan*/  td_state; int /*<<< orphan*/  td_name; TYPE_1__* td_proc; } ;
struct TYPE_4__ {int /*<<< orphan*/  lo_name; } ;
struct TYPE_3__ {scalar_t__ p_magic; int p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  MTX_DUPOK ; 
 scalar_t__ P_MAGIC ; 
 scalar_t__ TD_IS_RUNNING (struct thread*) ; 
 scalar_t__ TD_IS_SLEEPING (struct thread*) ; 
 int TD_ON_LOCK (struct thread*) ; 
 scalar_t__ TD_ON_RUNQ (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCKPTR_ASSERT (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  THREAD_LOCK_ASSERT (struct thread*,int /*<<< orphan*/ ) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  kdb_backtrace_thread (struct thread*) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  sched_lend_prio (struct thread*,int) ; 
 int /*<<< orphan*/  thread_lock_flags (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 int /*<<< orphan*/  turnstile_adjust_thread (struct turnstile*,struct thread*) ; 

__attribute__((used)) static void
propagate_priority(struct thread *td)
{
	struct turnstile *ts;
	int pri;

	THREAD_LOCK_ASSERT(td, MA_OWNED);
	pri = td->td_priority;
	ts = td->td_blocked;
	THREAD_LOCKPTR_ASSERT(td, &ts->ts_lock);
	/*
	 * Grab a recursive lock on this turnstile chain so it stays locked
	 * for the whole operation.  The caller expects us to return with
	 * the original lock held.  We only ever lock down the chain so
	 * the lock order is constant.
	 */
	mtx_lock_spin(&ts->ts_lock);
	for (;;) {
		td = ts->ts_owner;

		if (td == NULL) {
			/*
			 * This might be a read lock with no owner.  There's
			 * not much we can do, so just bail.
			 */
			mtx_unlock_spin(&ts->ts_lock);
			return;
		}

		thread_lock_flags(td, MTX_DUPOK);
		mtx_unlock_spin(&ts->ts_lock);
		MPASS(td->td_proc != NULL);
		MPASS(td->td_proc->p_magic == P_MAGIC);

		/*
		 * If the thread is asleep, then we are probably about
		 * to deadlock.  To make debugging this easier, show
		 * backtrace of misbehaving thread and panic to not
		 * leave the kernel deadlocked.
		 */
		if (TD_IS_SLEEPING(td)) {
			printf(
		"Sleeping thread (tid %d, pid %d) owns a non-sleepable lock\n",
			    td->td_tid, td->td_proc->p_pid);
			kdb_backtrace_thread(td);
			panic("sleeping thread");
		}

		/*
		 * If this thread already has higher priority than the
		 * thread that is being blocked, we are finished.
		 */
		if (td->td_priority <= pri) {
			thread_unlock(td);
			return;
		}

		/*
		 * Bump this thread's priority.
		 */
		sched_lend_prio(td, pri);

		/*
		 * If lock holder is actually running or on the run queue
		 * then we are done.
		 */
		if (TD_IS_RUNNING(td) || TD_ON_RUNQ(td)) {
			MPASS(td->td_blocked == NULL);
			thread_unlock(td);
			return;
		}

#ifndef SMP
		/*
		 * For UP, we check to see if td is curthread (this shouldn't
		 * ever happen however as it would mean we are in a deadlock.)
		 */
		KASSERT(td != curthread, ("Deadlock detected"));
#endif

		/*
		 * If we aren't blocked on a lock, we should be.
		 */
		KASSERT(TD_ON_LOCK(td), (
		    "thread %d(%s):%d holds %s but isn't blocked on a lock\n",
		    td->td_tid, td->td_name, td->td_state,
		    ts->ts_lockobj->lo_name));

		/*
		 * Pick up the lock that td is blocked on.
		 */
		ts = td->td_blocked;
		MPASS(ts != NULL);
		THREAD_LOCKPTR_ASSERT(td, &ts->ts_lock);
		/* Resort td on the list if needed. */
		if (!turnstile_adjust_thread(ts, td)) {
			mtx_unlock_spin(&ts->ts_lock);
			return;
		}
		/* The thread lock is released as ts lock above. */
	}
}
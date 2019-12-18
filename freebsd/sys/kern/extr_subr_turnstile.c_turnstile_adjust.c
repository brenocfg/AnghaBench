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
typedef  scalar_t__ u_char ;
struct turnstile {int /*<<< orphan*/ * ts_blocked; int /*<<< orphan*/  ts_lock; } ;
struct thread {size_t td_tsqueue; scalar_t__ td_priority; struct turnstile* td_blocked; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  MPASS (int) ; 
 struct thread* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int TD_ON_LOCK (struct thread*) ; 
 int /*<<< orphan*/  THREAD_LOCKPTR_ASSERT (struct thread*,int /*<<< orphan*/ *) ; 
 size_t TS_EXCLUSIVE_QUEUE ; 
 size_t TS_SHARED_QUEUE ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  propagate_priority (struct thread*) ; 
 int /*<<< orphan*/  turnstile_adjust_thread (struct turnstile*,struct thread*) ; 

void
turnstile_adjust(struct thread *td, u_char oldpri)
{
	struct turnstile *ts;

	MPASS(TD_ON_LOCK(td));

	/*
	 * Pick up the lock that td is blocked on.
	 */
	ts = td->td_blocked;
	MPASS(ts != NULL);
	THREAD_LOCKPTR_ASSERT(td, &ts->ts_lock);
	mtx_assert(&ts->ts_lock, MA_OWNED);

	/* Resort the turnstile on the list. */
	if (!turnstile_adjust_thread(ts, td))
		return;
	/*
	 * If our priority was lowered and we are at the head of the
	 * turnstile, then propagate our new priority up the chain.
	 * Note that we currently don't try to revoke lent priorities
	 * when our priority goes up.
	 */
	MPASS(td->td_tsqueue == TS_EXCLUSIVE_QUEUE ||
	    td->td_tsqueue == TS_SHARED_QUEUE);
	if (td == TAILQ_FIRST(&ts->ts_blocked[td->td_tsqueue]) &&
	    td->td_priority < oldpri) {
		propagate_priority(td);
	}
}
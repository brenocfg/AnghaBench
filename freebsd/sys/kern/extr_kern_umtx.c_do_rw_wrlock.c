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
typedef  scalar_t__ uint32_t ;
struct urwlock {int /*<<< orphan*/  rw_blocked_readers; int /*<<< orphan*/  rw_state; int /*<<< orphan*/  rw_blocked_writers; int /*<<< orphan*/  rw_flags; } ;
struct umtx_q {int /*<<< orphan*/  uq_key; } ;
struct thread {struct umtx_q* td_umtxq; } ;
struct abs_timeout {int dummy; } ;
struct _umtx_time {int dummy; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int EFAULT ; 
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  GET_SHARE (scalar_t__) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TYPE_RWLOCK ; 
 int /*<<< orphan*/  UMTX_EXCLUSIVE_QUEUE ; 
 int /*<<< orphan*/  UMTX_SHARED_QUEUE ; 
 scalar_t__ URWLOCK_READER_COUNT (scalar_t__) ; 
 scalar_t__ URWLOCK_WRITE_OWNER ; 
 scalar_t__ URWLOCK_WRITE_WAITERS ; 
 int /*<<< orphan*/  abs_timeout_init2 (struct abs_timeout*,struct _umtx_time*) ; 
 int casueword32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__) ; 
 int fueword32 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  suword32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int umtx_key_get (struct urwlock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_key_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_busy (int /*<<< orphan*/ *) ; 
 int umtxq_check_susp (struct thread*,int) ; 
 int /*<<< orphan*/  umtxq_insert_queue (struct umtx_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umtxq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_remove_queue (struct umtx_q*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  umtxq_signal_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int umtxq_sleep (struct umtx_q*,char*,struct abs_timeout*) ; 
 int /*<<< orphan*/  umtxq_unbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unbusy_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
do_rw_wrlock(struct thread *td, struct urwlock *rwlock, struct _umtx_time *timeout)
{
	struct abs_timeout timo;
	struct umtx_q *uq;
	uint32_t flags;
	int32_t state, oldstate;
	int32_t blocked_writers;
	int32_t blocked_readers;
	int error, error1, rv;

	uq = td->td_umtxq;
	error = fueword32(&rwlock->rw_flags, &flags);
	if (error == -1)
		return (EFAULT);
	error = umtx_key_get(rwlock, TYPE_RWLOCK, GET_SHARE(flags), &uq->uq_key);
	if (error != 0)
		return (error);

	if (timeout != NULL)
		abs_timeout_init2(&timo, timeout);

	blocked_readers = 0;
	for (;;) {
		rv = fueword32(&rwlock->rw_state, &state);
		if (rv == -1) {
			umtx_key_release(&uq->uq_key);
			return (EFAULT);
		}
		while ((state & URWLOCK_WRITE_OWNER) == 0 &&
		    URWLOCK_READER_COUNT(state) == 0) {
			rv = casueword32(&rwlock->rw_state, state,
			    &oldstate, state | URWLOCK_WRITE_OWNER);
			if (rv == -1) {
				umtx_key_release(&uq->uq_key);
				return (EFAULT);
			}
			if (rv == 0) {
				MPASS(oldstate == state);
				umtx_key_release(&uq->uq_key);
				return (0);
			}
			state = oldstate;
			error = umtxq_check_susp(td, true);
			if (error != 0)
				break;
		}

		if (error) {
			if ((state & (URWLOCK_WRITE_OWNER |
			    URWLOCK_WRITE_WAITERS)) == 0 &&
			    blocked_readers != 0) {
				umtxq_lock(&uq->uq_key);
				umtxq_busy(&uq->uq_key);
				umtxq_signal_queue(&uq->uq_key, INT_MAX,
				    UMTX_SHARED_QUEUE);
				umtxq_unbusy(&uq->uq_key);
				umtxq_unlock(&uq->uq_key);
			}

			break;
		}

		/* grab monitor lock */
		umtxq_lock(&uq->uq_key);
		umtxq_busy(&uq->uq_key);
		umtxq_unlock(&uq->uq_key);

		/*
		 * Re-read the state, in case it changed between the
		 * try-lock above and the check below.
		 */
		rv = fueword32(&rwlock->rw_state, &state);
		if (rv == -1)
			error = EFAULT;

		while (error == 0 && ((state & URWLOCK_WRITE_OWNER) ||
		    URWLOCK_READER_COUNT(state) != 0) &&
		    (state & URWLOCK_WRITE_WAITERS) == 0) {
			rv = casueword32(&rwlock->rw_state, state,
			    &oldstate, state | URWLOCK_WRITE_WAITERS);
			if (rv == -1) {
				error = EFAULT;
				break;
			}
			if (rv == 0) {
				MPASS(oldstate == state);
				goto sleep;
			}
			state = oldstate;
			error = umtxq_check_susp(td, false);
			if (error != 0)
				break;
		}
		if (error != 0) {
			umtxq_unbusy_unlocked(&uq->uq_key);
			break;
		}

		if ((state & URWLOCK_WRITE_OWNER) == 0 &&
		    URWLOCK_READER_COUNT(state) == 0) {
			umtxq_unbusy_unlocked(&uq->uq_key);
			error = umtxq_check_susp(td, false);
			if (error != 0)
				break;
			continue;
		}
sleep:
		rv = fueword32(&rwlock->rw_blocked_writers,
		    &blocked_writers);
		if (rv == -1) {
			umtxq_unbusy_unlocked(&uq->uq_key);
			error = EFAULT;
			break;
		}
		suword32(&rwlock->rw_blocked_writers, blocked_writers + 1);

		while ((state & URWLOCK_WRITE_OWNER) ||
		    URWLOCK_READER_COUNT(state) != 0) {
			umtxq_lock(&uq->uq_key);
			umtxq_insert_queue(uq, UMTX_EXCLUSIVE_QUEUE);
			umtxq_unbusy(&uq->uq_key);

			error = umtxq_sleep(uq, "uwrlck", timeout == NULL ?
			    NULL : &timo);

			umtxq_busy(&uq->uq_key);
			umtxq_remove_queue(uq, UMTX_EXCLUSIVE_QUEUE);
			umtxq_unlock(&uq->uq_key);
			if (error)
				break;
			rv = fueword32(&rwlock->rw_state, &state);
			if (rv == -1) {
				error = EFAULT;
				break;
			}
		}

		rv = fueword32(&rwlock->rw_blocked_writers,
		    &blocked_writers);
		if (rv == -1) {
			umtxq_unbusy_unlocked(&uq->uq_key);
			error = EFAULT;
			break;
		}
		suword32(&rwlock->rw_blocked_writers, blocked_writers-1);
		if (blocked_writers == 1) {
			rv = fueword32(&rwlock->rw_state, &state);
			if (rv == -1) {
				umtxq_unbusy_unlocked(&uq->uq_key);
				error = EFAULT;
				break;
			}
			for (;;) {
				rv = casueword32(&rwlock->rw_state, state,
				    &oldstate, state & ~URWLOCK_WRITE_WAITERS);
				if (rv == -1) {
					error = EFAULT;
					break;
				}
				if (rv == 0) {
					MPASS(oldstate == state);
					break;
				}
				state = oldstate;
				error1 = umtxq_check_susp(td, false);
				/*
				 * We are leaving the URWLOCK_WRITE_WAITERS
				 * behind, but this should not harm the
				 * correctness.
				 */
				if (error1 != 0) {
					if (error == 0)
						error = error1;
					break;
				}
			}
			rv = fueword32(&rwlock->rw_blocked_readers,
			    &blocked_readers);
			if (rv == -1) {
				umtxq_unbusy_unlocked(&uq->uq_key);
				error = EFAULT;
				break;
			}
		} else
			blocked_readers = 0;

		umtxq_unbusy_unlocked(&uq->uq_key);
	}

	umtx_key_release(&uq->uq_key);
	if (error == ERESTART)
		error = EINTR;
	return (error);
}
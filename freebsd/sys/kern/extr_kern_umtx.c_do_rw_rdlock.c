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
typedef  long uint32_t ;
struct urwlock {int /*<<< orphan*/  rw_state; int /*<<< orphan*/  rw_blocked_readers; int /*<<< orphan*/  rw_flags; } ;
struct umtx_q {int /*<<< orphan*/  uq_key; } ;
struct thread {struct umtx_q* td_umtxq; } ;
struct abs_timeout {int dummy; } ;
struct _umtx_time {int dummy; } ;
typedef  long int32_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EFAULT ; 
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  GET_SHARE (long) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TYPE_RWLOCK ; 
 scalar_t__ URWLOCK_MAX_READERS ; 
 long URWLOCK_PREFER_READER ; 
 scalar_t__ URWLOCK_READER_COUNT (long) ; 
 long URWLOCK_READ_WAITERS ; 
 long URWLOCK_WRITE_OWNER ; 
 long URWLOCK_WRITE_WAITERS ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  abs_timeout_init2 (struct abs_timeout*,struct _umtx_time*) ; 
 int casueword32 (int /*<<< orphan*/ *,long,long*,long) ; 
 int fueword32 (int /*<<< orphan*/ *,long*) ; 
 int /*<<< orphan*/  suword32 (int /*<<< orphan*/ *,long) ; 
 int umtx_key_get (struct urwlock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_key_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_busy (int /*<<< orphan*/ *) ; 
 int umtxq_check_susp (struct thread*,int) ; 
 int /*<<< orphan*/  umtxq_insert (struct umtx_q*) ; 
 int /*<<< orphan*/  umtxq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_remove (struct umtx_q*) ; 
 int umtxq_sleep (struct umtx_q*,char*,struct abs_timeout*) ; 
 int /*<<< orphan*/  umtxq_unbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unbusy_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
do_rw_rdlock(struct thread *td, struct urwlock *rwlock, long fflag,
    struct _umtx_time *timeout)
{
	struct abs_timeout timo;
	struct umtx_q *uq;
	uint32_t flags, wrflags;
	int32_t state, oldstate;
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

	wrflags = URWLOCK_WRITE_OWNER;
	if (!(fflag & URWLOCK_PREFER_READER) && !(flags & URWLOCK_PREFER_READER))
		wrflags |= URWLOCK_WRITE_WAITERS;

	for (;;) {
		rv = fueword32(&rwlock->rw_state, &state);
		if (rv == -1) {
			umtx_key_release(&uq->uq_key);
			return (EFAULT);
		}

		/* try to lock it */
		while (!(state & wrflags)) {
			if (__predict_false(URWLOCK_READER_COUNT(state) ==
			    URWLOCK_MAX_READERS)) {
				umtx_key_release(&uq->uq_key);
				return (EAGAIN);
			}
			rv = casueword32(&rwlock->rw_state, state,
			    &oldstate, state + 1);
			if (rv == -1) {
				umtx_key_release(&uq->uq_key);
				return (EFAULT);
			}
			if (rv == 0) {
				MPASS(oldstate == state);
				umtx_key_release(&uq->uq_key);
				return (0);
			}
			error = umtxq_check_susp(td, true);
			if (error != 0)
				break;
			state = oldstate;
		}

		if (error)
			break;

		/* grab monitor lock */
		umtxq_lock(&uq->uq_key);
		umtxq_busy(&uq->uq_key);
		umtxq_unlock(&uq->uq_key);

		/*
		 * re-read the state, in case it changed between the try-lock above
		 * and the check below
		 */
		rv = fueword32(&rwlock->rw_state, &state);
		if (rv == -1)
			error = EFAULT;

		/* set read contention bit */
		while (error == 0 && (state & wrflags) &&
		    !(state & URWLOCK_READ_WAITERS)) {
			rv = casueword32(&rwlock->rw_state, state,
			    &oldstate, state | URWLOCK_READ_WAITERS);
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

		/* state is changed while setting flags, restart */
		if (!(state & wrflags)) {
			umtxq_unbusy_unlocked(&uq->uq_key);
			error = umtxq_check_susp(td, true);
			if (error != 0)
				break;
			continue;
		}

sleep:
		/*
		 * Contention bit is set, before sleeping, increase
		 * read waiter count.
		 */
		rv = fueword32(&rwlock->rw_blocked_readers,
		    &blocked_readers);
		if (rv == -1) {
			umtxq_unbusy_unlocked(&uq->uq_key);
			error = EFAULT;
			break;
		}
		suword32(&rwlock->rw_blocked_readers, blocked_readers+1);

		while (state & wrflags) {
			umtxq_lock(&uq->uq_key);
			umtxq_insert(uq);
			umtxq_unbusy(&uq->uq_key);

			error = umtxq_sleep(uq, "urdlck", timeout == NULL ?
			    NULL : &timo);

			umtxq_busy(&uq->uq_key);
			umtxq_remove(uq);
			umtxq_unlock(&uq->uq_key);
			if (error)
				break;
			rv = fueword32(&rwlock->rw_state, &state);
			if (rv == -1) {
				error = EFAULT;
				break;
			}
		}

		/* decrease read waiter count, and may clear read contention bit */
		rv = fueword32(&rwlock->rw_blocked_readers,
		    &blocked_readers);
		if (rv == -1) {
			umtxq_unbusy_unlocked(&uq->uq_key);
			error = EFAULT;
			break;
		}
		suword32(&rwlock->rw_blocked_readers, blocked_readers-1);
		if (blocked_readers == 1) {
			rv = fueword32(&rwlock->rw_state, &state);
			if (rv == -1) {
				umtxq_unbusy_unlocked(&uq->uq_key);
				error = EFAULT;
				break;
			}
			for (;;) {
				rv = casueword32(&rwlock->rw_state, state,
				    &oldstate, state & ~URWLOCK_READ_WAITERS);
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
				if (error1 != 0) {
					if (error == 0)
						error = error1;
					break;
				}
			}
		}

		umtxq_unbusy_unlocked(&uq->uq_key);
		if (error != 0)
			break;
	}
	umtx_key_release(&uq->uq_key);
	if (error == ERESTART)
		error = EINTR;
	return (error);
}
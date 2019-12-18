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
struct umtx_q {int uq_flags; int /*<<< orphan*/  uq_key; } ;
struct thread {struct umtx_q* td_umtxq; } ;
struct abs_timeout {int /*<<< orphan*/  cur; int /*<<< orphan*/  end; } ;
struct _usem2 {int /*<<< orphan*/  _count; int /*<<< orphan*/  _flags; } ;
struct _umtx_time {int _flags; int /*<<< orphan*/  _timeout; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINTR ; 
 int ERESTART ; 
 int /*<<< orphan*/  GET_SHARE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_SEM ; 
 int UMTX_ABSTIME ; 
 int UQF_UMTXQ ; 
 scalar_t__ USEM_COUNT (scalar_t__) ; 
 scalar_t__ USEM_HAS_WAITERS ; 
 int /*<<< orphan*/  abs_timeout_init2 (struct abs_timeout*,struct _umtx_time*) ; 
 int /*<<< orphan*/  abs_timeout_update (struct abs_timeout*) ; 
 int casueword32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__) ; 
 int fueword32 (int /*<<< orphan*/ *,scalar_t__*) ; 
 scalar_t__ fuword32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timespecsub (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int umtx_key_get (struct _usem2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_key_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_busy (int /*<<< orphan*/ *) ; 
 int umtxq_check_susp (struct thread*,int) ; 
 int /*<<< orphan*/  umtxq_insert (struct umtx_q*) ; 
 int /*<<< orphan*/  umtxq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_remove (struct umtx_q*) ; 
 int umtxq_sleep (struct umtx_q*,char*,struct abs_timeout*) ; 
 int /*<<< orphan*/  umtxq_unbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
do_sem2_wait(struct thread *td, struct _usem2 *sem, struct _umtx_time *timeout)
{
	struct abs_timeout timo;
	struct umtx_q *uq;
	uint32_t count, flags;
	int error, rv;

	uq = td->td_umtxq;
	flags = fuword32(&sem->_flags);
	if (timeout != NULL)
		abs_timeout_init2(&timo, timeout);

again:
	error = umtx_key_get(sem, TYPE_SEM, GET_SHARE(flags), &uq->uq_key);
	if (error != 0)
		return (error);
	umtxq_lock(&uq->uq_key);
	umtxq_busy(&uq->uq_key);
	umtxq_insert(uq);
	umtxq_unlock(&uq->uq_key);
	rv = fueword32(&sem->_count, &count);
	if (rv == -1) {
		umtxq_lock(&uq->uq_key);
		umtxq_unbusy(&uq->uq_key);
		umtxq_remove(uq);
		umtxq_unlock(&uq->uq_key);
		umtx_key_release(&uq->uq_key);
		return (EFAULT);
	}
	for (;;) {
		if (USEM_COUNT(count) != 0) {
			umtxq_lock(&uq->uq_key);
			umtxq_unbusy(&uq->uq_key);
			umtxq_remove(uq);
			umtxq_unlock(&uq->uq_key);
			umtx_key_release(&uq->uq_key);
			return (0);
		}
		if (count == USEM_HAS_WAITERS)
			break;
		rv = casueword32(&sem->_count, 0, &count, USEM_HAS_WAITERS);
		if (rv == 0)
			break;
		umtxq_lock(&uq->uq_key);
		umtxq_unbusy(&uq->uq_key);
		umtxq_remove(uq);
		umtxq_unlock(&uq->uq_key);
		umtx_key_release(&uq->uq_key);
		if (rv == -1)
			return (EFAULT);
		rv = umtxq_check_susp(td, true);
		if (rv != 0)
			return (rv);
		goto again;
	}
	umtxq_lock(&uq->uq_key);
	umtxq_unbusy(&uq->uq_key);

	error = umtxq_sleep(uq, "usem", timeout == NULL ? NULL : &timo);

	if ((uq->uq_flags & UQF_UMTXQ) == 0)
		error = 0;
	else {
		umtxq_remove(uq);
		if (timeout != NULL && (timeout->_flags & UMTX_ABSTIME) == 0) {
			/* A relative timeout cannot be restarted. */
			if (error == ERESTART)
				error = EINTR;
			if (error == EINTR) {
				abs_timeout_update(&timo);
				timespecsub(&timo.end, &timo.cur,
				    &timeout->_timeout);
			}
		}
	}
	umtxq_unlock(&uq->uq_key);
	umtx_key_release(&uq->uq_key);
	return (error);
}
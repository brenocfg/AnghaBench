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
typedef  int uint32_t ;
struct umutex {int /*<<< orphan*/  m_owner; } ;
struct umtx_q {int /*<<< orphan*/  uq_key; } ;
struct thread {int td_tid; struct umtx_q* td_umtxq; } ;
struct abs_timeout {int dummy; } ;
struct _umtx_time {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EFAULT ; 
 int ENOTRECOVERABLE ; 
 int EOWNERDEAD ; 
 int /*<<< orphan*/  GET_SHARE (int) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TYPE_NORMAL_UMUTEX ; 
 int UMUTEX_CONTESTED ; 
 int UMUTEX_RB_NOTRECOV ; 
 int UMUTEX_RB_OWNERDEAD ; 
 int UMUTEX_UNOWNED ; 
 int _UMUTEX_TRY ; 
 int _UMUTEX_WAIT ; 
 int /*<<< orphan*/  abs_timeout_init2 (struct abs_timeout*,struct _umtx_time*) ; 
 int casueword32 (int /*<<< orphan*/ *,int,int*,int) ; 
 int fueword32 (int /*<<< orphan*/ *,int*) ; 
 int umtx_key_get (struct umutex*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
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
do_lock_normal(struct thread *td, struct umutex *m, uint32_t flags,
    struct _umtx_time *timeout, int mode)
{
	struct abs_timeout timo;
	struct umtx_q *uq;
	uint32_t owner, old, id;
	int error, rv;

	id = td->td_tid;
	uq = td->td_umtxq;
	error = 0;
	if (timeout != NULL)
		abs_timeout_init2(&timo, timeout);

	/*
	 * Care must be exercised when dealing with umtx structure. It
	 * can fault on any access.
	 */
	for (;;) {
		rv = fueword32(&m->m_owner, &owner);
		if (rv == -1)
			return (EFAULT);
		if (mode == _UMUTEX_WAIT) {
			if (owner == UMUTEX_UNOWNED ||
			    owner == UMUTEX_CONTESTED ||
			    owner == UMUTEX_RB_OWNERDEAD ||
			    owner == UMUTEX_RB_NOTRECOV)
				return (0);
		} else {
			/*
			 * Robust mutex terminated.  Kernel duty is to
			 * return EOWNERDEAD to the userspace.  The
			 * umutex.m_flags UMUTEX_NONCONSISTENT is set
			 * by the common userspace code.
			 */
			if (owner == UMUTEX_RB_OWNERDEAD) {
				rv = casueword32(&m->m_owner,
				    UMUTEX_RB_OWNERDEAD, &owner,
				    id | UMUTEX_CONTESTED);
				if (rv == -1)
					return (EFAULT);
				if (rv == 0) {
					MPASS(owner == UMUTEX_RB_OWNERDEAD);
					return (EOWNERDEAD); /* success */
				}
				MPASS(rv == 1);
				rv = umtxq_check_susp(td, false);
				if (rv != 0)
					return (rv);
				continue;
			}
			if (owner == UMUTEX_RB_NOTRECOV)
				return (ENOTRECOVERABLE);

			/*
			 * Try the uncontested case.  This should be
			 * done in userland.
			 */
			rv = casueword32(&m->m_owner, UMUTEX_UNOWNED,
			    &owner, id);
			/* The address was invalid. */
			if (rv == -1)
				return (EFAULT);

			/* The acquire succeeded. */
			if (rv == 0) {
				MPASS(owner == UMUTEX_UNOWNED);
				return (0);
			}

			/*
			 * If no one owns it but it is contested try
			 * to acquire it.
			 */
			MPASS(rv == 1);
			if (owner == UMUTEX_CONTESTED) {
				rv = casueword32(&m->m_owner,
				    UMUTEX_CONTESTED, &owner,
				    id | UMUTEX_CONTESTED);
				/* The address was invalid. */
				if (rv == -1)
					return (EFAULT);
				if (rv == 0) {
					MPASS(owner == UMUTEX_CONTESTED);
					return (0);
				}
				if (rv == 1) {
					rv = umtxq_check_susp(td, false);
					if (rv != 0)
						return (rv);
				}

				/*
				 * If this failed the lock has
				 * changed, restart.
				 */
				continue;
			}

			/* rv == 1 but not contested, likely store failure */
			rv = umtxq_check_susp(td, false);
			if (rv != 0)
				return (rv);
		}

		if (mode == _UMUTEX_TRY)
			return (EBUSY);

		/*
		 * If we caught a signal, we have retried and now
		 * exit immediately.
		 */
		if (error != 0)
			return (error);

		if ((error = umtx_key_get(m, TYPE_NORMAL_UMUTEX,
		    GET_SHARE(flags), &uq->uq_key)) != 0)
			return (error);

		umtxq_lock(&uq->uq_key);
		umtxq_busy(&uq->uq_key);
		umtxq_insert(uq);
		umtxq_unlock(&uq->uq_key);

		/*
		 * Set the contested bit so that a release in user space
		 * knows to use the system call for unlock.  If this fails
		 * either some one else has acquired the lock or it has been
		 * released.
		 */
		rv = casueword32(&m->m_owner, owner, &old,
		    owner | UMUTEX_CONTESTED);

		/* The address was invalid or casueword failed to store. */
		if (rv == -1 || rv == 1) {
			umtxq_lock(&uq->uq_key);
			umtxq_remove(uq);
			umtxq_unbusy(&uq->uq_key);
			umtxq_unlock(&uq->uq_key);
			umtx_key_release(&uq->uq_key);
			if (rv == -1)
				return (EFAULT);
			if (rv == 1) {
				rv = umtxq_check_susp(td, false);
				if (rv != 0)
					return (rv);
			}
			continue;
		}

		/*
		 * We set the contested bit, sleep. Otherwise the lock changed
		 * and we need to retry or we lost a race to the thread
		 * unlocking the umtx.
		 */
		umtxq_lock(&uq->uq_key);
		umtxq_unbusy(&uq->uq_key);
		MPASS(old == owner);
		error = umtxq_sleep(uq, "umtxn", timeout == NULL ?
		    NULL : &timo);
		umtxq_remove(uq);
		umtxq_unlock(&uq->uq_key);
		umtx_key_release(&uq->uq_key);

		if (error == 0)
			error = umtxq_check_susp(td, false);
	}

	return (0);
}
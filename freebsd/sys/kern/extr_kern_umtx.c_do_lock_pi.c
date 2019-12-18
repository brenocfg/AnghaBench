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
struct umutex {int /*<<< orphan*/  m_owner; } ;
struct umtx_q {int /*<<< orphan*/  uq_key; } ;
struct umtx_pi {int /*<<< orphan*/  pi_key; } ;
struct thread {scalar_t__ td_tid; struct umtx_q* td_umtxq; } ;
struct abs_timeout {int dummy; } ;
struct _umtx_time {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int EDEADLK ; 
 int EFAULT ; 
 int ENOTRECOVERABLE ; 
 int EOWNERDEAD ; 
 int /*<<< orphan*/  GET_SHARE (scalar_t__) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  TYPE_PI_ROBUST_UMUTEX ; 
 int /*<<< orphan*/  TYPE_PI_UMUTEX ; 
 scalar_t__ UMUTEX_CONTESTED ; 
 scalar_t__ UMUTEX_RB_NOTRECOV ; 
 scalar_t__ UMUTEX_RB_OWNERDEAD ; 
 scalar_t__ UMUTEX_ROBUST ; 
 scalar_t__ UMUTEX_UNOWNED ; 
 scalar_t__ USYNC_PROCESS_SHARED ; 
 int /*<<< orphan*/  abs_timeout_init2 (struct abs_timeout*,struct _umtx_time*) ; 
 int casueword32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  casuword32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int umtx_key_get (struct umutex*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_key_release (int /*<<< orphan*/ *) ; 
 struct umtx_pi* umtx_pi_alloc (int /*<<< orphan*/ ) ; 
 int umtx_pi_claim (struct umtx_pi*,struct thread*) ; 
 int /*<<< orphan*/  umtx_pi_free (struct umtx_pi*) ; 
 int /*<<< orphan*/  umtx_pi_insert (struct umtx_pi*) ; 
 struct umtx_pi* umtx_pi_lookup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_pi_ref (struct umtx_pi*) ; 
 int /*<<< orphan*/  umtx_pi_unref (struct umtx_pi*) ; 
 int /*<<< orphan*/  umtxq_busy (int /*<<< orphan*/ *) ; 
 int umtxq_check_susp (struct thread*,int) ; 
 int /*<<< orphan*/  umtxq_lock (int /*<<< orphan*/ *) ; 
 int umtxq_sleep_pi (struct umtx_q*,struct umtx_pi*,scalar_t__,char*,struct abs_timeout*,int) ; 
 int /*<<< orphan*/  umtxq_unbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unbusy_unlocked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
do_lock_pi(struct thread *td, struct umutex *m, uint32_t flags,
    struct _umtx_time *timeout, int try)
{
	struct abs_timeout timo;
	struct umtx_q *uq;
	struct umtx_pi *pi, *new_pi;
	uint32_t id, old_owner, owner, old;
	int error, rv;

	id = td->td_tid;
	uq = td->td_umtxq;

	if ((error = umtx_key_get(m, (flags & UMUTEX_ROBUST) != 0 ?
	    TYPE_PI_ROBUST_UMUTEX : TYPE_PI_UMUTEX, GET_SHARE(flags),
	    &uq->uq_key)) != 0)
		return (error);

	if (timeout != NULL)
		abs_timeout_init2(&timo, timeout);

	umtxq_lock(&uq->uq_key);
	pi = umtx_pi_lookup(&uq->uq_key);
	if (pi == NULL) {
		new_pi = umtx_pi_alloc(M_NOWAIT);
		if (new_pi == NULL) {
			umtxq_unlock(&uq->uq_key);
			new_pi = umtx_pi_alloc(M_WAITOK);
			umtxq_lock(&uq->uq_key);
			pi = umtx_pi_lookup(&uq->uq_key);
			if (pi != NULL) {
				umtx_pi_free(new_pi);
				new_pi = NULL;
			}
		}
		if (new_pi != NULL) {
			new_pi->pi_key = uq->uq_key;
			umtx_pi_insert(new_pi);
			pi = new_pi;
		}
	}
	umtx_pi_ref(pi);
	umtxq_unlock(&uq->uq_key);

	/*
	 * Care must be exercised when dealing with umtx structure.  It
	 * can fault on any access.
	 */
	for (;;) {
		/*
		 * Try the uncontested case.  This should be done in userland.
		 */
		rv = casueword32(&m->m_owner, UMUTEX_UNOWNED, &owner, id);
		/* The address was invalid. */
		if (rv == -1) {
			error = EFAULT;
			break;
		}
		/* The acquire succeeded. */
		if (rv == 0) {
			MPASS(owner == UMUTEX_UNOWNED);
			error = 0;
			break;
		}

		if (owner == UMUTEX_RB_NOTRECOV) {
			error = ENOTRECOVERABLE;
			break;
		}

		/*
		 * Avoid overwriting a possible error from sleep due
		 * to the pending signal with suspension check result.
		 */
		if (error == 0) {
			error = umtxq_check_susp(td, true);
			if (error != 0)
				break;
		}

		/* If no one owns it but it is contested try to acquire it. */
		if (owner == UMUTEX_CONTESTED || owner == UMUTEX_RB_OWNERDEAD) {
			old_owner = owner;
			rv = casueword32(&m->m_owner, owner, &owner,
			    id | UMUTEX_CONTESTED);
			/* The address was invalid. */
			if (rv == -1) {
				error = EFAULT;
				break;
			}
			if (rv == 1) {
				if (error == 0) {
					error = umtxq_check_susp(td, true);
					if (error != 0)
						break;
				}

				/*
				 * If this failed the lock could
				 * changed, restart.
				 */
				continue;
			}

			MPASS(rv == 0);
			MPASS(owner == old_owner);
			umtxq_lock(&uq->uq_key);
			umtxq_busy(&uq->uq_key);
			error = umtx_pi_claim(pi, td);
			umtxq_unbusy(&uq->uq_key);
			umtxq_unlock(&uq->uq_key);
			if (error != 0) {
				/*
				 * Since we're going to return an
				 * error, restore the m_owner to its
				 * previous, unowned state to avoid
				 * compounding the problem.
				 */
				(void)casuword32(&m->m_owner,
				    id | UMUTEX_CONTESTED, old_owner);
			}
			if (error == 0 && old_owner == UMUTEX_RB_OWNERDEAD)
				error = EOWNERDEAD;
			break;
		}

		if ((owner & ~UMUTEX_CONTESTED) == id) {
			error = EDEADLK;
			break;
		}

		if (try != 0) {
			error = EBUSY;
			break;
		}

		/*
		 * If we caught a signal, we have retried and now
		 * exit immediately.
		 */
		if (error != 0)
			break;
			
		umtxq_lock(&uq->uq_key);
		umtxq_busy(&uq->uq_key);
		umtxq_unlock(&uq->uq_key);

		/*
		 * Set the contested bit so that a release in user space
		 * knows to use the system call for unlock.  If this fails
		 * either some one else has acquired the lock or it has been
		 * released.
		 */
		rv = casueword32(&m->m_owner, owner, &old, owner |
		    UMUTEX_CONTESTED);

		/* The address was invalid. */
		if (rv == -1) {
			umtxq_unbusy_unlocked(&uq->uq_key);
			error = EFAULT;
			break;
		}
		if (rv == 1) {
			umtxq_unbusy_unlocked(&uq->uq_key);
			error = umtxq_check_susp(td, true);
			if (error != 0)
				break;

			/*
			 * The lock changed and we need to retry or we
			 * lost a race to the thread unlocking the
			 * umtx.  Note that the UMUTEX_RB_OWNERDEAD
			 * value for owner is impossible there.
			 */
			continue;
		}

		umtxq_lock(&uq->uq_key);

		/* We set the contested bit, sleep. */
		MPASS(old == owner);
		error = umtxq_sleep_pi(uq, pi, owner & ~UMUTEX_CONTESTED,
		    "umtxpi", timeout == NULL ? NULL : &timo,
		    (flags & USYNC_PROCESS_SHARED) != 0);
		if (error != 0)
			continue;

		error = umtxq_check_susp(td, false);
		if (error != 0)
			break;
	}

	umtxq_lock(&uq->uq_key);
	umtx_pi_unref(pi);
	umtxq_unlock(&uq->uq_key);

	umtx_key_release(&uq->uq_key);
	return (error);
}
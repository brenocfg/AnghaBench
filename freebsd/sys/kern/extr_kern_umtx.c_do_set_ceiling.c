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
struct umutex {int m_flags; int* m_ceilings; int m_owner; } ;
struct umtx_q {int /*<<< orphan*/  uq_key; } ;
struct thread {int td_tid; struct umtx_q* td_umtxq; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int ENOTRECOVERABLE ; 
 int EOWNERDEAD ; 
 int /*<<< orphan*/  GET_SHARE (int) ; 
 int /*<<< orphan*/  INT_MAX ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int RTP_PRIO_MAX ; 
 int /*<<< orphan*/  TYPE_PP_ROBUST_UMUTEX ; 
 int /*<<< orphan*/  TYPE_PP_UMUTEX ; 
 int UMUTEX_CONTESTED ; 
 int UMUTEX_PRIO_PROTECT ; 
 int UMUTEX_RB_NOTRECOV ; 
 int UMUTEX_RB_OWNERDEAD ; 
 int UMUTEX_ROBUST ; 
 int casueword32 (int*,int,int*,int) ; 
 int fueword32 (int*,int*) ; 
 int suword32 (int*,int) ; 
 int umtx_key_get (struct umutex*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtx_key_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_busy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_insert (struct umtx_q*) ; 
 int /*<<< orphan*/  umtxq_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_remove (struct umtx_q*) ; 
 int /*<<< orphan*/  umtxq_signal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int umtxq_sleep (struct umtx_q*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unbusy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umtxq_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
do_set_ceiling(struct thread *td, struct umutex *m, uint32_t ceiling,
    uint32_t *old_ceiling)
{
	struct umtx_q *uq;
	uint32_t flags, id, owner, save_ceiling;
	int error, rv, rv1;

	error = fueword32(&m->m_flags, &flags);
	if (error == -1)
		return (EFAULT);
	if ((flags & UMUTEX_PRIO_PROTECT) == 0)
		return (EINVAL);
	if (ceiling > RTP_PRIO_MAX)
		return (EINVAL);
	id = td->td_tid;
	uq = td->td_umtxq;
	if ((error = umtx_key_get(m, (flags & UMUTEX_ROBUST) != 0 ?
	    TYPE_PP_ROBUST_UMUTEX : TYPE_PP_UMUTEX, GET_SHARE(flags),
	    &uq->uq_key)) != 0)
		return (error);
	for (;;) {
		umtxq_lock(&uq->uq_key);
		umtxq_busy(&uq->uq_key);
		umtxq_unlock(&uq->uq_key);

		rv = fueword32(&m->m_ceilings[0], &save_ceiling);
		if (rv == -1) {
			error = EFAULT;
			break;
		}

		rv = casueword32(&m->m_owner, UMUTEX_CONTESTED, &owner,
		    id | UMUTEX_CONTESTED);
		if (rv == -1) {
			error = EFAULT;
			break;
		}

		if (rv == 0) {
			MPASS(owner == UMUTEX_CONTESTED);
			rv = suword32(&m->m_ceilings[0], ceiling);
			rv1 = suword32(&m->m_owner, UMUTEX_CONTESTED);
			error = (rv == 0 && rv1 == 0) ? 0: EFAULT;
			break;
		}

		if ((owner & ~UMUTEX_CONTESTED) == id) {
			rv = suword32(&m->m_ceilings[0], ceiling);
			error = rv == 0 ? 0 : EFAULT;
			break;
		}

		if (owner == UMUTEX_RB_OWNERDEAD) {
			error = EOWNERDEAD;
			break;
		} else if (owner == UMUTEX_RB_NOTRECOV) {
			error = ENOTRECOVERABLE;
			break;
		}

		/*
		 * If we caught a signal, we have retried and now
		 * exit immediately.
		 */
		if (error != 0)
			break;

		/*
		 * We set the contested bit, sleep. Otherwise the lock changed
		 * and we need to retry or we lost a race to the thread
		 * unlocking the umtx.
		 */
		umtxq_lock(&uq->uq_key);
		umtxq_insert(uq);
		umtxq_unbusy(&uq->uq_key);
		error = umtxq_sleep(uq, "umtxpp", NULL);
		umtxq_remove(uq);
		umtxq_unlock(&uq->uq_key);
	}
	umtxq_lock(&uq->uq_key);
	if (error == 0)
		umtxq_signal(&uq->uq_key, INT_MAX);
	umtxq_unbusy(&uq->uq_key);
	umtxq_unlock(&uq->uq_key);
	umtx_key_release(&uq->uq_key);
	if (error == 0 && old_ceiling != NULL) {
		rv = suword32(old_ceiling, save_ceiling);
		error = rv == 0 ? 0 : EFAULT;
	}
	return (error);
}
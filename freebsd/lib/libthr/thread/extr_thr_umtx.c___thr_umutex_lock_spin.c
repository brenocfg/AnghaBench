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
struct umutex {int m_flags; int m_owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SPINWAIT ; 
 int ENOTRECOVERABLE ; 
 int EOWNERDEAD ; 
 int SPINLOOPS ; 
 int /*<<< orphan*/  UMTX_OP_MUTEX_LOCK ; 
 int /*<<< orphan*/  UMTX_OP_MUTEX_WAIT ; 
 int UMUTEX_CONTESTED ; 
 int UMUTEX_PRIO_INHERIT ; 
 int UMUTEX_PRIO_PROTECT ; 
 int UMUTEX_RB_NOTRECOV ; 
 int UMUTEX_RB_OWNERDEAD ; 
 scalar_t__ __predict_false (int) ; 
 int __thr_umutex_lock (struct umutex*,int) ; 
 int /*<<< orphan*/  _thr_is_smp ; 
 int _umtx_op_err (struct umutex*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_cmpset_acq_32 (int*,int,int) ; 

int
__thr_umutex_lock_spin(struct umutex *mtx, uint32_t id)
{
	uint32_t owner;
	int count;

	if (!_thr_is_smp)
		return (__thr_umutex_lock(mtx, id));
	if ((mtx->m_flags & (UMUTEX_PRIO_PROTECT | UMUTEX_PRIO_INHERIT)) != 0)
		return	(_umtx_op_err(mtx, UMTX_OP_MUTEX_LOCK, 0, 0, 0));

	for (;;) {
		count = SPINLOOPS;
		while (count--) {
			owner = mtx->m_owner;
			if ((owner & ~UMUTEX_CONTESTED) == 0 &&
			    atomic_cmpset_acq_32(&mtx->m_owner, owner,
			    id | owner))
				return (0);
			if (__predict_false(owner == UMUTEX_RB_OWNERDEAD) &&
			    atomic_cmpset_acq_32(&mtx->m_owner, owner,
			    id | UMUTEX_CONTESTED))
				return (EOWNERDEAD);
			if (__predict_false(owner == UMUTEX_RB_NOTRECOV))
				return (ENOTRECOVERABLE);
			CPU_SPINWAIT;
		}

		/* wait in kernel */
		_umtx_op_err(mtx, UMTX_OP_MUTEX_WAIT, 0, 0, 0);
	}
}
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
struct umutex {int m_flags; scalar_t__ m_owner; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOTRECOVERABLE ; 
 int EOWNERDEAD ; 
 scalar_t__ UMUTEX_CONTESTED ; 
 int UMUTEX_PRIO_PROTECT ; 
 scalar_t__ UMUTEX_RB_NOTRECOV ; 
 scalar_t__ UMUTEX_RB_OWNERDEAD ; 
 scalar_t__ UMUTEX_UNOWNED ; 
 scalar_t__ __predict_false (int) ; 
 int __thr_umutex_trylock (struct umutex*) ; 
 scalar_t__ atomic_cmpset_acq_32 (scalar_t__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int
_thr_umutex_trylock(struct umutex *mtx, uint32_t id)
{

	if (atomic_cmpset_acq_32(&mtx->m_owner, UMUTEX_UNOWNED, id))
		return (0);
	if (__predict_false((uint32_t)mtx->m_owner == UMUTEX_RB_OWNERDEAD) &&
	    atomic_cmpset_acq_32(&mtx->m_owner, UMUTEX_RB_OWNERDEAD,
	    id | UMUTEX_CONTESTED))
		return (EOWNERDEAD);
	if (__predict_false((uint32_t)mtx->m_owner == UMUTEX_RB_NOTRECOV))
		return (ENOTRECOVERABLE);
	if ((mtx->m_flags & UMUTEX_PRIO_PROTECT) == 0)
		return (EBUSY);
	return (__thr_umutex_trylock(mtx));
}
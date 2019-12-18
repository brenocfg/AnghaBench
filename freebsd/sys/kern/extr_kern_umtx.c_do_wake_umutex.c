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
struct umutex {int /*<<< orphan*/  m_owner; int /*<<< orphan*/  m_flags; } ;
struct umtx_key {int dummy; } ;
struct thread {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  GET_SHARE (int) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TYPE_NORMAL_UMUTEX ; 
 int UMUTEX_CONTESTED ; 
 int UMUTEX_RB_NOTRECOV ; 
 int UMUTEX_RB_OWNERDEAD ; 
 int /*<<< orphan*/  UMUTEX_UNOWNED ; 
 int casueword32 (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int fueword32 (int /*<<< orphan*/ *,int*) ; 
 int umtx_key_get (struct umutex*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umtx_key*) ; 
 int /*<<< orphan*/  umtx_key_release (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_busy (struct umtx_key*) ; 
 int umtxq_check_susp (struct thread*,int) ; 
 int umtxq_count (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_lock (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_signal (struct umtx_key*,int) ; 
 int /*<<< orphan*/  umtxq_unbusy (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_unlock (struct umtx_key*) ; 

__attribute__((used)) static int
do_wake_umutex(struct thread *td, struct umutex *m)
{
	struct umtx_key key;
	uint32_t owner;
	uint32_t flags;
	int error;
	int count;

again:
	error = fueword32(&m->m_owner, &owner);
	if (error == -1)
		return (EFAULT);

	if ((owner & ~UMUTEX_CONTESTED) != 0 && owner != UMUTEX_RB_OWNERDEAD &&
	    owner != UMUTEX_RB_NOTRECOV)
		return (0);

	error = fueword32(&m->m_flags, &flags);
	if (error == -1)
		return (EFAULT);

	/* We should only ever be in here for contested locks */
	if ((error = umtx_key_get(m, TYPE_NORMAL_UMUTEX, GET_SHARE(flags),
	    &key)) != 0)
		return (error);

	umtxq_lock(&key);
	umtxq_busy(&key);
	count = umtxq_count(&key);
	umtxq_unlock(&key);

	if (count <= 1 && owner != UMUTEX_RB_OWNERDEAD &&
	    owner != UMUTEX_RB_NOTRECOV) {
		error = casueword32(&m->m_owner, UMUTEX_CONTESTED, &owner,
		    UMUTEX_UNOWNED);
		if (error == -1) {
			error = EFAULT;
		} else if (error == 1) {
			umtxq_lock(&key);
			umtxq_unbusy(&key);
			umtxq_unlock(&key);
			umtx_key_release(&key);
			error = umtxq_check_susp(td, false);
			if (error != 0)
				return (error);
			goto again;
		}
	}

	umtxq_lock(&key);
	if (error == 0 && count != 0) {
		MPASS((owner & ~UMUTEX_CONTESTED) == 0 ||
		    owner == UMUTEX_RB_OWNERDEAD ||
		    owner == UMUTEX_RB_NOTRECOV);
		umtxq_signal(&key, 1);
	}
	umtxq_unbusy(&key);
	umtxq_unlock(&key);
	umtx_key_release(&key);
	return (error);
}
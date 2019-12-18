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
struct umtx_key {int dummy; } ;
struct thread {int td_tid; } ;

/* Variables and functions */
 int EFAULT ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  GET_SHARE (int) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  TYPE_NORMAL_UMUTEX ; 
 int UMUTEX_CONTESTED ; 
 int casueword32 (int /*<<< orphan*/ *,int,int*,int) ; 
 int fueword32 (int /*<<< orphan*/ *,int*) ; 
 int umtx_key_get (struct umutex*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umtx_key*) ; 
 int /*<<< orphan*/  umtx_key_release (struct umtx_key*) ; 
 int umtx_unlock_val (int,int) ; 
 int /*<<< orphan*/  umtxq_busy (struct umtx_key*) ; 
 int umtxq_check_susp (struct thread*,int) ; 
 int umtxq_count (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_lock (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_signal (struct umtx_key*,int) ; 
 int /*<<< orphan*/  umtxq_unbusy (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_unlock (struct umtx_key*) ; 

__attribute__((used)) static int
do_unlock_normal(struct thread *td, struct umutex *m, uint32_t flags, bool rb)
{
	struct umtx_key key;
	uint32_t owner, old, id, newlock;
	int error, count;

	id = td->td_tid;

again:
	/*
	 * Make sure we own this mtx.
	 */
	error = fueword32(&m->m_owner, &owner);
	if (error == -1)
		return (EFAULT);

	if ((owner & ~UMUTEX_CONTESTED) != id)
		return (EPERM);

	newlock = umtx_unlock_val(flags, rb);
	if ((owner & UMUTEX_CONTESTED) == 0) {
		error = casueword32(&m->m_owner, owner, &old, newlock);
		if (error == -1)
			return (EFAULT);
		if (error == 1) {
			error = umtxq_check_susp(td, false);
			if (error != 0)
				return (error);
			goto again;
		}
		MPASS(old == owner);
		return (0);
	}

	/* We should only ever be in here for contested locks */
	if ((error = umtx_key_get(m, TYPE_NORMAL_UMUTEX, GET_SHARE(flags),
	    &key)) != 0)
		return (error);

	umtxq_lock(&key);
	umtxq_busy(&key);
	count = umtxq_count(&key);
	umtxq_unlock(&key);

	/*
	 * When unlocking the umtx, it must be marked as unowned if
	 * there is zero or one thread only waiting for it.
	 * Otherwise, it must be marked as contested.
	 */
	if (count > 1)
		newlock |= UMUTEX_CONTESTED;
	error = casueword32(&m->m_owner, owner, &old, newlock);
	umtxq_lock(&key);
	umtxq_signal(&key, 1);
	umtxq_unbusy(&key);
	umtxq_unlock(&key);
	umtx_key_release(&key);
	if (error == -1)
		return (EFAULT);
	if (error == 1) {
		if (old != owner)
			return (EINVAL);
		error = umtxq_check_susp(td, false);
		if (error != 0)
			return (error);
		goto again;
	}
	return (0);
}
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
struct umtx_key {int dummy; } ;
struct thread {int dummy; } ;
struct _usem2 {int /*<<< orphan*/  _count; int /*<<< orphan*/  _flags; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  GET_SHARE (int) ; 
 int /*<<< orphan*/  TYPE_SEM ; 
 int USEM_HAS_WAITERS ; 
 int casueword32 (int /*<<< orphan*/ *,int,int*,int) ; 
 int fueword32 (int /*<<< orphan*/ *,int*) ; 
 int umtx_key_get (struct _usem2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct umtx_key*) ; 
 int /*<<< orphan*/  umtx_key_release (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_busy (struct umtx_key*) ; 
 int umtxq_check_susp (struct thread*,int) ; 
 int umtxq_count (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_lock (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_signal (struct umtx_key*,int) ; 
 int /*<<< orphan*/  umtxq_unbusy (struct umtx_key*) ; 
 int /*<<< orphan*/  umtxq_unlock (struct umtx_key*) ; 

__attribute__((used)) static int
do_sem2_wake(struct thread *td, struct _usem2 *sem)
{
	struct umtx_key key;
	int error, cnt, rv;
	uint32_t count, flags;

	rv = fueword32(&sem->_flags, &flags);
	if (rv == -1)
		return (EFAULT);
	if ((error = umtx_key_get(sem, TYPE_SEM, GET_SHARE(flags), &key)) != 0)
		return (error);	
	umtxq_lock(&key);
	umtxq_busy(&key);
	cnt = umtxq_count(&key);
	if (cnt > 0) {
		/*
		 * If this was the last sleeping thread, clear the waiters
		 * flag in _count.
		 */
		if (cnt == 1) {
			umtxq_unlock(&key);
			rv = fueword32(&sem->_count, &count);
			while (rv != -1 && count & USEM_HAS_WAITERS) {
				rv = casueword32(&sem->_count, count, &count,
				    count & ~USEM_HAS_WAITERS);
				if (rv == 1) {
					rv = umtxq_check_susp(td, true);
					if (rv != 0)
						break;
				}
			}
			if (rv == -1)
				error = EFAULT;
			else if (rv > 0) {
				error = rv;
			}
			umtxq_lock(&key);
		}

		umtxq_signal(&key, 1);
	}
	umtxq_unbusy(&key);
	umtxq_unlock(&key);
	umtx_key_release(&key);
	return (error);
}
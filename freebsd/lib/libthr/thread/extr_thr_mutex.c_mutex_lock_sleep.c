#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct timespec {int tv_nsec; } ;
struct TYPE_3__ {int m_flags; int m_owner; } ;
struct pthread_mutex {int m_spinloops; int m_yieldloops; TYPE_1__ m_lock; } ;
struct pthread {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SPINWAIT ; 
 int EINVAL ; 
 int EOWNERDEAD ; 
 int PMUTEX_OWNER_ID (struct pthread_mutex*) ; 
 int TID (struct pthread*) ; 
 int UMUTEX_CONTESTED ; 
 int UMUTEX_NONCONSISTENT ; 
 int UMUTEX_PRIO_INHERIT ; 
 int UMUTEX_PRIO_PROTECT ; 
 int UMUTEX_ROBUST ; 
 scalar_t__ __predict_false (int) ; 
 int __thr_umutex_lock (TYPE_1__*,int) ; 
 int __thr_umutex_timedlock (TYPE_1__*,int,struct timespec const*) ; 
 int /*<<< orphan*/  _sched_yield () ; 
 int /*<<< orphan*/  _thr_is_smp ; 
 scalar_t__ atomic_cmpset_acq_32 (int*,int,int) ; 
 int /*<<< orphan*/  enqueue_mutex (struct pthread*,struct pthread_mutex*,int) ; 
 int mutex_self_lock (struct pthread_mutex*,struct timespec const*) ; 

__attribute__((used)) static int
mutex_lock_sleep(struct pthread *curthread, struct pthread_mutex *m,
    const struct timespec *abstime)
{
	uint32_t id, owner;
	int count, ret;

	id = TID(curthread);
	if (PMUTEX_OWNER_ID(m) == id)
		return (mutex_self_lock(m, abstime));

	/*
	 * For adaptive mutexes, spin for a bit in the expectation
	 * that if the application requests this mutex type then
	 * the lock is likely to be released quickly and it is
	 * faster than entering the kernel
	 */
	if (__predict_false((m->m_lock.m_flags & (UMUTEX_PRIO_PROTECT |
	    UMUTEX_PRIO_INHERIT | UMUTEX_ROBUST | UMUTEX_NONCONSISTENT)) != 0))
		goto sleep_in_kernel;

	if (!_thr_is_smp)
		goto yield_loop;

	count = m->m_spinloops;
	while (count--) {
		owner = m->m_lock.m_owner;
		if ((owner & ~UMUTEX_CONTESTED) == 0) {
			if (atomic_cmpset_acq_32(&m->m_lock.m_owner, owner,
			    id | owner)) {
				ret = 0;
				goto done;
			}
		}
		CPU_SPINWAIT;
	}

yield_loop:
	count = m->m_yieldloops;
	while (count--) {
		_sched_yield();
		owner = m->m_lock.m_owner;
		if ((owner & ~UMUTEX_CONTESTED) == 0) {
			if (atomic_cmpset_acq_32(&m->m_lock.m_owner, owner,
			    id | owner)) {
				ret = 0;
				goto done;
			}
		}
	}

sleep_in_kernel:
	if (abstime == NULL)
		ret = __thr_umutex_lock(&m->m_lock, id);
	else if (__predict_false(abstime->tv_nsec < 0 ||
	    abstime->tv_nsec >= 1000000000))
		ret = EINVAL;
	else
		ret = __thr_umutex_timedlock(&m->m_lock, id, abstime);
done:
	if (ret == 0 || ret == EOWNERDEAD) {
		enqueue_mutex(curthread, m, ret);
		if (ret == EOWNERDEAD)
			m->m_lock.m_flags |= UMUTEX_NONCONSISTENT;
	}
	return (ret);
}
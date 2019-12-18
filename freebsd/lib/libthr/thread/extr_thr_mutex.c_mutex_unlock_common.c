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
struct pthread_mutex {int m_flags; scalar_t__ m_count; int /*<<< orphan*/  m_lock; } ;
struct pthread {scalar_t__ nwaiter_defer; int /*<<< orphan*/  defer_waiters; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int PMUTEX_FLAG_DEFERRED ; 
 int PMUTEX_FLAG_PRIVATE ; 
 scalar_t__ PMUTEX_OWNER_ID (struct pthread_mutex*) ; 
 scalar_t__ PMUTEX_TYPE (int) ; 
 scalar_t__ PTHREAD_MUTEX_RECURSIVE ; 
 int /*<<< orphan*/  THR_CRITICAL_LEAVE (struct pthread*) ; 
 struct pthread_mutex* THR_MUTEX_DESTROYED ; 
 scalar_t__ TID (struct pthread*) ; 
 scalar_t__ __predict_false (int) ; 
 struct pthread* _get_curthread () ; 
 int _mutex_enter_robust (struct pthread*,struct pthread_mutex*) ; 
 int /*<<< orphan*/  _mutex_leave_robust (struct pthread*,struct pthread_mutex*) ; 
 int _thr_umutex_unlock2 (int /*<<< orphan*/ *,scalar_t__,int*) ; 
 int /*<<< orphan*/  _thr_wake_all (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dequeue_mutex (struct pthread*,struct pthread_mutex*) ; 

__attribute__((used)) static int
mutex_unlock_common(struct pthread_mutex *m, bool cv, int *mtx_defer)
{
	struct pthread *curthread;
	uint32_t id;
	int deferred, error, private, robust;

	if (__predict_false(m <= THR_MUTEX_DESTROYED)) {
		if (m == THR_MUTEX_DESTROYED)
			return (EINVAL);
		return (EPERM);
	}

	curthread = _get_curthread();
	id = TID(curthread);

	/*
	 * Check if the running thread is not the owner of the mutex.
	 */
	if (__predict_false(PMUTEX_OWNER_ID(m) != id))
		return (EPERM);

	error = 0;
	private = (m->m_flags & PMUTEX_FLAG_PRIVATE) != 0;
	if (__predict_false(PMUTEX_TYPE(m->m_flags) ==
	    PTHREAD_MUTEX_RECURSIVE && m->m_count > 0)) {
		m->m_count--;
	} else {
		if ((m->m_flags & PMUTEX_FLAG_DEFERRED) != 0) {
			deferred = 1;
			m->m_flags &= ~PMUTEX_FLAG_DEFERRED;
        	} else
			deferred = 0;

		robust = _mutex_enter_robust(curthread, m);
		dequeue_mutex(curthread, m);
		error = _thr_umutex_unlock2(&m->m_lock, id, mtx_defer);
		if (deferred)  {
			if (mtx_defer == NULL) {
				_thr_wake_all(curthread->defer_waiters,
				    curthread->nwaiter_defer);
				curthread->nwaiter_defer = 0;
			} else
				*mtx_defer = 1;
		}
		if (robust)
			_mutex_leave_robust(curthread, m);
	}
	if (!cv && private)
		THR_CRITICAL_LEAVE(curthread);
	return (error);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  m_flags; } ;
struct pthread_mutex {int m_flags; TYPE_1__ m_lock; } ;
struct pthread {int dummy; } ;
typedef  int /*<<< orphan*/  pthread_mutex_t ;

/* Variables and functions */
 int EOWNERDEAD ; 
 int PMUTEX_FLAG_PRIVATE ; 
 scalar_t__ PMUTEX_OWNER_ID (struct pthread_mutex*) ; 
 int /*<<< orphan*/  THR_CRITICAL_ENTER (struct pthread*) ; 
 int /*<<< orphan*/  THR_CRITICAL_LEAVE (struct pthread*) ; 
 scalar_t__ TID (struct pthread*) ; 
 int /*<<< orphan*/  UMUTEX_NONCONSISTENT ; 
 scalar_t__ __predict_true (int) ; 
 struct pthread* _get_curthread () ; 
 int _mutex_enter_robust (struct pthread*,struct pthread_mutex*) ; 
 int /*<<< orphan*/  _mutex_leave_robust (struct pthread*,struct pthread_mutex*) ; 
 int _thr_umutex_trylock (TYPE_1__*,scalar_t__) ; 
 int check_and_init_mutex (int /*<<< orphan*/ *,struct pthread_mutex**) ; 
 int /*<<< orphan*/  enqueue_mutex (struct pthread*,struct pthread_mutex*,int) ; 
 int mutex_self_trylock (struct pthread_mutex*) ; 

int
__Tthr_mutex_trylock(pthread_mutex_t *mutex)
{
	struct pthread *curthread;
	struct pthread_mutex *m;
	uint32_t id;
	int ret, robust;

	ret = check_and_init_mutex(mutex, &m);
	if (ret != 0)
		return (ret);
	curthread = _get_curthread();
	id = TID(curthread);
	if (m->m_flags & PMUTEX_FLAG_PRIVATE)
		THR_CRITICAL_ENTER(curthread);
	robust = _mutex_enter_robust(curthread, m);
	ret = _thr_umutex_trylock(&m->m_lock, id);
	if (__predict_true(ret == 0) || ret == EOWNERDEAD) {
		enqueue_mutex(curthread, m, ret);
		if (ret == EOWNERDEAD)
			m->m_lock.m_flags |= UMUTEX_NONCONSISTENT;
	} else if (PMUTEX_OWNER_ID(m) == id) {
		ret = mutex_self_trylock(m);
	} /* else {} */
	if (robust)
		_mutex_leave_robust(curthread, m);
	if (ret != 0 && ret != EOWNERDEAD &&
	    (m->m_flags & PMUTEX_FLAG_PRIVATE) != 0)
		THR_CRITICAL_LEAVE(curthread);
	return (ret);
}
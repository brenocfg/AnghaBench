#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct sleepqueue {int dummy; } ;
struct TYPE_4__ {int m_owner; int /*<<< orphan*/  m_flags; } ;
struct pthread_mutex {TYPE_2__ m_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  c_clockid; } ;
struct pthread_cond {int __has_user_waiters; TYPE_1__ kcond; } ;
struct pthread {scalar_t__ nwaiter_defer; struct pthread_mutex* mutex_obj; int /*<<< orphan*/ * wchan; int /*<<< orphan*/  defer_waiters; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PANIC (char*,struct pthread*) ; 
 int /*<<< orphan*/  PTHREAD_CANCELED ; 
 scalar_t__ SHOULD_CANCEL (struct pthread*) ; 
 int /*<<< orphan*/  THR_IN_CRITICAL (struct pthread*) ; 
 int /*<<< orphan*/  UMTX_OP_MUTEX_WAKE2 ; 
 int UMUTEX_CONTESTED ; 
 struct pthread* _get_curthread () ; 
 int _mutex_cv_lock (struct pthread_mutex*,int,int) ; 
 int /*<<< orphan*/  _mutex_cv_unlock (struct pthread_mutex*,int*,int*) ; 
 int /*<<< orphan*/  _pthread_exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _sleepq_add (struct pthread_cond*,struct pthread*) ; 
 int /*<<< orphan*/  _sleepq_lock (struct pthread_cond*) ; 
 struct sleepqueue* _sleepq_lookup (struct pthread_cond*) ; 
 void* _sleepq_remove (struct sleepqueue*,struct pthread*) ; 
 int /*<<< orphan*/  _sleepq_unlock (struct pthread_cond*) ; 
 int /*<<< orphan*/  _thr_cancel_enter2 (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _thr_clear_wake (struct pthread*) ; 
 int _thr_sleep (struct pthread*,int /*<<< orphan*/ ,struct timespec const*) ; 
 int /*<<< orphan*/  _thr_testcancel (struct pthread*) ; 
 int /*<<< orphan*/  _thr_wake_all (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  _umtx_op_err (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cond_wait_user(struct pthread_cond *cvp, struct pthread_mutex *mp,
    const struct timespec *abstime, int cancel)
{
	struct pthread *curthread;
	struct sleepqueue *sq;
	int deferred, error, error2, recurse;

	curthread = _get_curthread();
	if (curthread->wchan != NULL)
		PANIC("thread %p was already on queue.", curthread);

	if (cancel)
		_thr_testcancel(curthread);

	_sleepq_lock(cvp);
	/*
	 * set __has_user_waiters before unlocking mutex, this allows
	 * us to check it without locking in pthread_cond_signal().
	 */
	cvp->__has_user_waiters = 1; 
	deferred = 0;
	(void)_mutex_cv_unlock(mp, &recurse, &deferred);
	curthread->mutex_obj = mp;
	_sleepq_add(cvp, curthread);
	for(;;) {
		_thr_clear_wake(curthread);
		_sleepq_unlock(cvp);
		if (deferred) {
			deferred = 0;
			if ((mp->m_lock.m_owner & UMUTEX_CONTESTED) == 0)
				(void)_umtx_op_err(&mp->m_lock,
				    UMTX_OP_MUTEX_WAKE2, mp->m_lock.m_flags,
				    0, 0);
		}
		if (curthread->nwaiter_defer > 0) {
			_thr_wake_all(curthread->defer_waiters,
			    curthread->nwaiter_defer);
			curthread->nwaiter_defer = 0;
		}

		if (cancel)
			_thr_cancel_enter2(curthread, 0);
		error = _thr_sleep(curthread, cvp->kcond.c_clockid, abstime);
		if (cancel)
			_thr_cancel_leave(curthread, 0);

		_sleepq_lock(cvp);
		if (curthread->wchan == NULL) {
			error = 0;
			break;
		} else if (cancel && SHOULD_CANCEL(curthread)) {
			sq = _sleepq_lookup(cvp);
			cvp->__has_user_waiters = _sleepq_remove(sq, curthread);
			_sleepq_unlock(cvp);
			curthread->mutex_obj = NULL;
			error2 = _mutex_cv_lock(mp, recurse, false);
			if (!THR_IN_CRITICAL(curthread))
				_pthread_exit(PTHREAD_CANCELED);
			else /* this should not happen */
				return (error2);
		} else if (error == ETIMEDOUT) {
			sq = _sleepq_lookup(cvp);
			cvp->__has_user_waiters =
			    _sleepq_remove(sq, curthread);
			break;
		}
	}
	_sleepq_unlock(cvp);
	curthread->mutex_obj = NULL;
	error2 = _mutex_cv_lock(mp, recurse, false);
	if (error == 0)
		error = error2;
	return (error);
}
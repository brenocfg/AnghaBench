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
struct timespec {int dummy; } ;
struct pthread_mutex {int /*<<< orphan*/  m_lock; } ;
struct pthread_cond {int /*<<< orphan*/  kcond; } ;
struct pthread {int dummy; } ;

/* Variables and functions */
 int CVWAIT_ABSTIME ; 
 int CVWAIT_CLOCKID ; 
 int EINTR ; 
 int ETIMEDOUT ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _mutex_cv_attach (struct pthread_mutex*,int) ; 
 int _mutex_cv_detach (struct pthread_mutex*,int*) ; 
 int _mutex_cv_lock (struct pthread_mutex*,int,int) ; 
 int _mutex_enter_robust (struct pthread*,struct pthread_mutex*) ; 
 int /*<<< orphan*/  _mutex_leave_robust (struct pthread*,struct pthread_mutex*) ; 
 int /*<<< orphan*/  _thr_cancel_enter2 (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _thr_testcancel (struct pthread*) ; 
 int _thr_ucond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec const*,int) ; 

__attribute__((used)) static int
cond_wait_kernel(struct pthread_cond *cvp, struct pthread_mutex *mp,
    const struct timespec *abstime, int cancel)
{
	struct pthread *curthread;
	int error, error2, recurse, robust;

	curthread = _get_curthread();
	robust = _mutex_enter_robust(curthread, mp);

	error = _mutex_cv_detach(mp, &recurse);
	if (error != 0) {
		if (robust)
			_mutex_leave_robust(curthread, mp);
		return (error);
	}

	if (cancel)
		_thr_cancel_enter2(curthread, 0);
	error = _thr_ucond_wait(&cvp->kcond, &mp->m_lock, abstime,
	    CVWAIT_ABSTIME | CVWAIT_CLOCKID);
	if (cancel)
		_thr_cancel_leave(curthread, 0);

	/*
	 * Note that PP mutex and ROBUST mutex may return
	 * interesting error codes.
	 */
	if (error == 0) {
		error2 = _mutex_cv_lock(mp, recurse, true);
	} else if (error == EINTR || error == ETIMEDOUT) {
		error2 = _mutex_cv_lock(mp, recurse, true);
		/*
		 * Do not do cancellation on EOWNERDEAD there.  The
		 * cancellation cleanup handler will use the protected
		 * state and unlock the mutex without making the state
		 * consistent and the state will be unrecoverable.
		 */
		if (error2 == 0 && cancel) {
			if (robust) {
				_mutex_leave_robust(curthread, mp);
				robust = false;
			}
			_thr_testcancel(curthread);
		}

		if (error == EINTR)
			error = 0;
	} else {
		/* We know that it didn't unlock the mutex. */
		_mutex_cv_attach(mp, recurse);
		if (cancel) {
			if (robust) {
				_mutex_leave_robust(curthread, mp);
				robust = false;
			}
			_thr_testcancel(curthread);
		}
		error2 = 0;
	}
	if (robust)
		_mutex_leave_robust(curthread, mp);
	return (error2 != 0 ? error2 : error);
}
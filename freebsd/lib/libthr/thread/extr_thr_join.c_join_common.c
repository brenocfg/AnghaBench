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
struct timespec {scalar_t__ tv_sec; } ;
struct pthread {int flags; long tid; struct pthread* joiner; void* ret; } ;
typedef  struct pthread* pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 int EDEADLK ; 
 int EINVAL ; 
 int ENOTSUP ; 
 int ESRCH ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  THR_CLEANUP_POP (struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  THR_CLEANUP_PUSH (struct pthread*,int /*<<< orphan*/ ,struct pthread*) ; 
 int THR_FLAGS_DETACHED ; 
 int /*<<< orphan*/  THR_THREAD_LOCK (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 long TID_TERMINATED ; 
 int /*<<< orphan*/  TIMESPEC_SUB (struct timespec*,struct timespec const*,struct timespec*) ; 
 struct pthread* _get_curthread () ; 
 int /*<<< orphan*/  _thr_cancel_enter (struct pthread*) ; 
 int /*<<< orphan*/  _thr_cancel_leave (struct pthread*,int /*<<< orphan*/ ) ; 
 int _thr_find_thread (struct pthread*,struct pthread*,int) ; 
 int /*<<< orphan*/  _thr_testcancel (struct pthread*) ; 
 int /*<<< orphan*/  _thr_try_gc (struct pthread*,struct pthread*) ; 
 int _thr_umtx_wait (long*,long,struct timespec*) ; 
 int /*<<< orphan*/  backout_join ; 
 int /*<<< orphan*/  clock_gettime (int /*<<< orphan*/ ,struct timespec*) ; 

__attribute__((used)) static int
join_common(pthread_t pthread, void **thread_return,
	const struct timespec *abstime)
{
	struct pthread *curthread = _get_curthread();
	struct timespec ts, ts2, *tsp;
	void *tmp;
	long tid;
	int ret = 0;

	if (pthread == NULL)
		return (EINVAL);

	if (pthread == curthread)
		return (EDEADLK);

	if ((ret = _thr_find_thread(curthread, pthread, 1)) != 0)
		return (ESRCH);

	if ((pthread->flags & THR_FLAGS_DETACHED) != 0) {
		ret = EINVAL;
	} else if (pthread->joiner != NULL) {
		/* Multiple joiners are not supported. */
		ret = ENOTSUP;
	}
	if (ret) {
		THR_THREAD_UNLOCK(curthread, pthread);
		return (ret);
	}
	/* Set the running thread to be the joiner: */
	pthread->joiner = curthread;

	THR_THREAD_UNLOCK(curthread, pthread);

	THR_CLEANUP_PUSH(curthread, backout_join, pthread);
	_thr_cancel_enter(curthread);

	tid = pthread->tid;
	while (pthread->tid != TID_TERMINATED) {
		_thr_testcancel(curthread);
		if (abstime != NULL) {
			clock_gettime(CLOCK_REALTIME, &ts);
			TIMESPEC_SUB(&ts2, abstime, &ts);
			if (ts2.tv_sec < 0) {
				ret = ETIMEDOUT;
				break;
			}
			tsp = &ts2;
		} else
			tsp = NULL;
		ret = _thr_umtx_wait(&pthread->tid, tid, tsp);
		if (ret == ETIMEDOUT)
			break;
	}

	_thr_cancel_leave(curthread, 0);
	THR_CLEANUP_POP(curthread, 0);

	if (ret == ETIMEDOUT) {
		THR_THREAD_LOCK(curthread, pthread);
		pthread->joiner = NULL;
		THR_THREAD_UNLOCK(curthread, pthread);
	} else {
		ret = 0;
		tmp = pthread->ret;
		THR_THREAD_LOCK(curthread, pthread);
		pthread->flags |= THR_FLAGS_DETACHED;
		pthread->joiner = NULL;
		_thr_try_gc(curthread, pthread); /* thread lock released */

		if (thread_return != NULL)
			*thread_return = tmp;
	}
	return (ret);
}
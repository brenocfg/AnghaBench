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
struct pthread {int dummy; } ;
typedef  struct pthread* pthread_t ;

/* Variables and functions */
 int EDEADLK ; 
 int /*<<< orphan*/  THR_THREAD_LOCK (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 struct pthread* _get_curthread () ; 
 int _thr_ref_add (struct pthread*,struct pthread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _thr_ref_delete (struct pthread*,struct pthread*) ; 
 int /*<<< orphan*/  suspend_common (struct pthread*,struct pthread*,int) ; 

int
_pthread_suspend_np(pthread_t thread)
{
	struct pthread *curthread = _get_curthread();
	int ret;

	/* Suspending the current thread doesn't make sense. */
	if (thread == _get_curthread())
		ret = EDEADLK;

	/* Add a reference to the thread: */
	else if ((ret = _thr_ref_add(curthread, thread, /*include dead*/0))
	    == 0) {
		/* Lock the threads scheduling queue: */
		THR_THREAD_LOCK(curthread, thread);
		suspend_common(curthread, thread, 1);
		/* Unlock the threads scheduling queue: */
		THR_THREAD_UNLOCK(curthread, thread);

		/* Don't forget to remove the reference: */
		_thr_ref_delete(curthread, thread);
	}
	return (ret);
}
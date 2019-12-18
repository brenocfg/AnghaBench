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
typedef  int /*<<< orphan*/  pthread_t ;

/* Variables and functions */
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,int /*<<< orphan*/ ) ; 
 struct pthread* _get_curthread () ; 
 int _thr_find_thread (struct pthread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resume_common (int /*<<< orphan*/ ) ; 

int
_pthread_resume_np(pthread_t thread)
{
	struct pthread *curthread = _get_curthread();
	int ret;

	/* Add a reference to the thread: */
	if ((ret = _thr_find_thread(curthread, thread, /*include dead*/0)) == 0) {
		/* Lock the threads scheduling queue: */
		resume_common(thread);
		THR_THREAD_UNLOCK(curthread, thread);
	}
	return (ret);
}
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
struct sched_param {int /*<<< orphan*/  sched_priority; } ;
struct TYPE_2__ {int sched_policy; int /*<<< orphan*/  prio; } ;
struct pthread {TYPE_1__ attr; } ;
typedef  struct pthread* pthread_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  THR_LOCK (struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 struct pthread* _get_curthread () ; 
 int _thr_find_thread (struct pthread*,struct pthread*,int /*<<< orphan*/ ) ; 

int
_pthread_getschedparam(pthread_t pthread, int * __restrict policy, 
    struct sched_param * __restrict param)
{
	struct pthread *curthread = _get_curthread();
	int ret = 0;

	if (policy == NULL || param == NULL)
		return (EINVAL);

	/*
	 * Avoid searching the thread list when it is the current
	 * thread.
	 */
	if (pthread == curthread)
		THR_LOCK(curthread);
	else if ((ret = _thr_find_thread(curthread, pthread, /*include dead*/0)))
		return (ret);
	*policy = pthread->attr.sched_policy;
	param->sched_priority = pthread->attr.prio;
	THR_THREAD_UNLOCK(curthread, pthread);
	return (ret);
}
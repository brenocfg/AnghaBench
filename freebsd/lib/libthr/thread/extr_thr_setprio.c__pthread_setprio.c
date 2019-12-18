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
struct sched_param {int sched_priority; } ;
struct TYPE_2__ {scalar_t__ sched_policy; int prio; } ;
struct pthread {TYPE_1__ attr; int /*<<< orphan*/  tid; } ;
typedef  struct pthread* pthread_t ;

/* Variables and functions */
 scalar_t__ SCHED_OTHER ; 
 int /*<<< orphan*/  THR_LOCK (struct pthread*) ; 
 int /*<<< orphan*/  THR_THREAD_UNLOCK (struct pthread*,struct pthread*) ; 
 struct pthread* _get_curthread () ; 
 int _thr_find_thread (struct pthread*,struct pthread*,int /*<<< orphan*/ ) ; 
 int _thr_setscheduler (int /*<<< orphan*/ ,scalar_t__,struct sched_param*) ; 
 int errno ; 

int
_pthread_setprio(pthread_t pthread, int prio)
{
	struct pthread	*curthread = _get_curthread();
	struct sched_param	param;
	int	ret;

	param.sched_priority = prio;
	if (pthread == curthread)
		THR_LOCK(curthread);
	else if ((ret = _thr_find_thread(curthread, pthread, /*include dead*/0)))
		return (ret);
	if (pthread->attr.sched_policy == SCHED_OTHER ||
	    pthread->attr.prio == prio) {
		pthread->attr.prio = prio;
		ret = 0;
	} else {
		ret = _thr_setscheduler(pthread->tid,
			pthread->attr.sched_policy, &param);
		if (ret == -1)
			ret = errno;
		else
			pthread->attr.prio = prio;
	}
	THR_THREAD_UNLOCK(curthread, pthread);
	return (ret);
}
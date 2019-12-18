#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pthread_attr_t ;
struct TYPE_5__ {int /*<<< orphan*/  pri_default; } ;
struct TYPE_4__ {int sched_policy; int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 int SCHED_FIFO ; 
 int SCHED_RR ; 
 TYPE_2__* _thr_priorities ; 

int
_thr_attr_setschedpolicy(pthread_attr_t *attr, int policy)
{
	int ret = 0;

	if ((attr == NULL) || (*attr == NULL))
		ret = EINVAL;
	else if ((policy < SCHED_FIFO) || (policy > SCHED_RR)) {
		ret = ENOTSUP;
	} else {
		(*attr)->sched_policy = policy;
		(*attr)->prio = _thr_priorities[policy-1].pri_default;
	}
	return(ret);
}
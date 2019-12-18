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
struct sched_param {scalar_t__ sched_priority; } ;
typedef  TYPE_1__* pthread_attr_t ;
struct TYPE_5__ {scalar_t__ pri_min; scalar_t__ pri_max; } ;
struct TYPE_4__ {int sched_policy; scalar_t__ prio; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 int SCHED_FIFO ; 
 int SCHED_RR ; 
 TYPE_2__* _thr_priorities ; 

int
_thr_attr_setschedparam(pthread_attr_t * __restrict attr,
    const struct sched_param * __restrict param)
{
	int policy;

	if ((attr == NULL) || (*attr == NULL))
		return (EINVAL);

	if (param == NULL)
		return (ENOTSUP);

	policy = (*attr)->sched_policy;

	if (policy == SCHED_FIFO || policy == SCHED_RR) {
		if (param->sched_priority < _thr_priorities[policy-1].pri_min ||
		    param->sched_priority > _thr_priorities[policy-1].pri_max)
		return (ENOTSUP);
	} else {
		/*
		 * Ignore it for SCHED_OTHER now, patches for glib ports
		 * are wrongly using M:N thread library's internal macro
		 * THR_MIN_PRIORITY and THR_MAX_PRIORITY.
		 */
	}

	(*attr)->prio = param->sched_priority;

	return (0);
}
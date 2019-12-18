#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sched_param {int /*<<< orphan*/  sched_priority; } ;
typedef  TYPE_1__* pthread_attr_t ;
struct TYPE_3__ {int /*<<< orphan*/  prio; } ;

/* Variables and functions */
 int EINVAL ; 

int
_thr_attr_getschedparam(const pthread_attr_t * __restrict attr,
    struct sched_param * __restrict param)
{
	int ret = 0;

	if ((attr == NULL) || (*attr == NULL) || (param == NULL))
		ret = EINVAL;
	else
		param->sched_priority = (*attr)->prio;

	return(ret);
}
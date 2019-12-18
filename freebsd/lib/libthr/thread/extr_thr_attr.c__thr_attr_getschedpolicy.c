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
typedef  TYPE_1__* pthread_attr_t ;
struct TYPE_3__ {int sched_policy; } ;

/* Variables and functions */
 int EINVAL ; 

int
_thr_attr_getschedpolicy(const pthread_attr_t * __restrict attr,
    int * __restrict policy)
{
	int ret = 0;

	if ((attr == NULL) || (*attr == NULL) || (policy == NULL))
		ret = EINVAL;
	else
		*policy = (*attr)->sched_policy;

	return(ret);
}
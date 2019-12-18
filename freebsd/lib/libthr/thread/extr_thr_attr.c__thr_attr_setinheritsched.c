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
struct TYPE_3__ {int sched_inherit; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 int PTHREAD_EXPLICIT_SCHED ; 
 int PTHREAD_INHERIT_SCHED ; 

int
_thr_attr_setinheritsched(pthread_attr_t *attr, int sched_inherit)
{
	int ret = 0;

	if ((attr == NULL) || (*attr == NULL))
		ret = EINVAL;
	else if (sched_inherit != PTHREAD_INHERIT_SCHED &&
		 sched_inherit != PTHREAD_EXPLICIT_SCHED)
		ret = ENOTSUP;
	else
		(*attr)->sched_inherit = sched_inherit;

	return(ret);
}
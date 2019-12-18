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
typedef  TYPE_1__* pthread_mutexattr_t ;
struct TYPE_3__ {scalar_t__ m_protocol; int m_ceiling; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ PTHREAD_PRIO_PROTECT ; 

int
_pthread_mutexattr_setprioceiling(pthread_mutexattr_t *mattr, int prioceiling)
{
	int ret = 0;

	if (mattr == NULL || *mattr == NULL)
		ret = EINVAL;
	else if ((*mattr)->m_protocol != PTHREAD_PRIO_PROTECT)
		ret = EINVAL;
	else
		(*mattr)->m_ceiling = prioceiling;

	return (ret);
}
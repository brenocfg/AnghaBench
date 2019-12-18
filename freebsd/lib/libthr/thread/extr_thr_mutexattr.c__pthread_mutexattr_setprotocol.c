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
struct TYPE_3__ {int m_protocol; int /*<<< orphan*/  m_ceiling; } ;

/* Variables and functions */
 int EINVAL ; 
 int PTHREAD_PRIO_NONE ; 
 int PTHREAD_PRIO_PROTECT ; 
 int /*<<< orphan*/  THR_MAX_RR_PRIORITY ; 

int
_pthread_mutexattr_setprotocol(pthread_mutexattr_t *mattr, int protocol)
{
	int ret = 0;

	if (mattr == NULL || *mattr == NULL ||
	    protocol < PTHREAD_PRIO_NONE || protocol > PTHREAD_PRIO_PROTECT)
		ret = EINVAL;
	else {
		(*mattr)->m_protocol = protocol;
		(*mattr)->m_ceiling = THR_MAX_RR_PRIORITY;
	}
	return (ret);
}
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
struct TYPE_3__ {int m_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int PTHREAD_MUTEX_TYPE_MAX ; 

int
_thr_mutexattr_settype(pthread_mutexattr_t *attr, int type)
{
	int	ret;

	if (attr == NULL || *attr == NULL || type >= PTHREAD_MUTEX_TYPE_MAX) {
		ret = EINVAL;
	} else {
		(*attr)->m_type = type;
		ret = 0;
	}
	return (ret);
}
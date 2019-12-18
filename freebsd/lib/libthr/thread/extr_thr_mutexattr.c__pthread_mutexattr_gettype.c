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
_pthread_mutexattr_gettype(const pthread_mutexattr_t * __restrict attr,
    int * __restrict type)
{
	int	ret;

	if (attr == NULL || *attr == NULL || (*attr)->m_type >=
	    PTHREAD_MUTEX_TYPE_MAX) {
		ret = EINVAL;
	} else {
		*type = (*attr)->m_type;
		ret = 0;
	}
	return (ret);
}
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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

int
_pthread_mutexattr_setkind_np(pthread_mutexattr_t *attr, int kind)
{
	int	ret;
	if (attr == NULL || *attr == NULL) {
		errno = EINVAL;
		ret = -1;
	} else {
		(*attr)->m_type = kind;
		ret = 0;
	}
	return(ret);
}
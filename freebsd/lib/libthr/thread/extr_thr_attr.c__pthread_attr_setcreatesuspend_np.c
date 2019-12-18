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
struct TYPE_3__ {int /*<<< orphan*/  suspend; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  THR_CREATE_SUSPENDED ; 

int
_pthread_attr_setcreatesuspend_np(pthread_attr_t *attr)
{
	int	ret;

	if (attr == NULL || *attr == NULL) {
		ret = EINVAL;
	} else {
		(*attr)->suspend = THR_CREATE_SUSPENDED;
		ret = 0;
	}
	return(ret);
}
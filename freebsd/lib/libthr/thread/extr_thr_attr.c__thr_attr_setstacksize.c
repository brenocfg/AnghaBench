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
struct TYPE_3__ {size_t stacksize_attr; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t PTHREAD_STACK_MIN ; 

int
_thr_attr_setstacksize(pthread_attr_t *attr, size_t stacksize)
{
	int	ret;

	/* Check for invalid arguments: */
	if (attr == NULL || *attr == NULL || stacksize < PTHREAD_STACK_MIN)
		ret = EINVAL;
	else {
		/* Save the stack size: */
		(*attr)->stacksize_attr = stacksize;
		ret = 0;
	}
	return(ret);
}
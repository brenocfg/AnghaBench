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
struct TYPE_3__ {void* stackaddr_attr; } ;

/* Variables and functions */
 int EINVAL ; 

int
_thr_attr_getstackaddr(const pthread_attr_t *attr, void **stackaddr)
{
	int	ret;

	/* Check for invalid arguments: */
	if (attr == NULL || *attr == NULL || stackaddr == NULL)
		ret = EINVAL;
	else {
		/* Return the stack address: */
		*stackaddr = (*attr)->stackaddr_attr;
		ret = 0;
	}
	return(ret);
}
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
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int PTHREAD_CREATE_DETACHED ; 
 int PTHREAD_CREATE_JOINABLE ; 
 int PTHREAD_DETACHED ; 

int
_thr_attr_getdetachstate(const pthread_attr_t *attr, int *detachstate)
{
	int	ret;

	/* Check for invalid arguments: */
	if (attr == NULL || *attr == NULL || detachstate == NULL)
		ret = EINVAL;
	else {
		/* Check if the detached flag is set: */
		if ((*attr)->flags & PTHREAD_DETACHED)
			/* Return detached: */
			*detachstate = PTHREAD_CREATE_DETACHED;
		else
			/* Return joinable: */
			*detachstate = PTHREAD_CREATE_JOINABLE;
		ret = 0;
	}
	return(ret);
}
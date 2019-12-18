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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int PTHREAD_CREATE_DETACHED ; 
 int PTHREAD_CREATE_JOINABLE ; 
 int /*<<< orphan*/  PTHREAD_DETACHED ; 

int
_thr_attr_setdetachstate(pthread_attr_t *attr, int detachstate)
{
	int	ret;

	/* Check for invalid arguments: */
	if (attr == NULL || *attr == NULL ||
	    (detachstate != PTHREAD_CREATE_DETACHED &&
	    detachstate != PTHREAD_CREATE_JOINABLE))
		ret = EINVAL;
	else {
		/* Check if detached state: */
		if (detachstate == PTHREAD_CREATE_DETACHED)
			/* Set the detached flag: */
			(*attr)->flags |= PTHREAD_DETACHED;
		else
			/* Reset the detached flag: */
			(*attr)->flags &= ~PTHREAD_DETACHED;
		ret = 0;
	}
	return(ret);
}
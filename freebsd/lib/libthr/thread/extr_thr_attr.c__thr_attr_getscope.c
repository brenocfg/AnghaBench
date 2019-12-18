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
 int PTHREAD_SCOPE_PROCESS ; 
 int PTHREAD_SCOPE_SYSTEM ; 

int
_thr_attr_getscope(const pthread_attr_t * __restrict attr,
    int * __restrict contentionscope)
{
	int ret = 0;

	if ((attr == NULL) || (*attr == NULL) || (contentionscope == NULL))
		/* Return an invalid argument: */
		ret = EINVAL;

	else
		*contentionscope = (*attr)->flags & PTHREAD_SCOPE_SYSTEM ?
		    PTHREAD_SCOPE_SYSTEM : PTHREAD_SCOPE_PROCESS;

	return(ret);
}
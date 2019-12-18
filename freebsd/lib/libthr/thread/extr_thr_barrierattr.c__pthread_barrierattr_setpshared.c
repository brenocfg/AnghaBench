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
typedef  TYPE_1__* pthread_barrierattr_t ;
struct TYPE_3__ {int pshared; } ;

/* Variables and functions */
 int EINVAL ; 
 int PTHREAD_PROCESS_PRIVATE ; 
 int PTHREAD_PROCESS_SHARED ; 

int
_pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared)
{

	if (attr == NULL || *attr == NULL ||
	    (pshared != PTHREAD_PROCESS_PRIVATE &&
	    pshared != PTHREAD_PROCESS_SHARED))
		return (EINVAL);

	(*attr)->pshared = pshared;
	return (0);
}
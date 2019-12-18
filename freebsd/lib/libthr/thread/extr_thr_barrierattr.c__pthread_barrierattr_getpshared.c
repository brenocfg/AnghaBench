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

int
_pthread_barrierattr_getpshared(const pthread_barrierattr_t * __restrict attr,
    int * __restrict pshared)
{

	if (attr == NULL || *attr == NULL)
		return (EINVAL);

	*pshared = (*attr)->pshared;
	return (0);
}
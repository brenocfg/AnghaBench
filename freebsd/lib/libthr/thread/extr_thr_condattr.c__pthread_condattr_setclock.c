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
typedef  TYPE_1__* pthread_condattr_t ;
typedef  scalar_t__ clockid_t ;
struct TYPE_3__ {scalar_t__ c_clockid; } ;

/* Variables and functions */
 scalar_t__ CLOCK_MONOTONIC ; 
 scalar_t__ CLOCK_PROF ; 
 scalar_t__ CLOCK_REALTIME ; 
 scalar_t__ CLOCK_VIRTUAL ; 
 int EINVAL ; 

int
_pthread_condattr_setclock(pthread_condattr_t *attr, clockid_t clock_id)
{
	if (attr == NULL || *attr == NULL)
		return (EINVAL);
	if (clock_id != CLOCK_REALTIME &&
	    clock_id != CLOCK_VIRTUAL &&
	    clock_id != CLOCK_PROF &&
	    clock_id != CLOCK_MONOTONIC) {
		return  (EINVAL);
	}
	(*attr)->c_clockid = clock_id;
	return (0);
}
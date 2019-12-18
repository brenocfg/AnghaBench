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
typedef  int /*<<< orphan*/  clockid_t ;
struct TYPE_3__ {int /*<<< orphan*/  c_clockid; } ;

/* Variables and functions */
 int EINVAL ; 

int
_pthread_condattr_getclock(const pthread_condattr_t * __restrict attr,
    clockid_t * __restrict clock_id)
{
	if (attr == NULL || *attr == NULL)
		return (EINVAL);
	*clock_id = (*attr)->c_clockid;
	return (0);
}
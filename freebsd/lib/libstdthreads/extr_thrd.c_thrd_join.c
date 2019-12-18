#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  thrd_t ;

/* Variables and functions */
 scalar_t__ pthread_join (int /*<<< orphan*/ ,void**) ; 
 int thrd_error ; 
 int thrd_success ; 

int
thrd_join(thrd_t thr, int *res)
{
	void *value_ptr;

	if (pthread_join(thr, &value_ptr) != 0)
		return (thrd_error);
	if (res != NULL)
		*res = (intptr_t)value_ptr;
	return (thrd_success);
}
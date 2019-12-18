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
typedef  int /*<<< orphan*/ * pthread_rwlockattr_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int
_pthread_rwlockattr_destroy(pthread_rwlockattr_t *rwlockattr)
{
	pthread_rwlockattr_t prwlockattr;

	if (rwlockattr == NULL)
		return (EINVAL);
	prwlockattr = *rwlockattr;
	if (prwlockattr == NULL)
		return (EINVAL);
	free(prwlockattr);
	return (0);
}
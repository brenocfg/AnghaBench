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
typedef  int /*<<< orphan*/ * acl_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int _acl_brand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 

int
acl_get_brand_np(acl_t acl, int *brand_p)
{

	if (acl == NULL || brand_p == NULL) {
		errno = EINVAL;
		return (-1);
	}
	*brand_p = _acl_brand(acl);

	return (0);
}
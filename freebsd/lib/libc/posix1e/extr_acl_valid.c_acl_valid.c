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
 int /*<<< orphan*/  ACL_BRAND_POSIX ; 
 int EINVAL ; 
 int /*<<< orphan*/  _acl_brand_may_be (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int _posix1e_acl_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _posix1e_acl_sort (int /*<<< orphan*/ *) ; 
 int errno ; 

int
acl_valid(acl_t acl)
{
	int	error;

	if (acl == NULL) {
		errno = EINVAL;
		return (-1);
	}
	if (!_acl_brand_may_be(acl, ACL_BRAND_POSIX)) {
		errno = EINVAL;
		return (-1);
	}
	_posix1e_acl_sort(acl);
	error = _posix1e_acl_check(acl);
	if (error) {
		errno = error;
		return (-1);
	} else {
		return (0);
	}
}
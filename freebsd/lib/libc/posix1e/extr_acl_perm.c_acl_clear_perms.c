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
typedef  int /*<<< orphan*/ * acl_permset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_PERM_NONE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

int
acl_clear_perms(acl_permset_t permset_d)
{

	if (permset_d == NULL) {
		errno = EINVAL;
		return (-1);
	}

	*permset_d = ACL_PERM_NONE;

	return (0);
}
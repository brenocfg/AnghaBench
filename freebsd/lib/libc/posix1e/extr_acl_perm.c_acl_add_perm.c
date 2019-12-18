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
typedef  int /*<<< orphan*/  acl_perm_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ _perm_is_invalid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 

int
acl_add_perm(acl_permset_t permset_d, acl_perm_t perm)
{

	if (permset_d == NULL) {
		errno = EINVAL;
		return (-1);
	}

	if (_perm_is_invalid(perm))
		return (-1);

	*permset_d |= perm;

	return (0);
}
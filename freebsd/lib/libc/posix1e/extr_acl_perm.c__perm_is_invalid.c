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
typedef  int acl_perm_t ;

/* Variables and functions */
 int ACL_NFS4_PERM_BITS ; 
 int ACL_POSIX1E_BITS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  errno ; 

__attribute__((used)) static int
_perm_is_invalid(acl_perm_t perm)
{

	/* Check if more than a single bit is set. */
	if ((perm & -perm) == perm &&
	    (perm & (ACL_POSIX1E_BITS | ACL_NFS4_PERM_BITS)) == perm)
		return (0);

	errno = EINVAL;

	return (1);
}
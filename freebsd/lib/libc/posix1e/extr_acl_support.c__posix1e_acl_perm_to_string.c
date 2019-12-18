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
typedef  scalar_t__ ssize_t ;
typedef  int acl_perm_t ;

/* Variables and functions */
 int ACL_EXECUTE ; 
 int ACL_PERM_BITS ; 
 int ACL_READ ; 
 char ACL_STRING_PERM_EXEC ; 
 char ACL_STRING_PERM_NONE ; 
 char ACL_STRING_PERM_READ ; 
 char ACL_STRING_PERM_WRITE ; 
 int ACL_WRITE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ _POSIX1E_ACL_STRING_PERM_MAXSIZE ; 
 int /*<<< orphan*/  errno ; 

int
_posix1e_acl_perm_to_string(acl_perm_t perm, ssize_t buf_len, char *buf)
{

	if (buf_len < _POSIX1E_ACL_STRING_PERM_MAXSIZE + 1) {
		errno = ENOMEM;
		return (-1);
	}

	if ((perm | ACL_PERM_BITS) != ACL_PERM_BITS) {
		errno = EINVAL;
		return (-1);
	}

	buf[3] = 0;	/* null terminate */

	if (perm & ACL_READ)
		buf[0] = ACL_STRING_PERM_READ;
	else
		buf[0] = ACL_STRING_PERM_NONE;

	if (perm & ACL_WRITE)
		buf[1] = ACL_STRING_PERM_WRITE;
	else
		buf[1] = ACL_STRING_PERM_NONE;

	if (perm & ACL_EXECUTE)
		buf[2] = ACL_STRING_PERM_EXEC;
	else
		buf[2] = ACL_STRING_PERM_NONE;

	return (0);
}
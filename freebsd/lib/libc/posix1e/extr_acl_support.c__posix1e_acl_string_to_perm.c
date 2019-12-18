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
typedef  int /*<<< orphan*/  acl_perm_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_EXECUTE ; 
 int /*<<< orphan*/  ACL_PERM_NONE ; 
 int /*<<< orphan*/  ACL_READ ; 
#define  ACL_STRING_PERM_EXEC 131 
#define  ACL_STRING_PERM_NONE 130 
#define  ACL_STRING_PERM_READ 129 
#define  ACL_STRING_PERM_WRITE 128 
 int /*<<< orphan*/  ACL_WRITE ; 
 int EINVAL ; 

int
_posix1e_acl_string_to_perm(char *string, acl_perm_t *perm)
{
	acl_perm_t	myperm = ACL_PERM_NONE;
	char	*ch;

	ch = string;
	while (*ch) {
		switch(*ch) {
		case ACL_STRING_PERM_READ:
			myperm |= ACL_READ;
			break;
		case ACL_STRING_PERM_WRITE:
			myperm |= ACL_WRITE;
			break;
		case ACL_STRING_PERM_EXEC:
			myperm |= ACL_EXECUTE;
			break;
		case ACL_STRING_PERM_NONE:
			break;
		default:
			return (EINVAL);
		}
		ch++;
	}

	*perm = myperm;
	return (0);
}
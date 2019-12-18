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
typedef  int mode_t ;
typedef  int acl_tag_t ;
typedef  int /*<<< orphan*/  acl_perm_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_EXECUTE ; 
#define  ACL_GROUP_OBJ 130 
#define  ACL_OTHER 129 
 int /*<<< orphan*/  ACL_READ ; 
#define  ACL_USER_OBJ 128 
 int /*<<< orphan*/  ACL_WRITE ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  printf (char*,int) ; 

acl_perm_t
acl_posix1e_mode_to_perm(acl_tag_t tag, mode_t mode)
{
	acl_perm_t	perm = 0;

	switch(tag) {
	case ACL_USER_OBJ:
		if (mode & S_IXUSR)
			perm |= ACL_EXECUTE;
		if (mode & S_IRUSR)
			perm |= ACL_READ;
		if (mode & S_IWUSR)
			perm |= ACL_WRITE;
		return (perm);

	case ACL_GROUP_OBJ:
		if (mode & S_IXGRP)
			perm |= ACL_EXECUTE;
		if (mode & S_IRGRP)
			perm |= ACL_READ;
		if (mode & S_IWGRP)
			perm |= ACL_WRITE;
		return (perm);

	case ACL_OTHER:
		if (mode & S_IXOTH)
			perm |= ACL_EXECUTE;
		if (mode & S_IROTH)
			perm |= ACL_READ;
		if (mode & S_IWOTH)
			perm |= ACL_WRITE;
		return (perm);

	default:
		printf("acl_posix1e_mode_to_perm: invalid tag (%d)\n", tag);
		return (0);
	}
}
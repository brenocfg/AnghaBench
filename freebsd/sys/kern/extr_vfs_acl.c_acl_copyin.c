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
struct oldacl {int /*<<< orphan*/  acl_maxcnt; } ;
struct acl {int /*<<< orphan*/  acl_maxcnt; } ;
typedef  int /*<<< orphan*/  old ;
typedef  int acl_type_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACL_MAX_ENTRIES ; 
#define  ACL_TYPE_ACCESS_OLD 129 
#define  ACL_TYPE_DEFAULT_OLD 128 
 int EINVAL ; 
 int /*<<< orphan*/  acl_copy_oldacl_into_acl (struct oldacl*,struct oldacl*) ; 
 int copyin (void const*,struct oldacl*,int) ; 

__attribute__((used)) static int
acl_copyin(const void *user_acl, struct acl *kernel_acl, acl_type_t type)
{
	int error;
	struct oldacl old;

	switch (type) {
	case ACL_TYPE_ACCESS_OLD:
	case ACL_TYPE_DEFAULT_OLD:
		error = copyin(user_acl, &old, sizeof(old));
		if (error != 0)
			break;
		acl_copy_oldacl_into_acl(&old, kernel_acl);
		break;

	default:
		error = copyin(user_acl, kernel_acl, sizeof(*kernel_acl));
		if (kernel_acl->acl_maxcnt != ACL_MAX_ENTRIES)
			return (EINVAL);
	}

	return (error);
}
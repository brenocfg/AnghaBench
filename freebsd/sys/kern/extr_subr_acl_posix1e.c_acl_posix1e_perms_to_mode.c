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
struct acl_entry {int ae_perm; } ;
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int ACL_EXECUTE ; 
 int ACL_READ ; 
 int ACL_WRITE ; 
 int /*<<< orphan*/  S_IRGRP ; 
 int /*<<< orphan*/  S_IROTH ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  S_IWGRP ; 
 int /*<<< orphan*/  S_IWOTH ; 
 int /*<<< orphan*/  S_IWUSR ; 
 int /*<<< orphan*/  S_IXGRP ; 
 int /*<<< orphan*/  S_IXOTH ; 
 int /*<<< orphan*/  S_IXUSR ; 

mode_t
acl_posix1e_perms_to_mode(struct acl_entry *acl_user_obj_entry,
    struct acl_entry *acl_group_obj_entry, struct acl_entry *acl_other_entry)
{
	mode_t	mode;

	mode = 0;
	if (acl_user_obj_entry->ae_perm & ACL_EXECUTE)
		mode |= S_IXUSR;
	if (acl_user_obj_entry->ae_perm & ACL_READ)
		mode |= S_IRUSR;
	if (acl_user_obj_entry->ae_perm & ACL_WRITE)
		mode |= S_IWUSR;
	if (acl_group_obj_entry->ae_perm & ACL_EXECUTE)
		mode |= S_IXGRP;
	if (acl_group_obj_entry->ae_perm & ACL_READ)
		mode |= S_IRGRP;
	if (acl_group_obj_entry->ae_perm & ACL_WRITE)
		mode |= S_IWGRP;
	if (acl_other_entry->ae_perm & ACL_EXECUTE)
		mode |= S_IXOTH;
	if (acl_other_entry->ae_perm & ACL_READ)
		mode |= S_IROTH;
	if (acl_other_entry->ae_perm & ACL_WRITE)
		mode |= S_IWOTH;

	return (mode);
}
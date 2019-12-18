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
struct acl {scalar_t__ acl_cnt; } ;
typedef  int mode_t ;
typedef  int acl_perm_t ;

/* Variables and functions */
 int ACL_APPEND_DATA ; 
 int /*<<< orphan*/  ACL_ENTRY_TYPE_ALLOW ; 
 int /*<<< orphan*/  ACL_ENTRY_TYPE_DENY ; 
 int /*<<< orphan*/  ACL_EVERYONE ; 
 int ACL_EXECUTE ; 
 int /*<<< orphan*/  ACL_GROUP_OBJ ; 
 int ACL_READ_ACL ; 
 int ACL_READ_ATTRIBUTES ; 
 int ACL_READ_DATA ; 
 int ACL_READ_NAMED_ATTRS ; 
 int ACL_SYNCHRONIZE ; 
 int /*<<< orphan*/  ACL_USER_OBJ ; 
 int ACL_WRITE_ACL ; 
 int ACL_WRITE_ATTRIBUTES ; 
 int ACL_WRITE_DATA ; 
 int ACL_WRITE_NAMED_ATTRS ; 
 int ACL_WRITE_OWNER ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int S_IRGRP ; 
 int S_IROTH ; 
 int S_IRUSR ; 
 int S_IWGRP ; 
 int S_IWOTH ; 
 int S_IWUSR ; 
 int S_IXGRP ; 
 int S_IXOTH ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  _acl_append (struct acl*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acl_nfs4_inherit_entries (struct acl const*,struct acl*,int,int,int) ; 

__attribute__((used)) static void		
acl_nfs4_compute_inherited_acl_psarc(const struct acl *parent_aclp,
    struct acl *aclp, mode_t mode, int file_owner_id, int is_directory)
{
	acl_perm_t user_allow_first = 0, user_deny = 0, group_deny = 0;
	acl_perm_t user_allow, group_allow, everyone_allow;

	KASSERT(aclp->acl_cnt == 0, ("aclp->acl_cnt == 0"));

	user_allow = group_allow = everyone_allow = ACL_READ_ACL |
	    ACL_READ_ATTRIBUTES | ACL_READ_NAMED_ATTRS | ACL_SYNCHRONIZE;
	user_allow |= ACL_WRITE_ACL | ACL_WRITE_OWNER | ACL_WRITE_ATTRIBUTES |
	    ACL_WRITE_NAMED_ATTRS;

	if (mode & S_IRUSR)
		user_allow |= ACL_READ_DATA;
	if (mode & S_IWUSR)
		user_allow |= (ACL_WRITE_DATA | ACL_APPEND_DATA);
	if (mode & S_IXUSR)
		user_allow |= ACL_EXECUTE;

	if (mode & S_IRGRP)
		group_allow |= ACL_READ_DATA;
	if (mode & S_IWGRP)
		group_allow |= (ACL_WRITE_DATA | ACL_APPEND_DATA);
	if (mode & S_IXGRP)
		group_allow |= ACL_EXECUTE;

	if (mode & S_IROTH)
		everyone_allow |= ACL_READ_DATA;
	if (mode & S_IWOTH)
		everyone_allow |= (ACL_WRITE_DATA | ACL_APPEND_DATA);
	if (mode & S_IXOTH)
		everyone_allow |= ACL_EXECUTE;

	user_deny = ((group_allow | everyone_allow) & ~user_allow);
	group_deny = everyone_allow & ~group_allow;
	user_allow_first = group_deny & ~user_deny;

	if (user_allow_first != 0)
		_acl_append(aclp, ACL_USER_OBJ, user_allow_first,
		    ACL_ENTRY_TYPE_ALLOW);
	if (user_deny != 0)
		_acl_append(aclp, ACL_USER_OBJ, user_deny,
		    ACL_ENTRY_TYPE_DENY);
	if (group_deny != 0)
		_acl_append(aclp, ACL_GROUP_OBJ, group_deny,
		    ACL_ENTRY_TYPE_DENY);

	if (parent_aclp != NULL)
		acl_nfs4_inherit_entries(parent_aclp, aclp, mode,
		    file_owner_id, is_directory);

	_acl_append(aclp, ACL_USER_OBJ, user_allow, ACL_ENTRY_TYPE_ALLOW);
	_acl_append(aclp, ACL_GROUP_OBJ, group_allow, ACL_ENTRY_TYPE_ALLOW);
	_acl_append(aclp, ACL_EVERYONE, everyone_allow, ACL_ENTRY_TYPE_ALLOW);
}
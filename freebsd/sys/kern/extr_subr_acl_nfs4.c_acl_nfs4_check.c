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
struct acl_entry {int ae_tag; int ae_perm; scalar_t__ ae_entry_type; int ae_flags; int /*<<< orphan*/  ae_id; } ;
struct acl {int acl_cnt; struct acl_entry* acl_entry; } ;

/* Variables and functions */
 int ACL_ENTRY_DIRECTORY_INHERIT ; 
 int ACL_ENTRY_FAILED_ACCESS ; 
 int ACL_ENTRY_FILE_INHERIT ; 
 int ACL_ENTRY_INHERIT_ONLY ; 
 int ACL_ENTRY_NO_PROPAGATE_INHERIT ; 
 int ACL_ENTRY_SUCCESSFUL_ACCESS ; 
 scalar_t__ ACL_ENTRY_TYPE_ALLOW ; 
 scalar_t__ ACL_ENTRY_TYPE_DENY ; 
#define  ACL_EVERYONE 132 
 int ACL_FLAGS_BITS ; 
#define  ACL_GROUP 131 
#define  ACL_GROUP_OBJ 130 
 int ACL_MAX_ENTRIES ; 
 int ACL_NFS4_PERM_BITS ; 
 int /*<<< orphan*/  ACL_UNDEFINED_ID ; 
#define  ACL_USER 129 
#define  ACL_USER_OBJ 128 
 int EINVAL ; 

int
acl_nfs4_check(const struct acl *aclp, int is_directory)
{
	int i;
	const struct acl_entry *entry;

	/*
	 * The spec doesn't seem to say anything about ACL validity.
	 * It seems there is not much to do here.  There is even no need
	 * to count "owner@" or "everyone@" (ACL_USER_OBJ and ACL_EVERYONE)
	 * entries, as there can be several of them and that's perfectly
	 * valid.  There can be none of them too.  Really.
	 */

	if (aclp->acl_cnt > ACL_MAX_ENTRIES || aclp->acl_cnt <= 0)
		return (EINVAL);

	for (i = 0; i < aclp->acl_cnt; i++) {
		entry = &(aclp->acl_entry[i]);

		switch (entry->ae_tag) {
		case ACL_USER_OBJ:
		case ACL_GROUP_OBJ:
		case ACL_EVERYONE:
			if (entry->ae_id != ACL_UNDEFINED_ID)
				return (EINVAL);
			break;

		case ACL_USER:
		case ACL_GROUP:
			if (entry->ae_id == ACL_UNDEFINED_ID)
				return (EINVAL);
			break;

		default:
			return (EINVAL);
		}

		if ((entry->ae_perm | ACL_NFS4_PERM_BITS) != ACL_NFS4_PERM_BITS)
			return (EINVAL);

		/*
		 * Disallow ACL_ENTRY_TYPE_AUDIT and ACL_ENTRY_TYPE_ALARM for now.
		 */
		if (entry->ae_entry_type != ACL_ENTRY_TYPE_ALLOW &&
		    entry->ae_entry_type != ACL_ENTRY_TYPE_DENY)
			return (EINVAL);

		if ((entry->ae_flags | ACL_FLAGS_BITS) != ACL_FLAGS_BITS)
			return (EINVAL);

		/* Disallow unimplemented flags. */
		if (entry->ae_flags & (ACL_ENTRY_SUCCESSFUL_ACCESS |
		    ACL_ENTRY_FAILED_ACCESS))
			return (EINVAL);

		/* Disallow flags not allowed for ordinary files. */
		if (!is_directory) {
			if (entry->ae_flags & (ACL_ENTRY_FILE_INHERIT |
			    ACL_ENTRY_DIRECTORY_INHERIT |
			    ACL_ENTRY_NO_PROPAGATE_INHERIT | ACL_ENTRY_INHERIT_ONLY))
				return (EINVAL);
		}
	}

	return (0);
}
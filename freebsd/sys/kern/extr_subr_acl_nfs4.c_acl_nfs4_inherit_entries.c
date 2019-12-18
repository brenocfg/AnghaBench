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
struct acl_entry {int ae_flags; int ae_tag; scalar_t__ ae_entry_type; int ae_perm; } ;
struct acl {int acl_cnt; struct acl_entry* acl_entry; } ;
typedef  int mode_t ;

/* Variables and functions */
 int ACL_APPEND_DATA ; 
 int ACL_ENTRY_DIRECTORY_INHERIT ; 
 int ACL_ENTRY_FILE_INHERIT ; 
 int ACL_ENTRY_INHERITED ; 
 int ACL_ENTRY_INHERIT_ONLY ; 
 int ACL_ENTRY_NO_PROPAGATE_INHERIT ; 
 scalar_t__ ACL_ENTRY_TYPE_ALLOW ; 
 scalar_t__ ACL_ENTRY_TYPE_DENY ; 
 int ACL_EVERYONE ; 
 int ACL_EXECUTE ; 
 int ACL_GROUP_OBJ ; 
 int ACL_MAX_ENTRIES ; 
 int ACL_READ_DATA ; 
 int ACL_USER_OBJ ; 
 int ACL_WRITE_ACL ; 
 int ACL_WRITE_ATTRIBUTES ; 
 int ACL_WRITE_DATA ; 
 int ACL_WRITE_NAMED_ATTRS ; 
 int ACL_WRITE_OWNER ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int S_IRGRP ; 
 int S_IWGRP ; 
 int S_IXGRP ; 

__attribute__((used)) static void		
acl_nfs4_inherit_entries(const struct acl *parent_aclp,
    struct acl *child_aclp, mode_t mode, int file_owner_id,
    int is_directory)
{
	int i, flags, tag;
	const struct acl_entry *parent_entry;
	struct acl_entry *entry;

	KASSERT(parent_aclp->acl_cnt <= ACL_MAX_ENTRIES,
	    ("parent_aclp->acl_cnt <= ACL_MAX_ENTRIES"));

	for (i = 0; i < parent_aclp->acl_cnt; i++) {
		parent_entry = &(parent_aclp->acl_entry[i]);
		flags = parent_entry->ae_flags;
		tag = parent_entry->ae_tag;

		/*
		 * Don't inherit owner@, group@, or everyone@ entries.
		 */
		if (tag == ACL_USER_OBJ || tag == ACL_GROUP_OBJ ||
		    tag == ACL_EVERYONE)
			continue;

		/*
		 * Entry is not inheritable at all.
		 */
		if ((flags & (ACL_ENTRY_DIRECTORY_INHERIT |
		    ACL_ENTRY_FILE_INHERIT)) == 0)
			continue;

		/*
		 * We're creating a file, but entry is not inheritable
		 * by files.
		 */
		if (!is_directory && (flags & ACL_ENTRY_FILE_INHERIT) == 0)
			continue;

		/*
		 * Entry is inheritable only by files, but has NO_PROPAGATE
		 * flag set, and we're creating a directory, so it wouldn't
		 * propagate to any file in that directory anyway.
		 */
		if (is_directory &&
		    (flags & ACL_ENTRY_DIRECTORY_INHERIT) == 0 &&
		    (flags & ACL_ENTRY_NO_PROPAGATE_INHERIT))
			continue;

		/*
		 * Entry qualifies for being inherited.
		 */
		KASSERT(child_aclp->acl_cnt + 1 <= ACL_MAX_ENTRIES,
		    ("child_aclp->acl_cnt + 1 <= ACL_MAX_ENTRIES"));
		entry = &(child_aclp->acl_entry[child_aclp->acl_cnt]);
		*entry = *parent_entry;
		child_aclp->acl_cnt++;

		entry->ae_flags &= ~ACL_ENTRY_INHERIT_ONLY;
		entry->ae_flags |= ACL_ENTRY_INHERITED;

		/*
		 * If the type of the ACE is neither ALLOW nor DENY,
		 * then leave it as it is and proceed to the next one.
		 */
		if (entry->ae_entry_type != ACL_ENTRY_TYPE_ALLOW &&
		    entry->ae_entry_type != ACL_ENTRY_TYPE_DENY)
			continue;

		/*
		 * If the ACL_ENTRY_NO_PROPAGATE_INHERIT is set, or if
		 * the object being created is not a directory, then clear
		 * the following flags: ACL_ENTRY_NO_PROPAGATE_INHERIT,
		 * ACL_ENTRY_FILE_INHERIT, ACL_ENTRY_DIRECTORY_INHERIT,
		 * ACL_ENTRY_INHERIT_ONLY.
		 */
		if (entry->ae_flags & ACL_ENTRY_NO_PROPAGATE_INHERIT ||
		    !is_directory) {
			entry->ae_flags &= ~(ACL_ENTRY_NO_PROPAGATE_INHERIT |
			ACL_ENTRY_FILE_INHERIT | ACL_ENTRY_DIRECTORY_INHERIT |
			ACL_ENTRY_INHERIT_ONLY);
		}

		/*
		 * If the object is a directory and ACL_ENTRY_FILE_INHERIT
		 * is set, but ACL_ENTRY_DIRECTORY_INHERIT is not set, ensure
		 * that ACL_ENTRY_INHERIT_ONLY is set.
		 */
		if (is_directory &&
		    (entry->ae_flags & ACL_ENTRY_FILE_INHERIT) &&
		    ((entry->ae_flags & ACL_ENTRY_DIRECTORY_INHERIT) == 0)) {
			entry->ae_flags |= ACL_ENTRY_INHERIT_ONLY;
		}

		if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW &&
		    (entry->ae_flags & ACL_ENTRY_INHERIT_ONLY) == 0) {
			/*
			 * Some permissions must never be inherited.
			 */
			entry->ae_perm &= ~(ACL_WRITE_ACL | ACL_WRITE_OWNER |
			    ACL_WRITE_NAMED_ATTRS | ACL_WRITE_ATTRIBUTES);

			/*
			 * Others must be masked according to the file mode.
			 */
			if ((mode & S_IRGRP) == 0)
				entry->ae_perm &= ~ACL_READ_DATA;
			if ((mode & S_IWGRP) == 0)
				entry->ae_perm &=
				    ~(ACL_WRITE_DATA | ACL_APPEND_DATA);
			if ((mode & S_IXGRP) == 0)
				entry->ae_perm &= ~ACL_EXECUTE;
		}
	}
}
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
struct acl_entry {scalar_t__ ae_entry_type; int ae_flags; scalar_t__ ae_tag; int ae_perm; } ;
struct acl {int acl_cnt; struct acl_entry* acl_entry; } ;
typedef  int mode_t ;

/* Variables and functions */
 int ACL_ENTRY_INHERIT_ONLY ; 
 scalar_t__ ACL_ENTRY_TYPE_ALLOW ; 
 scalar_t__ ACL_ENTRY_TYPE_DENY ; 
 scalar_t__ ACL_EVERYONE ; 
 int ACL_EXECUTE ; 
 scalar_t__ ACL_GROUP_OBJ ; 
 int ACL_MAX_ENTRIES ; 
 int ACL_PRESERVE_MASK ; 
 int ACL_READ_DATA ; 
 scalar_t__ ACL_USER_OBJ ; 
 int ACL_WRITE_DATA ; 
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

void
acl_nfs4_sync_mode_from_acl(mode_t *_mode, const struct acl *aclp)
{
	int i;
	mode_t old_mode = *_mode, mode = 0, seen = 0;
	const struct acl_entry *entry;

	KASSERT(aclp->acl_cnt <= ACL_MAX_ENTRIES,
	    ("aclp->acl_cnt <= ACL_MAX_ENTRIES"));

	/*
	 * NFSv4 Minor Version 1, draft-ietf-nfsv4-minorversion1-03.txt
	 *
	 * 3.16.6.1. Recomputing mode upon SETATTR of ACL
	 */

	for (i = 0; i < aclp->acl_cnt; i++) {
		entry = &(aclp->acl_entry[i]);

		if (entry->ae_entry_type != ACL_ENTRY_TYPE_ALLOW &&
		    entry->ae_entry_type != ACL_ENTRY_TYPE_DENY)
			continue;

		if (entry->ae_flags & ACL_ENTRY_INHERIT_ONLY)
			continue;

		if (entry->ae_tag == ACL_USER_OBJ) {
			if ((entry->ae_perm & ACL_READ_DATA) &&
			    ((seen & S_IRUSR) == 0)) {
				seen |= S_IRUSR;
				if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
					mode |= S_IRUSR;
			}
			if ((entry->ae_perm & ACL_WRITE_DATA) &&
			     ((seen & S_IWUSR) == 0)) {
				seen |= S_IWUSR;
				if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
					mode |= S_IWUSR;
			}
			if ((entry->ae_perm & ACL_EXECUTE) &&
			    ((seen & S_IXUSR) == 0)) {
				seen |= S_IXUSR;
				if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
					mode |= S_IXUSR;
			}
		} else if (entry->ae_tag == ACL_GROUP_OBJ) {
			if ((entry->ae_perm & ACL_READ_DATA) &&
			    ((seen & S_IRGRP) == 0)) {
				seen |= S_IRGRP;
				if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
					mode |= S_IRGRP;
			}
			if ((entry->ae_perm & ACL_WRITE_DATA) &&
			    ((seen & S_IWGRP) == 0)) {
				seen |= S_IWGRP;
				if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
					mode |= S_IWGRP;
			}
			if ((entry->ae_perm & ACL_EXECUTE) &&
			    ((seen & S_IXGRP) == 0)) {
				seen |= S_IXGRP;
				if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
					mode |= S_IXGRP;
			}
		} else if (entry->ae_tag == ACL_EVERYONE) {
			if (entry->ae_perm & ACL_READ_DATA) {
				if ((seen & S_IRUSR) == 0) {
					seen |= S_IRUSR;
					if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
						mode |= S_IRUSR;
				}
				if ((seen & S_IRGRP) == 0) {
					seen |= S_IRGRP;
					if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
						mode |= S_IRGRP;
				}
				if ((seen & S_IROTH) == 0) {
					seen |= S_IROTH;
					if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
						mode |= S_IROTH;
				}
			}
			if (entry->ae_perm & ACL_WRITE_DATA) {
				if ((seen & S_IWUSR) == 0) {
					seen |= S_IWUSR;
					if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
						mode |= S_IWUSR;
				}
				if ((seen & S_IWGRP) == 0) {
					seen |= S_IWGRP;
					if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
						mode |= S_IWGRP;
				}
				if ((seen & S_IWOTH) == 0) {
					seen |= S_IWOTH;
					if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
						mode |= S_IWOTH;
				}
			}
			if (entry->ae_perm & ACL_EXECUTE) {
				if ((seen & S_IXUSR) == 0) {
					seen |= S_IXUSR;
					if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
						mode |= S_IXUSR;
				}
				if ((seen & S_IXGRP) == 0) {
					seen |= S_IXGRP;
					if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
						mode |= S_IXGRP;
				}
				if ((seen & S_IXOTH) == 0) {
					seen |= S_IXOTH;
					if (entry->ae_entry_type == ACL_ENTRY_TYPE_ALLOW)
						mode |= S_IXOTH;
				}
			}
		}
	}

	*_mode = mode | (old_mode & ACL_PRESERVE_MASK);
}
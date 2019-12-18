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
struct archive_acl {int acl_types; } ;

/* Variables and functions */
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 
 int ARCHIVE_ENTRY_ACL_TYPE_DEFAULT ; 
 int ARCHIVE_ENTRY_ACL_TYPE_NFS4 ; 
 int ARCHIVE_ENTRY_ACL_TYPE_POSIX1E ; 

__attribute__((used)) static int
archive_acl_text_want_type(struct archive_acl *acl, int flags)
{
	int want_type;

	/* Check if ACL is NFSv4 */
	if ((acl->acl_types & ARCHIVE_ENTRY_ACL_TYPE_NFS4) != 0) {
		/* NFSv4 should never mix with POSIX.1e */
		if ((acl->acl_types & ARCHIVE_ENTRY_ACL_TYPE_POSIX1E) != 0)
			return (0);
		else
			return (ARCHIVE_ENTRY_ACL_TYPE_NFS4);
	}

	/* Now deal with POSIX.1e ACLs */

	want_type = 0;
	if ((flags & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0)
		want_type |= ARCHIVE_ENTRY_ACL_TYPE_ACCESS;
	if ((flags & ARCHIVE_ENTRY_ACL_TYPE_DEFAULT) != 0)
		want_type |= ARCHIVE_ENTRY_ACL_TYPE_DEFAULT;

	/* By default we want both access and default ACLs */
	if (want_type == 0)
		return (ARCHIVE_ENTRY_ACL_TYPE_POSIX1E);

	return (want_type);
}
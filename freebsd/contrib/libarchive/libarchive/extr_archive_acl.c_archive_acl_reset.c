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
struct archive_acl {int /*<<< orphan*/  acl_head; int /*<<< orphan*/  acl_p; scalar_t__ acl_state; } ;

/* Variables and functions */
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 
 scalar_t__ ARCHIVE_ENTRY_ACL_USER_OBJ ; 
 int archive_acl_count (struct archive_acl*,int) ; 

int
archive_acl_reset(struct archive_acl *acl, int want_type)
{
	int count, cutoff;

	count = archive_acl_count(acl, want_type);

	/*
	 * If the only entries are the three standard ones,
	 * then don't return any ACL data.  (In this case,
	 * client can just use chmod(2) to set permissions.)
	 */
	if ((want_type & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0)
		cutoff = 3;
	else
		cutoff = 0;

	if (count > cutoff)
		acl->acl_state = ARCHIVE_ENTRY_ACL_USER_OBJ;
	else
		acl->acl_state = 0;
	acl->acl_p = acl->acl_head;
	return (count);
}
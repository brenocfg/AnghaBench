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
struct archive_acl_entry {int type; struct archive_acl_entry* next; } ;
struct archive_acl {struct archive_acl_entry* acl_head; } ;

/* Variables and functions */
 int ARCHIVE_ENTRY_ACL_TYPE_ACCESS ; 

int
archive_acl_count(struct archive_acl *acl, int want_type)
{
	int count;
	struct archive_acl_entry *ap;

	count = 0;
	ap = acl->acl_head;
	while (ap != NULL) {
		if ((ap->type & want_type) != 0)
			count++;
		ap = ap->next;
	}

	if (count > 0 && ((want_type & ARCHIVE_ENTRY_ACL_TYPE_ACCESS) != 0))
		count += 3;
	return (count);
}
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
struct archive_acl_entry {struct archive_acl_entry* next; int /*<<< orphan*/  name; int /*<<< orphan*/  id; int /*<<< orphan*/  tag; int /*<<< orphan*/  permset; int /*<<< orphan*/  type; } ;
struct archive_acl {struct archive_acl_entry* acl_head; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 struct archive_acl_entry* acl_new_entry (struct archive_acl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  archive_acl_clear (struct archive_acl*) ; 
 int /*<<< orphan*/  archive_mstring_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
archive_acl_copy(struct archive_acl *dest, struct archive_acl *src)
{
	struct archive_acl_entry *ap, *ap2;

	archive_acl_clear(dest);

	dest->mode = src->mode;
	ap = src->acl_head;
	while (ap != NULL) {
		ap2 = acl_new_entry(dest,
		    ap->type, ap->permset, ap->tag, ap->id);
		if (ap2 != NULL)
			archive_mstring_copy(&ap2->name, &ap->name);
		ap = ap->next;
	}
}
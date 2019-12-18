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
struct archive_acl_entry {int /*<<< orphan*/  name; struct archive_acl_entry* next; } ;
struct archive_acl {scalar_t__ acl_state; scalar_t__ acl_types; int /*<<< orphan*/ * acl_p; struct archive_acl_entry* acl_text; struct archive_acl_entry* acl_text_w; struct archive_acl_entry* acl_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  archive_mstring_clean (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct archive_acl_entry*) ; 

void
archive_acl_clear(struct archive_acl *acl)
{
	struct archive_acl_entry *ap;

	while (acl->acl_head != NULL) {
		ap = acl->acl_head->next;
		archive_mstring_clean(&acl->acl_head->name);
		free(acl->acl_head);
		acl->acl_head = ap;
	}
	free(acl->acl_text_w);
	acl->acl_text_w = NULL;
	free(acl->acl_text);
	acl->acl_text = NULL;
	acl->acl_p = NULL;
	acl->acl_types = 0;
	acl->acl_state = 0; /* Not counting. */
}
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
struct archive_entry {int /*<<< orphan*/ * sparse_tail; struct ae_sparse* sparse_head; } ;
struct ae_sparse {struct ae_sparse* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct ae_sparse*) ; 

void
archive_entry_sparse_clear(struct archive_entry *entry)
{
	struct ae_sparse *sp;

	while (entry->sparse_head != NULL) {
		sp = entry->sparse_head->next;
		free(entry->sparse_head);
		entry->sparse_head = sp;
	}
	entry->sparse_tail = NULL;
}
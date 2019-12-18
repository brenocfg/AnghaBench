#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct links_entry {struct links_entry* links_head; struct links_entry* name; struct links_entry* next; } ;
struct cpio {struct cpio* links_head; struct cpio* name; struct cpio* next; } ;
struct archive_read {TYPE_1__* format; } ;
struct TYPE_2__ {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int /*<<< orphan*/  free (struct links_entry*) ; 

__attribute__((used)) static int
archive_read_format_cpio_cleanup(struct archive_read *a)
{
	struct cpio *cpio;

	cpio = (struct cpio *)(a->format->data);
        /* Free inode->name map */
        while (cpio->links_head != NULL) {
                struct links_entry *lp = cpio->links_head->next;

                free(cpio->links_head->name);
                free(cpio->links_head);
                cpio->links_head = lp;
        }
	free(cpio);
	(a->format->data) = NULL;
	return (ARCHIVE_OK);
}
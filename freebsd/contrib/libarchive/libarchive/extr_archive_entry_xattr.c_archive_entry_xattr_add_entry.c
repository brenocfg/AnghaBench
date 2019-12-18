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
struct archive_entry {struct ae_xattr* xattr_head; } ;
struct ae_xattr {size_t size; struct ae_xattr* next; int /*<<< orphan*/ * value; int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  __archive_errx (int,char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 int /*<<< orphan*/ * strdup (char const*) ; 

void
archive_entry_xattr_add_entry(struct archive_entry *entry,
	const char *name, const void *value, size_t size)
{
	struct ae_xattr	*xp;

	if ((xp = (struct ae_xattr *)malloc(sizeof(struct ae_xattr))) == NULL)
		__archive_errx(1, "Out of memory");

	if ((xp->name = strdup(name)) == NULL)
		__archive_errx(1, "Out of memory");

	if ((xp->value = malloc(size)) != NULL) {
		memcpy(xp->value, value, size);
		xp->size = size;
	} else
		xp->size = 0;

	xp->next = entry->xattr_head;
	entry->xattr_head = xp;
}
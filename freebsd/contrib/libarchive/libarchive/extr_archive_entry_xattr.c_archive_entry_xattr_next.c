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
struct archive_entry {TYPE_1__* xattr_p; } ;
struct TYPE_2__ {char* name; void* value; size_t size; struct TYPE_2__* next; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 

int
archive_entry_xattr_next(struct archive_entry * entry,
	const char **name, const void **value, size_t *size)
{
	if (entry->xattr_p) {
		*name = entry->xattr_p->name;
		*value = entry->xattr_p->value;
		*size = entry->xattr_p->size;

		entry->xattr_p = entry->xattr_p->next;

		return (ARCHIVE_OK);
	} else {
		*name = NULL;
		*value = NULL;
		*size = (size_t)0;
		return (ARCHIVE_WARN);
	}
}
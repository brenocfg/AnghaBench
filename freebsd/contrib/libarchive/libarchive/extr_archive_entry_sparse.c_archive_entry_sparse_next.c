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
struct archive_entry {TYPE_1__* sparse_p; } ;
typedef  scalar_t__ la_int64_t ;
struct TYPE_2__ {struct TYPE_2__* next; scalar_t__ length; scalar_t__ offset; } ;

/* Variables and functions */
 int ARCHIVE_OK ; 
 int ARCHIVE_WARN ; 

int
archive_entry_sparse_next(struct archive_entry * entry,
	la_int64_t *offset, la_int64_t *length)
{
	if (entry->sparse_p) {
		*offset = entry->sparse_p->offset;
		*length = entry->sparse_p->length;

		entry->sparse_p = entry->sparse_p->next;

		return (ARCHIVE_OK);
	} else {
		*offset = 0;
		*length = 0;
		return (ARCHIVE_WARN);
	}
}
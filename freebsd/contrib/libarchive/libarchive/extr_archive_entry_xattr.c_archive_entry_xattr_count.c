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
struct ae_xattr {struct ae_xattr* next; } ;

/* Variables and functions */

int
archive_entry_xattr_count(struct archive_entry *entry)
{
	struct ae_xattr *xp;
	int count = 0;

	for (xp = entry->xattr_head; xp != NULL; xp = xp->next)
		count++;

	return count;
}
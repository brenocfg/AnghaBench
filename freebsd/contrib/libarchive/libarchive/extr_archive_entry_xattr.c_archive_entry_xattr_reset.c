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
struct archive_entry {int /*<<< orphan*/  xattr_head; int /*<<< orphan*/  xattr_p; } ;

/* Variables and functions */
 int archive_entry_xattr_count (struct archive_entry*) ; 

int
archive_entry_xattr_reset(struct archive_entry * entry)
{
	entry->xattr_p = entry->xattr_head;

	return archive_entry_xattr_count(entry);
}
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
struct disk_entry {int /*<<< orphan*/  index; } ;
struct device_entry {int flags; } ;

/* Variables and functions */
 int HR_DEVICE_IMMUTABLE ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct disk_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_entry_delete (struct device_entry*) ; 
 struct device_entry* device_find_by_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_tbl ; 
 int /*<<< orphan*/  free (struct disk_entry*) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
disk_entry_delete(struct disk_entry *entry)
{
	struct device_entry *devEntry;

	assert(entry != NULL);
	TAILQ_REMOVE(&disk_tbl, entry, link);

	devEntry = device_find_by_index(entry->index);

	free(entry);

	/*
	 * Also delete the respective device entry -
	 * this is needed for disk devices that are not
	 * detected by libdevinfo
	 */
	if (devEntry != NULL &&
	    (devEntry->flags & HR_DEVICE_IMMUTABLE) == HR_DEVICE_IMMUTABLE)
		device_entry_delete(devEntry);
}
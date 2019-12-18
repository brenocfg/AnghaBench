#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  TYPE_3__* vm_map_entry_t ;
struct TYPE_22__ {int /*<<< orphan*/ * vm_object; } ;
struct TYPE_24__ {scalar_t__ start; int eflags; scalar_t__ wired_count; scalar_t__ end; TYPE_1__ object; } ;
struct TYPE_23__ {unsigned int timestamp; scalar_t__ anon_loc; int /*<<< orphan*/  pmap; } ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int MAP_ENTRY_IN_TRANSITION ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int MAP_ENTRY_NEEDS_WAKEUP ; 
 int /*<<< orphan*/  VM_MAP_ASSERT_LOCKED (TYPE_2__*) ; 
 scalar_t__ kernel_pmap ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_end (TYPE_2__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_start (TYPE_2__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_entry_delete (TYPE_2__*,TYPE_3__*) ; 
 TYPE_3__* vm_map_entry_succ (TYPE_3__*) ; 
 scalar_t__ vm_map_entry_system_wired_count (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_entry_unwire (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (TYPE_2__*,scalar_t__,TYPE_3__**) ; 
 scalar_t__ vm_map_pmap (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_unlock_and_wait (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
vm_map_delete(vm_map_t map, vm_offset_t start, vm_offset_t end)
{
	vm_map_entry_t entry;
	vm_map_entry_t first_entry;

	VM_MAP_ASSERT_LOCKED(map);
	if (start == end)
		return (KERN_SUCCESS);

	/*
	 * Find the start of the region, and clip it
	 */
	if (!vm_map_lookup_entry(map, start, &first_entry))
		entry = vm_map_entry_succ(first_entry);
	else {
		entry = first_entry;
		vm_map_clip_start(map, entry, start);
	}

	/*
	 * Step through all entries in this region
	 */
	while (entry->start < end) {
		vm_map_entry_t next;

		/*
		 * Wait for wiring or unwiring of an entry to complete.
		 * Also wait for any system wirings to disappear on
		 * user maps.
		 */
		if ((entry->eflags & MAP_ENTRY_IN_TRANSITION) != 0 ||
		    (vm_map_pmap(map) != kernel_pmap &&
		    vm_map_entry_system_wired_count(entry) != 0)) {
			unsigned int last_timestamp;
			vm_offset_t saved_start;
			vm_map_entry_t tmp_entry;

			saved_start = entry->start;
			entry->eflags |= MAP_ENTRY_NEEDS_WAKEUP;
			last_timestamp = map->timestamp;
			(void) vm_map_unlock_and_wait(map, 0);
			vm_map_lock(map);
			if (last_timestamp + 1 != map->timestamp) {
				/*
				 * Look again for the entry because the map was
				 * modified while it was unlocked.
				 * Specifically, the entry may have been
				 * clipped, merged, or deleted.
				 */
				if (!vm_map_lookup_entry(map, saved_start,
							 &tmp_entry))
					entry = vm_map_entry_succ(tmp_entry);
				else {
					entry = tmp_entry;
					vm_map_clip_start(map, entry,
							  saved_start);
				}
			}
			continue;
		}
		vm_map_clip_end(map, entry, end);

		next = vm_map_entry_succ(entry);

		/*
		 * Unwire before removing addresses from the pmap; otherwise,
		 * unwiring will put the entries back in the pmap.
		 */
		if (entry->wired_count != 0)
			vm_map_entry_unwire(map, entry);

		/*
		 * Remove mappings for the pages, but only if the
		 * mappings could exist.  For instance, it does not
		 * make sense to call pmap_remove() for guard entries.
		 */
		if ((entry->eflags & MAP_ENTRY_IS_SUB_MAP) != 0 ||
		    entry->object.vm_object != NULL)
			pmap_remove(map->pmap, entry->start, entry->end);

		if (entry->end == map->anon_loc)
			map->anon_loc = entry->start;

		/*
		 * Delete the entry only after removing all pmap
		 * entries pointing to its pages.  (Otherwise, its
		 * page frames may be reallocated, and any modify bits
		 * will be set in the wrong object!)
		 */
		vm_map_entry_delete(map, entry);
		entry = next;
	}
	return (KERN_SUCCESS);
}
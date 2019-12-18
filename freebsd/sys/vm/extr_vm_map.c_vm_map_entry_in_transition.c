#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_1__* vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
typedef  scalar_t__ u_int ;
struct TYPE_14__ {int eflags; int /*<<< orphan*/  start; } ;
struct TYPE_13__ {scalar_t__ timestamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAP_ENTRY_IN_TRANSITION ; 
 int MAP_ENTRY_NEEDS_WAKEUP ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_MAP_ASSERT_LOCKED (TYPE_1__*) ; 
 TYPE_2__* vm_map_entry_succ (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_lookup_entry (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 scalar_t__ vm_map_unlock_and_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static vm_map_entry_t
vm_map_entry_in_transition(vm_map_t map, vm_offset_t in_start,
    vm_offset_t *io_end, bool holes_ok, vm_map_entry_t in_entry)
{
	vm_map_entry_t entry;
	vm_offset_t start;
	u_int last_timestamp;

	VM_MAP_ASSERT_LOCKED(map);
	KASSERT((in_entry->eflags & MAP_ENTRY_IN_TRANSITION) != 0,
	    ("not in-tranition map entry %p", in_entry));
	/*
	 * We have not yet clipped the entry.
	 */
	start = MAX(in_start, in_entry->start);
	in_entry->eflags |= MAP_ENTRY_NEEDS_WAKEUP;
	last_timestamp = map->timestamp;
	if (vm_map_unlock_and_wait(map, 0)) {
		/*
		 * Allow interruption of user wiring/unwiring?
		 */
	}
	vm_map_lock(map);
	if (last_timestamp + 1 == map->timestamp)
		return (in_entry);

	/*
	 * Look again for the entry because the map was modified while it was
	 * unlocked.  Specifically, the entry may have been clipped, merged, or
	 * deleted.
	 */
	if (!vm_map_lookup_entry(map, start, &entry)) {
		if (!holes_ok) {
			*io_end = start;
			return (NULL);
		}
		entry = vm_map_entry_succ(entry);
	}
	return (entry);
}
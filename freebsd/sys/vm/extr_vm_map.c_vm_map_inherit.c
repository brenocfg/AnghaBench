#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_1__* vm_map_entry_t ;
typedef  int vm_inherit_t ;
struct TYPE_9__ {int eflags; int inheritance; int /*<<< orphan*/  start; } ;

/* Variables and functions */
 int KERN_INVALID_ARGUMENT ; 
 int KERN_SUCCESS ; 
 int MAP_ENTRY_GUARD ; 
#define  VM_INHERIT_COPY 131 
#define  VM_INHERIT_NONE 130 
#define  VM_INHERIT_SHARE 129 
#define  VM_INHERIT_ZERO 128 
 int /*<<< orphan*/  VM_MAP_RANGE_CHECK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_clip_end (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_clip_start (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_entry_pred (TYPE_1__*) ; 
 TYPE_1__* vm_map_entry_succ (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_lookup_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  vm_map_try_merge_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_unlock (int /*<<< orphan*/ ) ; 

int
vm_map_inherit(vm_map_t map, vm_offset_t start, vm_offset_t end,
	       vm_inherit_t new_inheritance)
{
	vm_map_entry_t entry;
	vm_map_entry_t temp_entry;

	switch (new_inheritance) {
	case VM_INHERIT_NONE:
	case VM_INHERIT_COPY:
	case VM_INHERIT_SHARE:
	case VM_INHERIT_ZERO:
		break;
	default:
		return (KERN_INVALID_ARGUMENT);
	}
	if (start == end)
		return (KERN_SUCCESS);
	vm_map_lock(map);
	VM_MAP_RANGE_CHECK(map, start, end);
	if (vm_map_lookup_entry(map, start, &temp_entry)) {
		entry = temp_entry;
		vm_map_clip_start(map, entry, start);
	} else
		entry = vm_map_entry_succ(temp_entry);
	while (entry->start < end) {
		vm_map_clip_end(map, entry, end);
		if ((entry->eflags & MAP_ENTRY_GUARD) == 0 ||
		    new_inheritance != VM_INHERIT_ZERO)
			entry->inheritance = new_inheritance;
		vm_map_try_merge_entries(map, vm_map_entry_pred(entry), entry);
		entry = vm_map_entry_succ(entry);
	}
	vm_map_try_merge_entries(map, vm_map_entry_pred(entry), entry);
	vm_map_unlock(map);
	return (KERN_SUCCESS);
}
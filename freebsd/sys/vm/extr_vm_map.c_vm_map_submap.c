#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  TYPE_3__* vm_map_entry_t ;
struct TYPE_17__ {TYPE_2__* sub_map; int /*<<< orphan*/ * vm_object; } ;
struct TYPE_19__ {scalar_t__ start; scalar_t__ end; int eflags; TYPE_1__ object; } ;
struct TYPE_18__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int KERN_INVALID_ARGUMENT ; 
 int KERN_SUCCESS ; 
 int MAP_ENTRY_COW ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int /*<<< orphan*/  MAP_IS_SUB_MAP ; 
 int /*<<< orphan*/  VM_MAP_RANGE_CHECK (TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_end (TYPE_2__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  vm_map_clip_start (TYPE_2__*,TYPE_3__*,scalar_t__) ; 
 TYPE_3__* vm_map_entry_succ (TYPE_3__*) ; 
 int /*<<< orphan*/  vm_map_lock (TYPE_2__*) ; 
 scalar_t__ vm_map_lookup_entry (TYPE_2__*,scalar_t__,TYPE_3__**) ; 
 int /*<<< orphan*/  vm_map_unlock (TYPE_2__*) ; 

int
vm_map_submap(
	vm_map_t map,
	vm_offset_t start,
	vm_offset_t end,
	vm_map_t submap)
{
	vm_map_entry_t entry;
	int result;

	result = KERN_INVALID_ARGUMENT;

	vm_map_lock(submap);
	submap->flags |= MAP_IS_SUB_MAP;
	vm_map_unlock(submap);

	vm_map_lock(map);

	VM_MAP_RANGE_CHECK(map, start, end);

	if (vm_map_lookup_entry(map, start, &entry)) {
		vm_map_clip_start(map, entry, start);
	} else
		entry = vm_map_entry_succ(entry);

	vm_map_clip_end(map, entry, end);

	if ((entry->start == start) && (entry->end == end) &&
	    ((entry->eflags & MAP_ENTRY_COW) == 0) &&
	    (entry->object.vm_object == NULL)) {
		entry->object.sub_map = submap;
		entry->eflags |= MAP_ENTRY_IS_SUB_MAP;
		result = KERN_SUCCESS;
	}
	vm_map_unlock(map);

	if (result != KERN_SUCCESS) {
		vm_map_lock(submap);
		submap->flags &= ~MAP_IS_SUB_MAP;
		vm_map_unlock(submap);
	}
	return (result);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_8__ {int /*<<< orphan*/  vm_object; } ;
struct TYPE_9__ {scalar_t__ start; scalar_t__ end; int eflags; TYPE_1__ object; int /*<<< orphan*/ * cred; int /*<<< orphan*/  offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int /*<<< orphan*/  VM_MAP_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_entry_charge_object (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* vm_map_entry_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_entry_link (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_map_entry_set_vnode_text (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_object_reference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_vm_map_clip_end(vm_map_t map, vm_map_entry_t entry, vm_offset_t end)
{
	vm_map_entry_t new_entry;

	VM_MAP_ASSERT_LOCKED(map);
	KASSERT(entry->start < end && entry->end > end,
	    ("_vm_map_clip_end: invalid clip of entry %p", entry));

	/*
	 * Create a backing object now, if none exists, so that more individual
	 * objects won't be created after the map entry is split.
	 */
	vm_map_entry_charge_object(map, entry);

	/* Clone the entry. */
	new_entry = vm_map_entry_create(map);
	*new_entry = *entry;

	/*
	 * Split off the back portion.  Insert the new entry AFTER this one,
	 * so that this entry has the specified ending address.
	 */
	new_entry->start = entry->end = end;
	new_entry->offset += (end - entry->start);
	if (new_entry->cred != NULL)
		crhold(entry->cred);

	vm_map_entry_link(map, new_entry);

	if ((entry->eflags & MAP_ENTRY_IS_SUB_MAP) == 0) {
		vm_object_reference(new_entry->object.vm_object);
		vm_map_entry_set_vnode_text(new_entry, true);
	}
}
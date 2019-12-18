#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_1__* vm_map_entry_t ;
struct TYPE_8__ {int eflags; } ;

/* Variables and functions */
 int MAP_ENTRY_NOMERGE_MASK ; 
 int /*<<< orphan*/  UNLINK_MERGE_NEXT ; 
 int /*<<< orphan*/  VM_MAP_ASSERT_LOCKED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_entry_unlink (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_mergeable_neighbors (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_merged_neighbor_dispose (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
vm_map_try_merge_entries(vm_map_t map, vm_map_entry_t prev, vm_map_entry_t entry)
{

	VM_MAP_ASSERT_LOCKED(map);
	if ((entry->eflags & MAP_ENTRY_NOMERGE_MASK) == 0 &&
	    vm_map_mergeable_neighbors(prev, entry)) {
		vm_map_entry_unlink(map, prev, UNLINK_MERGE_NEXT);
		vm_map_merged_neighbor_dispose(map, prev);
	}
}
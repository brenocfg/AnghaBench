#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;
struct vmspace {int /*<<< orphan*/  vm_tsize; scalar_t__ vm_taddr; int /*<<< orphan*/  vm_dsize; scalar_t__ vm_daddr; int /*<<< orphan*/  vm_ssize; TYPE_1__ vm_map; } ;
struct TYPE_5__ {int eflags; scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int MAP_ENTRY_GROWS_DOWN ; 
 int MAP_ENTRY_GROWS_UP ; 
 int MAP_ENTRY_GUARD ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 scalar_t__ btoc (scalar_t__) ; 
 scalar_t__ ctob (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vmspace_map_entry_forked(const struct vmspace *vm1, struct vmspace *vm2,
    vm_map_entry_t entry)
{
	vm_size_t entrysize;
	vm_offset_t newend;

	if ((entry->eflags & MAP_ENTRY_GUARD) != 0)
		return;
	entrysize = entry->end - entry->start;
	vm2->vm_map.size += entrysize;
	if (entry->eflags & (MAP_ENTRY_GROWS_DOWN | MAP_ENTRY_GROWS_UP)) {
		vm2->vm_ssize += btoc(entrysize);
	} else if (entry->start >= (vm_offset_t)vm1->vm_daddr &&
	    entry->start < (vm_offset_t)vm1->vm_daddr + ctob(vm1->vm_dsize)) {
		newend = MIN(entry->end,
		    (vm_offset_t)vm1->vm_daddr + ctob(vm1->vm_dsize));
		vm2->vm_dsize += btoc(newend - entry->start);
	} else if (entry->start >= (vm_offset_t)vm1->vm_taddr &&
	    entry->start < (vm_offset_t)vm1->vm_taddr + ctob(vm1->vm_tsize)) {
		newend = MIN(entry->end,
		    (vm_offset_t)vm1->vm_taddr + ctob(vm1->vm_tsize));
		vm2->vm_tsize += btoc(newend - entry->start);
	}
}
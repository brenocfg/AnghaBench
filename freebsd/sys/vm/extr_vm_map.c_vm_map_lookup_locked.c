#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  TYPE_3__* vm_map_entry_t ;
typedef  int boolean_t ;
struct TYPE_8__ {int /*<<< orphan*/ * vm_object; } ;
struct TYPE_10__ {int eflags; int protection; scalar_t__ wired_count; TYPE_1__ object; scalar_t__ offset; scalar_t__ start; } ;
struct TYPE_9__ {int /*<<< orphan*/  system_map; } ;

/* Variables and functions */
 int KERN_FAILURE ; 
 int KERN_INVALID_ADDRESS ; 
 int KERN_PROTECTION_FAILURE ; 
 int KERN_SUCCESS ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int MAP_ENTRY_NEEDS_COPY ; 
 int /*<<< orphan*/  OFF_TO_IDX (scalar_t__) ; 
 int VM_PROT_EXECUTE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  vm_map_lookup_entry (TYPE_2__*,scalar_t__,TYPE_3__**) ; 

int
vm_map_lookup_locked(vm_map_t *var_map,		/* IN/OUT */
		     vm_offset_t vaddr,
		     vm_prot_t fault_typea,
		     vm_map_entry_t *out_entry,	/* OUT */
		     vm_object_t *object,	/* OUT */
		     vm_pindex_t *pindex,	/* OUT */
		     vm_prot_t *out_prot,	/* OUT */
		     boolean_t *wired)		/* OUT */
{
	vm_map_entry_t entry;
	vm_map_t map = *var_map;
	vm_prot_t prot;
	vm_prot_t fault_type = fault_typea;

	/*
	 * Lookup the faulting address.
	 */
	if (!vm_map_lookup_entry(map, vaddr, out_entry))
		return (KERN_INVALID_ADDRESS);

	entry = *out_entry;

	/*
	 * Fail if the entry refers to a submap.
	 */
	if (entry->eflags & MAP_ENTRY_IS_SUB_MAP)
		return (KERN_FAILURE);

	/*
	 * Check whether this task is allowed to have this page.
	 */
	prot = entry->protection;
	fault_type &= VM_PROT_READ | VM_PROT_WRITE | VM_PROT_EXECUTE;
	if ((fault_type & prot) != fault_type)
		return (KERN_PROTECTION_FAILURE);

	/*
	 * If this page is not pageable, we have to get it for all possible
	 * accesses.
	 */
	*wired = (entry->wired_count != 0);
	if (*wired)
		fault_type = entry->protection;

	if (entry->eflags & MAP_ENTRY_NEEDS_COPY) {
		/*
		 * Fail if the entry was copy-on-write for a write fault.
		 */
		if (fault_type & VM_PROT_WRITE)
			return (KERN_FAILURE);
		/*
		 * We're attempting to read a copy-on-write page --
		 * don't allow writes.
		 */
		prot &= ~VM_PROT_WRITE;
	}

	/*
	 * Fail if an object should be created.
	 */
	if (entry->object.vm_object == NULL && !map->system_map)
		return (KERN_FAILURE);

	/*
	 * Return the object/offset from this entry.  If the entry was
	 * copy-on-write or empty, it has been fixed up.
	 */
	*pindex = OFF_TO_IDX((vaddr - entry->start) + entry->offset);
	*object = entry->object.vm_object;

	*out_prot = prot;
	return (KERN_SUCCESS);
}
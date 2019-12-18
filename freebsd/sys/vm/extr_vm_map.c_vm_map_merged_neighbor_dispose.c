#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/ * vm_object; } ;
struct TYPE_6__ {int /*<<< orphan*/ * cred; TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  crfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_entry_dispose (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  vm_object_deallocate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vm_map_merged_neighbor_dispose(vm_map_t map, vm_map_entry_t entry)
{

	/*
	 * If the backing object is a vnode object, vm_object_deallocate()
	 * calls vrele().  However, vrele() does not lock the vnode because
	 * the vnode has additional references.  Thus, the map lock can be
	 * kept without causing a lock-order reversal with the vnode lock.
	 *
	 * Since we count the number of virtual page mappings in
	 * object->un_pager.vnp.writemappings, the writemappings value
	 * should not be adjusted when the entry is disposed of.
	 */
	if (entry->object.vm_object != NULL)
		vm_object_deallocate(entry->object.vm_object);
	if (entry->cred != NULL)
		crfree(entry->cred);
	vm_map_entry_dispose(map, entry);
}
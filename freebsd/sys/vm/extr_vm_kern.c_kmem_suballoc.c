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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  MAP_ACC_NO_CHARGE ; 
 int /*<<< orphan*/  VMFS_ANY_SPACE ; 
 int /*<<< orphan*/  VMFS_SUPER_SPACE ; 
 int /*<<< orphan*/  VM_PROT_ALL ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 scalar_t__ round_page (scalar_t__) ; 
 int /*<<< orphan*/ * vm_map_create (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int vm_map_find (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_map_min (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_map_pmap (int /*<<< orphan*/ *) ; 
 int vm_map_submap (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

vm_map_t
kmem_suballoc(vm_map_t parent, vm_offset_t *min, vm_offset_t *max,
    vm_size_t size, boolean_t superpage_align)
{
	int ret;
	vm_map_t result;

	size = round_page(size);

	*min = vm_map_min(parent);
	ret = vm_map_find(parent, NULL, 0, min, size, 0, superpage_align ?
	    VMFS_SUPER_SPACE : VMFS_ANY_SPACE, VM_PROT_ALL, VM_PROT_ALL,
	    MAP_ACC_NO_CHARGE);
	if (ret != KERN_SUCCESS)
		panic("kmem_suballoc: bad status return of %d", ret);
	*max = *min + size;
	result = vm_map_create(vm_map_pmap(parent), *min, *max);
	if (result == NULL)
		panic("kmem_suballoc: cannot create submap");
	if (vm_map_submap(parent, *min, *max, result) != KERN_SUCCESS)
		panic("kmem_suballoc: unable to change range to submap");
	return (result);
}
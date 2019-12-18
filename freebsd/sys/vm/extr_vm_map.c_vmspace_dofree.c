#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * pmap; } ;
struct vmspace {TYPE_1__ vm_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,struct vmspace*) ; 
 int /*<<< orphan*/  KTR_VM ; 
 int /*<<< orphan*/  pmap_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shmexit (struct vmspace*) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct vmspace*) ; 
 int /*<<< orphan*/  vm_map_max (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_min (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_map_remove (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmspace_pmap (struct vmspace*) ; 
 int /*<<< orphan*/  vmspace_zone ; 

__attribute__((used)) static inline void
vmspace_dofree(struct vmspace *vm)
{

	CTR1(KTR_VM, "vmspace_free: %p", vm);

	/*
	 * Make sure any SysV shm is freed, it might not have been in
	 * exit1().
	 */
	shmexit(vm);

	/*
	 * Lock the map, to wait out all other references to it.
	 * Delete all of the mappings and pages they hold, then call
	 * the pmap module to reclaim anything left.
	 */
	(void)vm_map_remove(&vm->vm_map, vm_map_min(&vm->vm_map),
	    vm_map_max(&vm->vm_map));

	pmap_release(vmspace_pmap(vm));
	vm->vm_map.pmap = NULL;
	uma_zfree(vmspace_zone, vm);
}
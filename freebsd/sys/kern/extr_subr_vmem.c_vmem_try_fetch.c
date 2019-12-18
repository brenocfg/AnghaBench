#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ vm_qcache_max; scalar_t__ vm_size; scalar_t__ vm_inuse; int /*<<< orphan*/  (* vm_reclaimfn ) (TYPE_1__*,int) ;} ;
typedef  TYPE_1__ vmem_t ;
typedef  scalar_t__ vmem_size_t ;

/* Variables and functions */
 int M_NOWAIT ; 
 int /*<<< orphan*/  VMEM_ASSERT_LOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  VMEM_CONDVAR_WAIT (TYPE_1__*) ; 
 int /*<<< orphan*/  VMEM_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VMEM_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  qc_drain (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 scalar_t__ vmem_import (TYPE_1__*,scalar_t__ const,scalar_t__,int) ; 

__attribute__((used)) static int
vmem_try_fetch(vmem_t *vm, const vmem_size_t size, vmem_size_t align, int flags)
{
	vmem_size_t avail;

	VMEM_ASSERT_LOCKED(vm);

	/*
	 * XXX it is possible to fail to meet xalloc constraints with the
	 * imported region.  It is up to the user to specify the
	 * import quantum such that it can satisfy any allocation.
	 */
	if (vmem_import(vm, size, align, flags) == 0)
		return (1);

	/*
	 * Try to free some space from the quantum cache or reclaim
	 * functions if available.
	 */
	if (vm->vm_qcache_max != 0 || vm->vm_reclaimfn != NULL) {
		avail = vm->vm_size - vm->vm_inuse;
		VMEM_UNLOCK(vm);
		if (vm->vm_qcache_max != 0)
			qc_drain(vm);
		if (vm->vm_reclaimfn != NULL)
			vm->vm_reclaimfn(vm, flags);
		VMEM_LOCK(vm);
		/* If we were successful retry even NOWAIT. */
		if (vm->vm_size - vm->vm_inuse > avail)
			return (1);
	}
	if ((flags & M_NOWAIT) != 0)
		return (0);
	VMEM_CONDVAR_WAIT(vm);
	return (1);
}
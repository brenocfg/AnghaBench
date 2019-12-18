#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_offset_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pmap; } ;
struct vmspace {int vm_refcnt; scalar_t__ vm_maxsaddr; scalar_t__ vm_daddr; scalar_t__ vm_taddr; scalar_t__ vm_ssize; scalar_t__ vm_dsize; scalar_t__ vm_tsize; scalar_t__ vm_swrss; int /*<<< orphan*/ * vm_shm; TYPE_1__ vm_map; } ;
typedef  int /*<<< orphan*/  (* pmap_pinit_t ) (int /*<<< orphan*/ ) ;

/* Variables and functions */
 int /*<<< orphan*/  CTR1 (int /*<<< orphan*/ ,char*,struct vmspace*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  KTR_VM ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  _vm_map_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vmspace* uma_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uma_zfree (int /*<<< orphan*/ ,struct vmspace*) ; 
 int /*<<< orphan*/  vmspace_pmap (struct vmspace*) ; 
 int /*<<< orphan*/  vmspace_zone ; 

struct vmspace *
vmspace_alloc(vm_offset_t min, vm_offset_t max, pmap_pinit_t pinit)
{
	struct vmspace *vm;

	vm = uma_zalloc(vmspace_zone, M_WAITOK);
	KASSERT(vm->vm_map.pmap == NULL, ("vm_map.pmap must be NULL"));
	if (!pinit(vmspace_pmap(vm))) {
		uma_zfree(vmspace_zone, vm);
		return (NULL);
	}
	CTR1(KTR_VM, "vmspace_alloc: %p", vm);
	_vm_map_init(&vm->vm_map, vmspace_pmap(vm), min, max);
	vm->vm_refcnt = 1;
	vm->vm_shm = NULL;
	vm->vm_swrss = 0;
	vm->vm_tsize = 0;
	vm->vm_dsize = 0;
	vm->vm_ssize = 0;
	vm->vm_taddr = 0;
	vm->vm_daddr = 0;
	vm->vm_maxsaddr = 0;
	return (vm);
}
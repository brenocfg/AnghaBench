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
struct vm {int maxcpus; int /*<<< orphan*/ * vmspace; struct mem_map* mem_maps; int /*<<< orphan*/  cookie; int /*<<< orphan*/  vioapic; int /*<<< orphan*/  vatpic; int /*<<< orphan*/  vhpet; int /*<<< orphan*/  vatpit; int /*<<< orphan*/  vpmtmr; int /*<<< orphan*/  vrtc; int /*<<< orphan*/ * iommu; } ;
struct mem_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VMCLEANUP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VMSPACE_FREE (int /*<<< orphan*/ *) ; 
 int VM_MAX_MEMMAPS ; 
 int VM_MAX_MEMSEGS ; 
 int /*<<< orphan*/  iommu_destroy_domain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppt_unassign_all (struct vm*) ; 
 int /*<<< orphan*/  sysmem_mapping (struct vm*,struct mem_map*) ; 
 int /*<<< orphan*/  vatpic_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vatpit_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_cleanup (struct vm*,int,int) ; 
 int /*<<< orphan*/  vhpet_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vioapic_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_free_memmap (struct vm*,int) ; 
 int /*<<< orphan*/  vm_free_memseg (struct vm*,int) ; 
 int /*<<< orphan*/  vpmtmr_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrtc_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vrtc_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_cleanup(struct vm *vm, bool destroy)
{
	struct mem_map *mm;
	int i;

	ppt_unassign_all(vm);

	if (vm->iommu != NULL)
		iommu_destroy_domain(vm->iommu);

	if (destroy)
		vrtc_cleanup(vm->vrtc);
	else
		vrtc_reset(vm->vrtc);
	vpmtmr_cleanup(vm->vpmtmr);
	vatpit_cleanup(vm->vatpit);
	vhpet_cleanup(vm->vhpet);
	vatpic_cleanup(vm->vatpic);
	vioapic_cleanup(vm->vioapic);

	for (i = 0; i < vm->maxcpus; i++)
		vcpu_cleanup(vm, i, destroy);

	VMCLEANUP(vm->cookie);

	/*
	 * System memory is removed from the guest address space only when
	 * the VM is destroyed. This is because the mapping remains the same
	 * across VM reset.
	 *
	 * Device memory can be relocated by the guest (e.g. using PCI BARs)
	 * so those mappings are removed on a VM reset.
	 */
	for (i = 0; i < VM_MAX_MEMMAPS; i++) {
		mm = &vm->mem_maps[i];
		if (destroy || !sysmem_mapping(vm, mm))
			vm_free_memmap(vm, i);
	}

	if (destroy) {
		for (i = 0; i < VM_MAX_MEMSEGS; i++)
			vm_free_memseg(vm, i);

		VMSPACE_FREE(vm->vmspace);
		vm->vmspace = NULL;
	}
}
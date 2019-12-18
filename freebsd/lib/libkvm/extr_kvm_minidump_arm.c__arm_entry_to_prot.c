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
typedef  int /*<<< orphan*/  vm_prot_t ;
struct TYPE_4__ {scalar_t__ mmuformat; } ;
struct vmstate {TYPE_1__ hdr; } ;
struct TYPE_5__ {struct vmstate* vmst; } ;
typedef  TYPE_2__ kvm_t ;
typedef  int arm_pt_entry_t ;

/* Variables and functions */
 int ARM_L2_S_PROT_W ; 
 int ARM_PTE2_NX ; 
 int ARM_PTE2_RO ; 
 scalar_t__ MINIDUMP_MMU_FORMAT_V4 ; 
 int /*<<< orphan*/  VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 

__attribute__((used)) static vm_prot_t
_arm_entry_to_prot(kvm_t *kd, arm_pt_entry_t pte)
{
	struct vmstate *vm = kd->vmst;
	vm_prot_t prot = VM_PROT_READ;

	/* Source: arm/arm/pmap-v4.c:pmap_fault_fixup() */
	if (vm->hdr.mmuformat == MINIDUMP_MMU_FORMAT_V4) {
		if (pte & ARM_L2_S_PROT_W)
			prot |= VM_PROT_WRITE;
		return prot;
	}

	/* Source: arm/arm/pmap-v6.c:pmap_protect() */
	if ((pte & ARM_PTE2_RO) == 0)
		prot |= VM_PROT_WRITE;
	if ((pte & ARM_PTE2_NX) == 0)
		prot |= VM_PROT_EXECUTE;
	return prot;
}
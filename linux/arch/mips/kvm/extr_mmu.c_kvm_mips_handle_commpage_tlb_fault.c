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
struct TYPE_2__ {int /*<<< orphan*/  kseg0_commpage; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SHARED ; 
 int /*<<< orphan*/  PFN_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_err (char*,unsigned long) ; 
 int /*<<< orphan*/  kvm_mips_host_tlb_inv (struct kvm_vcpu*,unsigned long,int,int) ; 
 int /*<<< orphan*/ * kvm_trap_emul_pte_for_gva (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  pfn_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkdirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_mkyoung (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

int kvm_mips_handle_commpage_tlb_fault(unsigned long badvaddr,
				       struct kvm_vcpu *vcpu)
{
	kvm_pfn_t pfn;
	pte_t *ptep;

	ptep = kvm_trap_emul_pte_for_gva(vcpu, badvaddr);
	if (!ptep) {
		kvm_err("No ptep for commpage %lx\n", badvaddr);
		return -1;
	}

	pfn = PFN_DOWN(virt_to_phys(vcpu->arch.kseg0_commpage));
	/* Also set valid and dirty, so refill handler doesn't have to */
	*ptep = pte_mkyoung(pte_mkdirty(pfn_pte(pfn, PAGE_SHARED)));

	/* Invalidate this entry in the TLB, guest kernel ASID only */
	kvm_mips_host_tlb_inv(vcpu, badvaddr, false, true);
	return 0;
}
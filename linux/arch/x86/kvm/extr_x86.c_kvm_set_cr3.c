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
typedef  int /*<<< orphan*/  ulong ;
struct TYPE_2__ {unsigned long cr3; int /*<<< orphan*/  regs_avail; int /*<<< orphan*/  walk_mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_TLB_FLUSH ; 
 int /*<<< orphan*/  VCPU_EXREG_CR3 ; 
 unsigned long X86_CR3_PCID_NOFLUSH ; 
 int /*<<< orphan*/  X86_CR4_PCIDE ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpuid_maxphyaddr (struct kvm_vcpu*) ; 
 scalar_t__ is_long_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_pae_paging (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_new_cr3 (struct kvm_vcpu*,unsigned long,int) ; 
 int /*<<< orphan*/  kvm_mmu_sync_roots (struct kvm_vcpu*) ; 
 unsigned long kvm_read_cr3 (struct kvm_vcpu*) ; 
 int kvm_read_cr4_bits (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  load_pdptrs (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pdptrs_changed (struct kvm_vcpu*) ; 
 unsigned long rsvd_bits (int /*<<< orphan*/ ,int) ; 

int kvm_set_cr3(struct kvm_vcpu *vcpu, unsigned long cr3)
{
	bool skip_tlb_flush = false;
#ifdef CONFIG_X86_64
	bool pcid_enabled = kvm_read_cr4_bits(vcpu, X86_CR4_PCIDE);

	if (pcid_enabled) {
		skip_tlb_flush = cr3 & X86_CR3_PCID_NOFLUSH;
		cr3 &= ~X86_CR3_PCID_NOFLUSH;
	}
#endif

	if (cr3 == kvm_read_cr3(vcpu) && !pdptrs_changed(vcpu)) {
		if (!skip_tlb_flush) {
			kvm_mmu_sync_roots(vcpu);
			kvm_make_request(KVM_REQ_TLB_FLUSH, vcpu);
		}
		return 0;
	}

	if (is_long_mode(vcpu) &&
	    (cr3 & rsvd_bits(cpuid_maxphyaddr(vcpu), 63)))
		return 1;
	else if (is_pae_paging(vcpu) &&
		 !load_pdptrs(vcpu, vcpu->arch.walk_mmu, cr3))
		return 1;

	kvm_mmu_new_cr3(vcpu, cr3, skip_tlb_flush);
	vcpu->arch.cr3 = cr3;
	__set_bit(VCPU_EXREG_CR3, (ulong *)&vcpu->arch.regs_avail);

	return 0;
}
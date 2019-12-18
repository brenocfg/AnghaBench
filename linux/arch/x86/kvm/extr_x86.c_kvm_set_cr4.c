#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  walk_mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {scalar_t__ (* set_cr4 ) (struct kvm_vcpu*,unsigned long) ;} ;

/* Variables and functions */
 int X86_CR3_PCID_MASK ; 
 unsigned long X86_CR4_OSXSAVE ; 
 unsigned long X86_CR4_PAE ; 
 unsigned long X86_CR4_PCIDE ; 
 unsigned long X86_CR4_PGE ; 
 unsigned long X86_CR4_PKE ; 
 unsigned long X86_CR4_PSE ; 
 unsigned long X86_CR4_SMAP ; 
 unsigned long X86_CR4_SMEP ; 
 int /*<<< orphan*/  X86_FEATURE_PCID ; 
 int /*<<< orphan*/  guest_cpuid_has (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_long_mode (struct kvm_vcpu*) ; 
 scalar_t__ is_paging (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_reset_context (struct kvm_vcpu*) ; 
 int kvm_read_cr3 (struct kvm_vcpu*) ; 
 unsigned long kvm_read_cr4 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_update_cpuid (struct kvm_vcpu*) ; 
 scalar_t__ kvm_valid_cr4 (struct kvm_vcpu*,unsigned long) ; 
 TYPE_2__* kvm_x86_ops ; 
 int /*<<< orphan*/  load_pdptrs (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct kvm_vcpu*,unsigned long) ; 

int kvm_set_cr4(struct kvm_vcpu *vcpu, unsigned long cr4)
{
	unsigned long old_cr4 = kvm_read_cr4(vcpu);
	unsigned long pdptr_bits = X86_CR4_PGE | X86_CR4_PSE | X86_CR4_PAE |
				   X86_CR4_SMEP | X86_CR4_SMAP | X86_CR4_PKE;

	if (kvm_valid_cr4(vcpu, cr4))
		return 1;

	if (is_long_mode(vcpu)) {
		if (!(cr4 & X86_CR4_PAE))
			return 1;
	} else if (is_paging(vcpu) && (cr4 & X86_CR4_PAE)
		   && ((cr4 ^ old_cr4) & pdptr_bits)
		   && !load_pdptrs(vcpu, vcpu->arch.walk_mmu,
				   kvm_read_cr3(vcpu)))
		return 1;

	if ((cr4 & X86_CR4_PCIDE) && !(old_cr4 & X86_CR4_PCIDE)) {
		if (!guest_cpuid_has(vcpu, X86_FEATURE_PCID))
			return 1;

		/* PCID can not be enabled when cr3[11:0]!=000H or EFER.LMA=0 */
		if ((kvm_read_cr3(vcpu) & X86_CR3_PCID_MASK) || !is_long_mode(vcpu))
			return 1;
	}

	if (kvm_x86_ops->set_cr4(vcpu, cr4))
		return 1;

	if (((cr4 ^ old_cr4) & pdptr_bits) ||
	    (!(cr4 & X86_CR4_PCIDE) && (old_cr4 & X86_CR4_PCIDE)))
		kvm_mmu_reset_context(vcpu);

	if ((cr4 ^ old_cr4) & (X86_CR4_OSXSAVE | X86_CR4_PKE))
		kvm_update_cpuid(vcpu);

	return 0;
}
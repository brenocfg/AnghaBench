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
typedef  int ulong ;
struct TYPE_2__ {int shadow_msrp; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int MSRP_DEP ; 
 int MSRP_PMMP ; 
 int MSRP_UCLEP ; 
 int MSR_DE ; 
 int MSR_PMM ; 
 int MSR_UCLE ; 

void kvm_guest_protect_msr(struct kvm_vcpu *vcpu, ulong prot_bitmap, bool set)
{
	/* XXX: Add similar MSR protection for BookE-PR */
#ifdef CONFIG_KVM_BOOKE_HV
	BUG_ON(prot_bitmap & ~(MSRP_UCLEP | MSRP_DEP | MSRP_PMMP));
	if (set) {
		if (prot_bitmap & MSR_UCLE)
			vcpu->arch.shadow_msrp |= MSRP_UCLEP;
		if (prot_bitmap & MSR_DE)
			vcpu->arch.shadow_msrp |= MSRP_DEP;
		if (prot_bitmap & MSR_PMM)
			vcpu->arch.shadow_msrp |= MSRP_PMMP;
	} else {
		if (prot_bitmap & MSR_UCLE)
			vcpu->arch.shadow_msrp &= ~MSRP_UCLEP;
		if (prot_bitmap & MSR_DE)
			vcpu->arch.shadow_msrp &= ~MSRP_DEP;
		if (prot_bitmap & MSR_PMM)
			vcpu->arch.shadow_msrp &= ~MSRP_PMMP;
	}
#endif
}
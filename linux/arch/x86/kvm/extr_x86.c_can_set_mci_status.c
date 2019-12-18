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
struct TYPE_2__ {int msr_hwcr; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 scalar_t__ guest_cpuid_is_amd (struct kvm_vcpu*) ; 

__attribute__((used)) static bool can_set_mci_status(struct kvm_vcpu *vcpu)
{
	/* McStatusWrEn enabled? */
	if (guest_cpuid_is_amd(vcpu))
		return !!(vcpu->arch.msr_hwcr & BIT_ULL(18));

	return false;
}
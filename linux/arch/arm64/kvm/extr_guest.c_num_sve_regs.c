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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int SVE_NUM_PREGS ; 
 int SVE_NUM_ZREGS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  kvm_arm_vcpu_sve_finalized (struct kvm_vcpu const*) ; 
 int /*<<< orphan*/  vcpu_has_sve (struct kvm_vcpu const*) ; 
 unsigned int vcpu_sve_slices (struct kvm_vcpu const*) ; 

__attribute__((used)) static unsigned long num_sve_regs(const struct kvm_vcpu *vcpu)
{
	const unsigned int slices = vcpu_sve_slices(vcpu);

	if (!vcpu_has_sve(vcpu))
		return 0;

	/* Policed by KVM_GET_REG_LIST: */
	WARN_ON(!kvm_arm_vcpu_sve_finalized(vcpu));

	return slices * (SVE_NUM_PREGS + SVE_NUM_ZREGS + 1 /* FFR */)
		+ 1; /* KVM_REG_ARM64_SVE_VLS */
}
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
 int EINVAL ; 
 int EPERM ; 
#define  KVM_ARM_VCPU_SVE 128 
 int /*<<< orphan*/  kvm_arm_vcpu_sve_finalized (struct kvm_vcpu*) ; 
 int kvm_vcpu_finalize_sve (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_has_sve (struct kvm_vcpu*) ; 

int kvm_arm_vcpu_finalize(struct kvm_vcpu *vcpu, int feature)
{
	switch (feature) {
	case KVM_ARM_VCPU_SVE:
		if (!vcpu_has_sve(vcpu))
			return -EINVAL;

		if (kvm_arm_vcpu_sve_finalized(vcpu))
			return -EPERM;

		return kvm_vcpu_finalize_sve(vcpu);
	}

	return -EINVAL;
}
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
struct kvm_device_attr {int group; } ;

/* Variables and functions */
 int ENXIO ; 
#define  KVM_ARM_VCPU_PMU_V3_CTRL 129 
#define  KVM_ARM_VCPU_TIMER_CTRL 128 
 int kvm_arm_pmu_v3_has_attr (struct kvm_vcpu*,struct kvm_device_attr*) ; 
 int kvm_arm_timer_has_attr (struct kvm_vcpu*,struct kvm_device_attr*) ; 

int kvm_arm_vcpu_arch_has_attr(struct kvm_vcpu *vcpu,
			       struct kvm_device_attr *attr)
{
	int ret;

	switch (attr->group) {
	case KVM_ARM_VCPU_PMU_V3_CTRL:
		ret = kvm_arm_pmu_v3_has_attr(vcpu, attr);
		break;
	case KVM_ARM_VCPU_TIMER_CTRL:
		ret = kvm_arm_timer_has_attr(vcpu, attr);
		break;
	default:
		ret = -ENXIO;
		break;
	}

	return ret;
}
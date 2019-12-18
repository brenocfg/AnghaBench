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
struct kvm_one_reg {int id; } ;

/* Variables and functions */
 int EINVAL ; 
 int KVM_REG_ARM64 ; 
#define  KVM_REG_ARM64_SVE 130 
 int KVM_REG_ARM_COPROC_MASK ; 
#define  KVM_REG_ARM_CORE 129 
#define  KVM_REG_ARM_FW 128 
 int KVM_REG_SIZE_MASK ; 
 scalar_t__ is_timer_reg (int) ; 
 int kvm_arm_set_fw_reg (struct kvm_vcpu*,struct kvm_one_reg const*) ; 
 int kvm_arm_sys_reg_set_reg (struct kvm_vcpu*,struct kvm_one_reg const*) ; 
 int set_core_reg (struct kvm_vcpu*,struct kvm_one_reg const*) ; 
 int set_sve_reg (struct kvm_vcpu*,struct kvm_one_reg const*) ; 
 int set_timer_reg (struct kvm_vcpu*,struct kvm_one_reg const*) ; 

int kvm_arm_set_reg(struct kvm_vcpu *vcpu, const struct kvm_one_reg *reg)
{
	/* We currently use nothing arch-specific in upper 32 bits */
	if ((reg->id & ~KVM_REG_SIZE_MASK) >> 32 != KVM_REG_ARM64 >> 32)
		return -EINVAL;

	switch (reg->id & KVM_REG_ARM_COPROC_MASK) {
	case KVM_REG_ARM_CORE:	return set_core_reg(vcpu, reg);
	case KVM_REG_ARM_FW:	return kvm_arm_set_fw_reg(vcpu, reg);
	case KVM_REG_ARM64_SVE:	return set_sve_reg(vcpu, reg);
	}

	if (is_timer_reg(reg->id))
		return set_timer_reg(vcpu, reg);

	return kvm_arm_sys_reg_set_reg(vcpu, reg);
}
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
 scalar_t__ NUM_TIMER_REGS ; 
 scalar_t__ kvm_arm_get_fw_num_regs (struct kvm_vcpu*) ; 
 scalar_t__ kvm_arm_num_sys_reg_descs (struct kvm_vcpu*) ; 
 scalar_t__ num_core_regs (struct kvm_vcpu*) ; 
 scalar_t__ num_sve_regs (struct kvm_vcpu*) ; 

unsigned long kvm_arm_num_regs(struct kvm_vcpu *vcpu)
{
	unsigned long res = 0;

	res += num_core_regs(vcpu);
	res += num_sve_regs(vcpu);
	res += kvm_arm_num_sys_reg_descs(vcpu);
	res += kvm_arm_get_fw_num_regs(vcpu);
	res += NUM_TIMER_REGS;

	return res;
}
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
struct sys_reg_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  target; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cp15_regs ; 
 struct sys_reg_desc* get_target_table (int /*<<< orphan*/ ,int,size_t*) ; 
 int kvm_handle_cp_32 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct sys_reg_desc const*,size_t) ; 

int kvm_handle_cp15_32(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	const struct sys_reg_desc *target_specific;
	size_t num;

	target_specific = get_target_table(vcpu->arch.target, false, &num);
	return kvm_handle_cp_32(vcpu,
				cp15_regs, ARRAY_SIZE(cp15_regs),
				target_specific, num);
}
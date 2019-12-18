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
struct sys_reg_params {int dummy; } ;
struct sys_reg_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  target; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct sys_reg_desc const*) ; 
 struct sys_reg_desc* find_reg (struct sys_reg_params*,struct sys_reg_desc const*,size_t) ; 
 struct sys_reg_desc* get_target_table (int /*<<< orphan*/ ,int,size_t*) ; 
 int /*<<< orphan*/  kvm_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_undefined (struct kvm_vcpu*) ; 
 scalar_t__ likely (struct sys_reg_desc const*) ; 
 int /*<<< orphan*/  perform_access (struct kvm_vcpu*,struct sys_reg_params*,struct sys_reg_desc const*) ; 
 int /*<<< orphan*/  print_sys_reg_instr (struct sys_reg_params*) ; 
 struct sys_reg_desc const* sys_reg_descs ; 
 int /*<<< orphan*/ * vcpu_cpsr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/ * vcpu_pc (struct kvm_vcpu*) ; 

__attribute__((used)) static int emulate_sys_reg(struct kvm_vcpu *vcpu,
			   struct sys_reg_params *params)
{
	size_t num;
	const struct sys_reg_desc *table, *r;

	table = get_target_table(vcpu->arch.target, true, &num);

	/* Search target-specific then generic table. */
	r = find_reg(params, table, num);
	if (!r)
		r = find_reg(params, sys_reg_descs, ARRAY_SIZE(sys_reg_descs));

	if (likely(r)) {
		perform_access(vcpu, params, r);
	} else {
		kvm_err("Unsupported guest sys_reg access at: %lx [%08lx]\n",
			*vcpu_pc(vcpu), *vcpu_cpsr(vcpu));
		print_sys_reg_instr(params);
		kvm_inject_undefined(vcpu);
	}
	return 1;
}
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
struct TYPE_2__ {int /*<<< orphan*/  target; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct coproc_reg {struct coproc_reg const* (* access ) (struct kvm_vcpu*,struct coproc_params const*,struct coproc_reg const*) ;} ;
struct coproc_params {int /*<<< orphan*/  is_write; int /*<<< orphan*/  Op2; int /*<<< orphan*/  CRm; int /*<<< orphan*/  CRn; int /*<<< orphan*/  Rt1; int /*<<< orphan*/  Op1; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct coproc_reg const*) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct coproc_reg const* cp15_regs ; 
 struct coproc_reg* find_reg (struct coproc_params const*,struct coproc_reg const*,size_t) ; 
 struct coproc_reg* get_target_table (int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  kvm_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_inject_undefined (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_skip_instr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_trap_il_is32bit (struct kvm_vcpu*) ; 
 scalar_t__ likely (struct coproc_reg const*) ; 
 int /*<<< orphan*/  print_cp_instr (struct coproc_params const*) ; 
 struct coproc_reg const* stub1 (struct kvm_vcpu*,struct coproc_params const*,struct coproc_reg const*) ; 
 int /*<<< orphan*/  trace_kvm_emulate_cp15_imp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vcpu_cpsr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/ * vcpu_pc (struct kvm_vcpu*) ; 

__attribute__((used)) static int emulate_cp15(struct kvm_vcpu *vcpu,
			const struct coproc_params *params)
{
	size_t num;
	const struct coproc_reg *table, *r;

	trace_kvm_emulate_cp15_imp(params->Op1, params->Rt1, params->CRn,
				   params->CRm, params->Op2, params->is_write);

	table = get_target_table(vcpu->arch.target, &num);

	/* Search target-specific then generic table. */
	r = find_reg(params, table, num);
	if (!r)
		r = find_reg(params, cp15_regs, ARRAY_SIZE(cp15_regs));

	if (likely(r)) {
		/* If we don't have an accessor, we should never get here! */
		BUG_ON(!r->access);

		if (likely(r->access(vcpu, params, r))) {
			/* Skip instruction, since it was emulated */
			kvm_skip_instr(vcpu, kvm_vcpu_trap_il_is32bit(vcpu));
		}
	} else {
		/* If access function fails, it should complain. */
		kvm_err("Unsupported guest CP15 access at: %08lx [%08lx]\n",
			*vcpu_pc(vcpu), *vcpu_cpsr(vcpu));
		print_cp_instr(params);
		kvm_inject_undefined(vcpu);
	}

	return 1;
}
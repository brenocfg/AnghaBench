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
struct sys_reg_params {int dummy; } ;
struct sys_reg_desc {int /*<<< orphan*/  (* access ) (struct kvm_vcpu*,struct sys_reg_params*,struct sys_reg_desc const*) ;} ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  kvm_inject_undefined (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_skip_instr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_trap_il_is32bit (struct kvm_vcpu*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct kvm_vcpu*,struct sys_reg_params*,struct sys_reg_desc const*) ; 
 scalar_t__ sysreg_hidden_from_guest (struct kvm_vcpu*,struct sys_reg_desc const*) ; 
 int /*<<< orphan*/  trace_kvm_sys_access (int /*<<< orphan*/ ,struct sys_reg_params*,struct sys_reg_desc const*) ; 
 int /*<<< orphan*/ * vcpu_pc (struct kvm_vcpu*) ; 

__attribute__((used)) static void perform_access(struct kvm_vcpu *vcpu,
			   struct sys_reg_params *params,
			   const struct sys_reg_desc *r)
{
	trace_kvm_sys_access(*vcpu_pc(vcpu), params, r);

	/* Check for regs disabled by runtime config */
	if (sysreg_hidden_from_guest(vcpu, r)) {
		kvm_inject_undefined(vcpu);
		return;
	}

	/*
	 * Not having an accessor means that we have configured a trap
	 * that we don't know how to handle. This certainly qualifies
	 * as a gross bug that should be fixed right away.
	 */
	BUG_ON(!r->access);

	/* Skip instruction if instructed so */
	if (likely(r->access(vcpu, params, r)))
		kvm_skip_instr(vcpu, kvm_vcpu_trap_il_is32bit(vcpu));
}
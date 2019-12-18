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
struct kvm_run {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_skip_instr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_trap_il_is32bit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_set_reg (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static int handle_smc(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	/*
	 * "If an SMC instruction executed at Non-secure EL1 is
	 * trapped to EL2 because HCR_EL2.TSC is 1, the exception is a
	 * Trap exception, not a Secure Monitor Call exception [...]"
	 *
	 * We need to advance the PC after the trap, as it would
	 * otherwise return to the same address...
	 */
	vcpu_set_reg(vcpu, 0, ~0UL);
	kvm_skip_instr(vcpu, kvm_vcpu_trap_il_is32bit(vcpu));
	return 1;
}
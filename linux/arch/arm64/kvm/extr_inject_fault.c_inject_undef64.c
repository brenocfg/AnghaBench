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
typedef  int u32 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESR_EL1 ; 
 int ESR_ELx_EC_SHIFT ; 
 int ESR_ELx_EC_UNKNOWN ; 
 int ESR_ELx_IL ; 
 unsigned long PSTATE_FAULT_BITS_64 ; 
 int /*<<< orphan*/  except_type_sync ; 
 int /*<<< orphan*/  get_except_vector (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvm_vcpu_trap_il_is32bit (struct kvm_vcpu*) ; 
 unsigned long* vcpu_cpsr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/ * vcpu_pc (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_write_elr_el1 (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_write_spsr (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  vcpu_write_sys_reg (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void inject_undef64(struct kvm_vcpu *vcpu)
{
	unsigned long cpsr = *vcpu_cpsr(vcpu);
	u32 esr = (ESR_ELx_EC_UNKNOWN << ESR_ELx_EC_SHIFT);

	vcpu_write_elr_el1(vcpu, *vcpu_pc(vcpu));
	*vcpu_pc(vcpu) = get_except_vector(vcpu, except_type_sync);

	*vcpu_cpsr(vcpu) = PSTATE_FAULT_BITS_64;
	vcpu_write_spsr(vcpu, cpsr);

	/*
	 * Build an unknown exception, depending on the instruction
	 * set.
	 */
	if (kvm_vcpu_trap_il_is32bit(vcpu))
		esr |= ESR_ELx_IL;

	vcpu_write_sys_reg(vcpu, esr, ESR_EL1);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sysregs_loaded_on_cpu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct TYPE_4__ {unsigned long* spsr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  KVM_SPSR_ABT 132 
#define  KVM_SPSR_FIQ 131 
#define  KVM_SPSR_IRQ 130 
#define  KVM_SPSR_SVC 129 
#define  KVM_SPSR_UND 128 
 int /*<<< orphan*/  SYS_SPSR ; 
 unsigned long read_sysreg (int /*<<< orphan*/ ) ; 
 unsigned long read_sysreg_el1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spsr_abt ; 
 int /*<<< orphan*/  spsr_fiq ; 
 int /*<<< orphan*/  spsr_irq ; 
 int /*<<< orphan*/  spsr_und ; 
 TYPE_2__* vcpu_gp_regs (struct kvm_vcpu const*) ; 
 int vcpu_spsr32_mode (struct kvm_vcpu const*) ; 

unsigned long vcpu_read_spsr32(const struct kvm_vcpu *vcpu)
{
	int spsr_idx = vcpu_spsr32_mode(vcpu);

	if (!vcpu->arch.sysregs_loaded_on_cpu)
		return vcpu_gp_regs(vcpu)->spsr[spsr_idx];

	switch (spsr_idx) {
	case KVM_SPSR_SVC:
		return read_sysreg_el1(SYS_SPSR);
	case KVM_SPSR_ABT:
		return read_sysreg(spsr_abt);
	case KVM_SPSR_UND:
		return read_sysreg(spsr_und);
	case KVM_SPSR_IRQ:
		return read_sysreg(spsr_irq);
	case KVM_SPSR_FIQ:
		return read_sysreg(spsr_fiq);
	default:
		BUG();
	}
}
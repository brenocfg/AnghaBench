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
#define  KVM_SPSR_ABT 132 
#define  KVM_SPSR_FIQ 131 
#define  KVM_SPSR_IRQ 130 
#define  KVM_SPSR_SVC 129 
#define  KVM_SPSR_UND 128 
 int /*<<< orphan*/  SYS_SPSR ; 
 int /*<<< orphan*/  spsr_abt ; 
 int /*<<< orphan*/  spsr_fiq ; 
 int /*<<< orphan*/  spsr_irq ; 
 int /*<<< orphan*/  spsr_und ; 
 TYPE_2__* vcpu_gp_regs (struct kvm_vcpu*) ; 
 int vcpu_spsr32_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  write_sysreg (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_sysreg_el1 (unsigned long,int /*<<< orphan*/ ) ; 

void vcpu_write_spsr32(struct kvm_vcpu *vcpu, unsigned long v)
{
	int spsr_idx = vcpu_spsr32_mode(vcpu);

	if (!vcpu->arch.sysregs_loaded_on_cpu) {
		vcpu_gp_regs(vcpu)->spsr[spsr_idx] = v;
		return;
	}

	switch (spsr_idx) {
	case KVM_SPSR_SVC:
		write_sysreg_el1(v, SYS_SPSR);
		break;
	case KVM_SPSR_ABT:
		write_sysreg(v, spsr_abt);
		break;
	case KVM_SPSR_UND:
		write_sysreg(v, spsr_und);
		break;
	case KVM_SPSR_IRQ:
		write_sysreg(v, spsr_irq);
		break;
	case KVM_SPSR_FIQ:
		write_sysreg(v, spsr_fiq);
		break;
	}
}
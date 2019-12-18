#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ vm86_active; } ;
struct vcpu_vmx {TYPE_1__ rmode; TYPE_3__* loaded_vmcs; } ;
struct TYPE_5__ {int /*<<< orphan*/  nmi_injections; } ;
struct kvm_vcpu {TYPE_2__ stat; } ;
struct TYPE_6__ {int soft_vnmi_blocked; int nmi_known_unmasked; scalar_t__ vnmi_blocked_time; } ;

/* Variables and functions */
 int INTR_INFO_VALID_MASK ; 
 int INTR_TYPE_NMI_INTR ; 
 int NMI_VECTOR ; 
 int /*<<< orphan*/  VM_ENTRY_INTR_INFO_FIELD ; 
 int /*<<< orphan*/  enable_vnmi ; 
 int /*<<< orphan*/  kvm_inject_realmode_interrupt (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_write32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmx_clear_hlt (struct kvm_vcpu*) ; 

__attribute__((used)) static void vmx_inject_nmi(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (!enable_vnmi) {
		/*
		 * Tracking the NMI-blocked state in software is built upon
		 * finding the next open IRQ window. This, in turn, depends on
		 * well-behaving guests: They have to keep IRQs disabled at
		 * least as long as the NMI handler runs. Otherwise we may
		 * cause NMI nesting, maybe breaking the guest. But as this is
		 * highly unlikely, we can live with the residual risk.
		 */
		vmx->loaded_vmcs->soft_vnmi_blocked = 1;
		vmx->loaded_vmcs->vnmi_blocked_time = 0;
	}

	++vcpu->stat.nmi_injections;
	vmx->loaded_vmcs->nmi_known_unmasked = false;

	if (vmx->rmode.vm86_active) {
		kvm_inject_realmode_interrupt(vcpu, NMI_VECTOR, 0);
		return;
	}

	vmcs_write32(VM_ENTRY_INTR_INFO_FIELD,
			INTR_TYPE_NMI_INTR | INTR_INFO_VALID_MASK | NMI_VECTOR);

	vmx_clear_hlt(vcpu);
}
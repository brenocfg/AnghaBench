#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pir; } ;
struct vcpu_vmx {TYPE_2__ pi_desc; } ;
struct TYPE_4__ {int /*<<< orphan*/  apicv_active; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_EVENT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_guest_mode (struct kvm_vcpu*) ; 
 int kvm_apic_update_irr (struct kvm_vcpu*,int /*<<< orphan*/ ,int*) ; 
 int kvm_lapic_find_highest_irr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_vcpu_exiting_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ nested_exit_on_intr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  pi_clear_on (TYPE_2__*) ; 
 scalar_t__ pi_test_on (TYPE_2__*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_hwapic_irr_update (struct kvm_vcpu*,int) ; 

__attribute__((used)) static int vmx_sync_pir_to_irr(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	int max_irr;
	bool max_irr_updated;

	WARN_ON(!vcpu->arch.apicv_active);
	if (pi_test_on(&vmx->pi_desc)) {
		pi_clear_on(&vmx->pi_desc);
		/*
		 * IOMMU can write to PID.ON, so the barrier matters even on UP.
		 * But on x86 this is just a compiler barrier anyway.
		 */
		smp_mb__after_atomic();
		max_irr_updated =
			kvm_apic_update_irr(vcpu, vmx->pi_desc.pir, &max_irr);

		/*
		 * If we are running L2 and L1 has a new pending interrupt
		 * which can be injected, we should re-evaluate
		 * what should be done with this new L1 interrupt.
		 * If L1 intercepts external-interrupts, we should
		 * exit from L2 to L1. Otherwise, interrupt should be
		 * delivered directly to L2.
		 */
		if (is_guest_mode(vcpu) && max_irr_updated) {
			if (nested_exit_on_intr(vcpu))
				kvm_vcpu_exiting_guest_mode(vcpu);
			else
				kvm_make_request(KVM_REQ_EVENT, vcpu);
		}
	} else {
		max_irr = kvm_lapic_find_highest_irr(vcpu);
	}
	vmx_hwapic_irr_update(vcpu, max_irr);
	return max_irr;
}
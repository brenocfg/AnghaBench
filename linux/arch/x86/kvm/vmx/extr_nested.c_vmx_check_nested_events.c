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
struct TYPE_5__ {scalar_t__ preemption_timer_expired; scalar_t__ nested_run_pending; } ;
struct vcpu_vmx {TYPE_2__ nested; } ;
struct TYPE_4__ {scalar_t__ pending; } ;
struct TYPE_6__ {scalar_t__ nmi_pending; TYPE_1__ exception; struct kvm_lapic* apic; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct kvm_lapic {int /*<<< orphan*/  pending_events; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  EXIT_REASON_EXCEPTION_NMI ; 
 int /*<<< orphan*/  EXIT_REASON_EXTERNAL_INTERRUPT ; 
 int /*<<< orphan*/  EXIT_REASON_INIT_SIGNAL ; 
 int /*<<< orphan*/  EXIT_REASON_PREEMPTION_TIMER ; 
 int INTR_INFO_VALID_MASK ; 
 int INTR_TYPE_NMI_INTR ; 
 int /*<<< orphan*/  KVM_APIC_INIT ; 
 int NMI_VECTOR ; 
 int /*<<< orphan*/  get_vmcs12 (struct kvm_vcpu*) ; 
 scalar_t__ kvm_cpu_has_interrupt (struct kvm_vcpu*) ; 
 scalar_t__ kvm_event_needs_reinjection (struct kvm_vcpu*) ; 
 scalar_t__ lapic_in_kernel (struct kvm_vcpu*) ; 
 scalar_t__ nested_cpu_has_preemption_timer (int /*<<< orphan*/ ) ; 
 scalar_t__ nested_exit_on_intr (struct kvm_vcpu*) ; 
 scalar_t__ nested_exit_on_nmi (struct kvm_vcpu*) ; 
 scalar_t__ nested_vmx_check_exception (struct kvm_vcpu*,unsigned long*) ; 
 int /*<<< orphan*/  nested_vmx_inject_exception_vmexit (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  nested_vmx_vmexit (struct kvm_vcpu*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_complete_nested_posted_interrupt (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_set_nmi_mask (struct kvm_vcpu*,int) ; 

__attribute__((used)) static int vmx_check_nested_events(struct kvm_vcpu *vcpu, bool external_intr)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	unsigned long exit_qual;
	bool block_nested_events =
	    vmx->nested.nested_run_pending || kvm_event_needs_reinjection(vcpu);
	struct kvm_lapic *apic = vcpu->arch.apic;

	if (lapic_in_kernel(vcpu) &&
		test_bit(KVM_APIC_INIT, &apic->pending_events)) {
		if (block_nested_events)
			return -EBUSY;
		nested_vmx_vmexit(vcpu, EXIT_REASON_INIT_SIGNAL, 0, 0);
		return 0;
	}

	if (vcpu->arch.exception.pending &&
		nested_vmx_check_exception(vcpu, &exit_qual)) {
		if (block_nested_events)
			return -EBUSY;
		nested_vmx_inject_exception_vmexit(vcpu, exit_qual);
		return 0;
	}

	if (nested_cpu_has_preemption_timer(get_vmcs12(vcpu)) &&
	    vmx->nested.preemption_timer_expired) {
		if (block_nested_events)
			return -EBUSY;
		nested_vmx_vmexit(vcpu, EXIT_REASON_PREEMPTION_TIMER, 0, 0);
		return 0;
	}

	if (vcpu->arch.nmi_pending && nested_exit_on_nmi(vcpu)) {
		if (block_nested_events)
			return -EBUSY;
		nested_vmx_vmexit(vcpu, EXIT_REASON_EXCEPTION_NMI,
				  NMI_VECTOR | INTR_TYPE_NMI_INTR |
				  INTR_INFO_VALID_MASK, 0);
		/*
		 * The NMI-triggered VM exit counts as injection:
		 * clear this one and block further NMIs.
		 */
		vcpu->arch.nmi_pending = 0;
		vmx_set_nmi_mask(vcpu, true);
		return 0;
	}

	if ((kvm_cpu_has_interrupt(vcpu) || external_intr) &&
	    nested_exit_on_intr(vcpu)) {
		if (block_nested_events)
			return -EBUSY;
		nested_vmx_vmexit(vcpu, EXIT_REASON_EXTERNAL_INTERRUPT, 0, 0);
		return 0;
	}

	vmx_complete_nested_posted_interrupt(vcpu);
	return 0;
}
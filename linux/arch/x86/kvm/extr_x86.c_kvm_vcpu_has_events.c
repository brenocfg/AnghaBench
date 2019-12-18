#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pending; } ;
struct TYPE_7__ {scalar_t__ pv_unhalted; } ;
struct TYPE_9__ {scalar_t__ smi_pending; scalar_t__ nmi_pending; TYPE_3__ exception; TYPE_2__ pv; } ;
struct TYPE_6__ {int /*<<< orphan*/  done; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_1__ async_pf; } ;
struct TYPE_10__ {scalar_t__ (* nmi_allowed ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_NMI ; 
 int /*<<< orphan*/  KVM_REQ_SMI ; 
 int /*<<< orphan*/  is_smm (struct kvm_vcpu*) ; 
 scalar_t__ kvm_apic_has_events (struct kvm_vcpu*) ; 
 scalar_t__ kvm_arch_interrupt_allowed (struct kvm_vcpu*) ; 
 scalar_t__ kvm_cpu_has_interrupt (struct kvm_vcpu*) ; 
 scalar_t__ kvm_guest_apic_has_interrupt (struct kvm_vcpu*) ; 
 scalar_t__ kvm_hv_has_stimer_pending (struct kvm_vcpu*) ; 
 scalar_t__ kvm_test_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 TYPE_5__* kvm_x86_ops ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static inline bool kvm_vcpu_has_events(struct kvm_vcpu *vcpu)
{
	if (!list_empty_careful(&vcpu->async_pf.done))
		return true;

	if (kvm_apic_has_events(vcpu))
		return true;

	if (vcpu->arch.pv.pv_unhalted)
		return true;

	if (vcpu->arch.exception.pending)
		return true;

	if (kvm_test_request(KVM_REQ_NMI, vcpu) ||
	    (vcpu->arch.nmi_pending &&
	     kvm_x86_ops->nmi_allowed(vcpu)))
		return true;

	if (kvm_test_request(KVM_REQ_SMI, vcpu) ||
	    (vcpu->arch.smi_pending && !is_smm(vcpu)))
		return true;

	if (kvm_arch_interrupt_allowed(vcpu) &&
	    (kvm_cpu_has_interrupt(vcpu) ||
	    kvm_guest_apic_has_interrupt(vcpu)))
		return true;

	if (kvm_hv_has_stimer_pending(vcpu))
		return true;

	return false;
}
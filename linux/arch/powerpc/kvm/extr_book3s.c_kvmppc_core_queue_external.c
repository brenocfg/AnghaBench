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
struct TYPE_2__ {int external_oneshot; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_interrupt {scalar_t__ irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_INTERRUPT_EXTERNAL ; 
 scalar_t__ KVM_INTERRUPT_SET ; 
 int /*<<< orphan*/  kvmppc_book3s_queue_irqprio (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvmppc_core_queue_external(struct kvm_vcpu *vcpu,
                                struct kvm_interrupt *irq)
{
	/*
	 * This case (KVM_INTERRUPT_SET) should never actually arise for
	 * a pseries guest (because pseries guests expect their interrupt
	 * controllers to continue asserting an external interrupt request
	 * until it is acknowledged at the interrupt controller), but is
	 * included to avoid ABI breakage and potentially for other
	 * sorts of guest.
	 *
	 * There is a subtlety here: HV KVM does not test the
	 * external_oneshot flag in the code that synthesizes
	 * external interrupts for the guest just before entering
	 * the guest.  That is OK even if userspace did do a
	 * KVM_INTERRUPT_SET on a pseries guest vcpu, because the
	 * caller (kvm_vcpu_ioctl_interrupt) does a kvm_vcpu_kick()
	 * which ends up doing a smp_send_reschedule(), which will
	 * pull the guest all the way out to the host, meaning that
	 * we will call kvmppc_core_prepare_to_enter() before entering
	 * the guest again, and that will handle the external_oneshot
	 * flag correctly.
	 */
	if (irq->irq == KVM_INTERRUPT_SET)
		vcpu->arch.external_oneshot = 1;

	kvmppc_book3s_queue_irqprio(vcpu, BOOK3S_INTERRUPT_EXTERNAL);
}
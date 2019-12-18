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
struct kvm_interrupt {scalar_t__ irq; } ;

/* Variables and functions */
 unsigned int BOOKE_IRQPRIO_EXTERNAL ; 
 unsigned int BOOKE_IRQPRIO_EXTERNAL_LEVEL ; 
 scalar_t__ KVM_INTERRUPT_SET_LEVEL ; 
 int /*<<< orphan*/  kvmppc_booke_queue_irqprio (struct kvm_vcpu*,unsigned int) ; 

void kvmppc_core_queue_external(struct kvm_vcpu *vcpu,
                                struct kvm_interrupt *irq)
{
	unsigned int prio = BOOKE_IRQPRIO_EXTERNAL;

	if (irq->irq == KVM_INTERRUPT_SET_LEVEL)
		prio = BOOKE_IRQPRIO_EXTERNAL_LEVEL;

	kvmppc_booke_queue_irqprio(vcpu, prio);
}
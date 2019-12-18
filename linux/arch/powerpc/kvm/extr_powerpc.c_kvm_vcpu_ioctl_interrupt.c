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
 scalar_t__ KVM_INTERRUPT_UNSET ; 
 int /*<<< orphan*/  kvm_vcpu_kick (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_core_dequeue_external (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_core_queue_external (struct kvm_vcpu*,struct kvm_interrupt*) ; 

int kvm_vcpu_ioctl_interrupt(struct kvm_vcpu *vcpu, struct kvm_interrupt *irq)
{
	if (irq->irq == KVM_INTERRUPT_UNSET) {
		kvmppc_core_dequeue_external(vcpu);
		return 0;
	}

	kvmppc_core_queue_external(vcpu, irq);

	kvm_vcpu_kick(vcpu);

	return 0;
}
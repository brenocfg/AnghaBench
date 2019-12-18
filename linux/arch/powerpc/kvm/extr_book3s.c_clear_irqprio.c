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
struct TYPE_2__ {int /*<<< orphan*/  external_oneshot; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
#define  BOOK3S_IRQPRIO_DECREMENTER 129 
#define  BOOK3S_IRQPRIO_EXTERNAL 128 

__attribute__((used)) static bool clear_irqprio(struct kvm_vcpu *vcpu, unsigned int priority)
{
	switch (priority) {
		case BOOK3S_IRQPRIO_DECREMENTER:
			/* DEC interrupts get cleared by mtdec */
			return false;
		case BOOK3S_IRQPRIO_EXTERNAL:
			/*
			 * External interrupts get cleared by userspace
			 * except when set by the KVM_INTERRUPT ioctl with
			 * KVM_INTERRUPT_SET (not KVM_INTERRUPT_SET_LEVEL).
			 */
			if (vcpu->arch.external_oneshot) {
				vcpu->arch.external_oneshot = 0;
				return true;
			}
			return false;
	}

	return true;
}
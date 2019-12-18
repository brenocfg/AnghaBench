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
struct TYPE_2__ {int /*<<< orphan*/  pending_exceptions; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  set_bit (unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_kvm_booke_queue_irqprio (struct kvm_vcpu*,unsigned int) ; 

__attribute__((used)) static void kvmppc_booke_queue_irqprio(struct kvm_vcpu *vcpu,
                                       unsigned int priority)
{
	trace_kvm_booke_queue_irqprio(vcpu, priority);
	set_bit(priority, &vcpu->arch.pending_exceptions);
}
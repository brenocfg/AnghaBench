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
struct TYPE_2__ {unsigned long pending_exceptions; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  kvmppc_book3s_vec2irqprio (unsigned int) ; 
 int /*<<< orphan*/  kvmppc_update_int_pending (struct kvm_vcpu*,unsigned long,unsigned long) ; 

void kvmppc_book3s_dequeue_irqprio(struct kvm_vcpu *vcpu,
					  unsigned int vec)
{
	unsigned long old_pending = vcpu->arch.pending_exceptions;

	clear_bit(kvmppc_book3s_vec2irqprio(vec),
		  &vcpu->arch.pending_exceptions);

	kvmppc_update_int_pending(vcpu, vcpu->arch.pending_exceptions,
				  old_pending);
}
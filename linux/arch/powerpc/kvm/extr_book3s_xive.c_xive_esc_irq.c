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
struct TYPE_2__ {int irq_pending; int xive_esc_on; scalar_t__ ceded; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  kvmppc_fast_vcpu_kick (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static irqreturn_t xive_esc_irq(int irq, void *data)
{
	struct kvm_vcpu *vcpu = data;

	vcpu->arch.irq_pending = 1;
	smp_mb();
	if (vcpu->arch.ceded)
		kvmppc_fast_vcpu_kick(vcpu);

	/* Since we have the no-EOI flag, the interrupt is effectively
	 * disabled now. Clearing xive_esc_on means we won't bother
	 * doing so on the next entry.
	 *
	 * This also allows the entry code to know that if a PQ combination
	 * of 10 is observed while xive_esc_on is true, it means the queue
	 * contains an unprocessed escalation interrupt. We don't make use of
	 * that knowledge today but might (see comment in book3s_hv_rmhandler.S)
	 */
	vcpu->arch.xive_esc_on = false;

	/* This orders xive_esc_on = false vs. subsequent stale_p = true */
	smp_wmb();	/* goes with smp_mb() in cleanup_single_escalation */

	return IRQ_HANDLED;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct kvmppc_xive_src_block {int /*<<< orphan*/  lock; struct kvmppc_xive_irq_state* irq_state; } ;
struct kvmppc_xive_irq_state {int old_p; int old_q; unsigned int pt_number; int /*<<< orphan*/  guest_priority; int /*<<< orphan*/  pt_data; int /*<<< orphan*/  number; int /*<<< orphan*/  act_priority; int /*<<< orphan*/  act_server; int /*<<< orphan*/  ipi_data; } ;
struct kvmppc_xive {TYPE_2__* ops; } ;
struct TYPE_3__ {struct kvmppc_xive* xive; } ;
struct kvm {TYPE_1__ arch; } ;
struct irq_desc {int dummy; } ;
struct irq_data {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* reset_mapped ) (struct kvm*,unsigned long) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  MASKED ; 
 int /*<<< orphan*/  XIVE_ESB_SET_PQ_01 ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_data_get_irq_handler_data (struct irq_data*) ; 
 unsigned int irq_desc_get_irq (struct irq_desc*) ; 
 struct irq_data* irq_desc_get_irq_data (struct irq_desc*) ; 
 int irq_set_vcpu_affinity (unsigned int,struct kvmppc_xive_irq_state*) ; 
 scalar_t__ irqd_to_hwirq (struct irq_data*) ; 
 struct kvmppc_xive_src_block* kvmppc_xive_find_source (struct kvmppc_xive*,unsigned long,size_t*) ; 
 int /*<<< orphan*/  kvmppc_xive_vp (struct kvmppc_xive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  pr_devel (char*,unsigned long,int,...) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct kvm*,unsigned long) ; 
 int /*<<< orphan*/  xive_lock_and_mask (struct kvmppc_xive*,struct kvmppc_xive_src_block*,struct kvmppc_xive_irq_state*) ; 
 int /*<<< orphan*/  xive_native_configure_irq (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_vm_esb_load (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_vm_source_eoi (unsigned int,int /*<<< orphan*/ ) ; 

int kvmppc_xive_set_mapped(struct kvm *kvm, unsigned long guest_irq,
			   struct irq_desc *host_desc)
{
	struct kvmppc_xive *xive = kvm->arch.xive;
	struct kvmppc_xive_src_block *sb;
	struct kvmppc_xive_irq_state *state;
	struct irq_data *host_data = irq_desc_get_irq_data(host_desc);
	unsigned int host_irq = irq_desc_get_irq(host_desc);
	unsigned int hw_irq = (unsigned int)irqd_to_hwirq(host_data);
	u16 idx;
	u8 prio;
	int rc;

	if (!xive)
		return -ENODEV;

	pr_devel("set_mapped girq 0x%lx host HW irq 0x%x...\n",guest_irq, hw_irq);

	sb = kvmppc_xive_find_source(xive, guest_irq, &idx);
	if (!sb)
		return -EINVAL;
	state = &sb->irq_state[idx];

	/*
	 * Mark the passed-through interrupt as going to a VCPU,
	 * this will prevent further EOIs and similar operations
	 * from the XIVE code. It will also mask the interrupt
	 * to either PQ=10 or 11 state, the latter if the interrupt
	 * is pending. This will allow us to unmask or retrigger it
	 * after routing it to the guest with a simple EOI.
	 *
	 * The "state" argument is a "token", all it needs is to be
	 * non-NULL to switch to passed-through or NULL for the
	 * other way around. We may not yet have an actual VCPU
	 * target here and we don't really care.
	 */
	rc = irq_set_vcpu_affinity(host_irq, state);
	if (rc) {
		pr_err("Failed to set VCPU affinity for irq %d\n", host_irq);
		return rc;
	}

	/*
	 * Mask and read state of IPI. We need to know if its P bit
	 * is set as that means it's potentially already using a
	 * queue entry in the target
	 */
	prio = xive_lock_and_mask(xive, sb, state);
	pr_devel(" old IPI prio %02x P:%d Q:%d\n", prio,
		 state->old_p, state->old_q);

	/* Turn the IPI hard off */
	xive_vm_esb_load(&state->ipi_data, XIVE_ESB_SET_PQ_01);

	/*
	 * Reset ESB guest mapping. Needed when ESB pages are exposed
	 * to the guest in XIVE native mode
	 */
	if (xive->ops && xive->ops->reset_mapped)
		xive->ops->reset_mapped(kvm, guest_irq);

	/* Grab info about irq */
	state->pt_number = hw_irq;
	state->pt_data = irq_data_get_irq_handler_data(host_data);

	/*
	 * Configure the IRQ to match the existing configuration of
	 * the IPI if it was already targetted. Otherwise this will
	 * mask the interrupt in a lossy way (act_priority is 0xff)
	 * which is fine for a never started interrupt.
	 */
	xive_native_configure_irq(hw_irq,
				  kvmppc_xive_vp(xive, state->act_server),
				  state->act_priority, state->number);

	/*
	 * We do an EOI to enable the interrupt (and retrigger if needed)
	 * if the guest has the interrupt unmasked and the P bit was *not*
	 * set in the IPI. If it was set, we know a slot may still be in
	 * use in the target queue thus we have to wait for a guest
	 * originated EOI
	 */
	if (prio != MASKED && !state->old_p)
		xive_vm_source_eoi(hw_irq, state->pt_data);

	/* Clear old_p/old_q as they are no longer relevant */
	state->old_p = state->old_q = false;

	/* Restore guest prio (unlocks EOI) */
	mb();
	state->guest_priority = prio;
	arch_spin_unlock(&sb->lock);

	return 0;
}
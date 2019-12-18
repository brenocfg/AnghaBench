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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xive_irq_data {int flags; } ;
struct kvmppc_xive_src_block {int dummy; } ;
struct kvmppc_xive_irq_state {scalar_t__ guest_priority; int /*<<< orphan*/  old_p; scalar_t__ old_q; int /*<<< orphan*/  number; int /*<<< orphan*/  act_priority; int /*<<< orphan*/  act_server; } ;
struct kvmppc_xive {int dummy; } ;

/* Variables and functions */
 scalar_t__ MASKED ; 
 int OPAL_XIVE_IRQ_LSI ; 
 int OPAL_XIVE_IRQ_MASK_VIA_FW ; 
 int /*<<< orphan*/  XIVE_ESB_SET_PQ_11 ; 
 int /*<<< orphan*/  kvmppc_xive_select_irq (struct kvmppc_xive_irq_state*,int /*<<< orphan*/ *,struct xive_irq_data**) ; 
 int /*<<< orphan*/  kvmppc_xive_vp (struct kvmppc_xive*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mb () ; 
 int /*<<< orphan*/  xive_irq_trigger (struct xive_irq_data*) ; 
 int /*<<< orphan*/  xive_native_configure_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_vm_esb_load (struct xive_irq_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xive_vm_source_eoi (int /*<<< orphan*/ ,struct xive_irq_data*) ; 

__attribute__((used)) static void xive_finish_unmask(struct kvmppc_xive *xive,
			       struct kvmppc_xive_src_block *sb,
			       struct kvmppc_xive_irq_state *state,
			       u8 prio)
{
	struct xive_irq_data *xd;
	u32 hw_num;

	/* If we aren't changing a thing, move on */
	if (state->guest_priority != MASKED)
		goto bail;

	/* Get the right irq */
	kvmppc_xive_select_irq(state, &hw_num, &xd);

	/*
	 * See command in xive_lock_and_mask() concerning masking
	 * via firmware.
	 */
	if (xd->flags & OPAL_XIVE_IRQ_MASK_VIA_FW) {
		xive_native_configure_irq(hw_num,
				kvmppc_xive_vp(xive, state->act_server),
				state->act_priority, state->number);
		/* If an EOI is needed, do it here */
		if (!state->old_p)
			xive_vm_source_eoi(hw_num, xd);
		/* If this is not an LSI, force a trigger */
		if (!(xd->flags & OPAL_XIVE_IRQ_LSI))
			xive_irq_trigger(xd);
		goto bail;
	}

	/* Old Q set, set PQ to 11 */
	if (state->old_q)
		xive_vm_esb_load(xd, XIVE_ESB_SET_PQ_11);

	/*
	 * If not old P, then perform an "effective" EOI,
	 * on the source. This will handle the cases where
	 * FW EOI is needed.
	 */
	if (!state->old_p)
		xive_vm_source_eoi(hw_num, xd);

	/* Synchronize ordering and mark unmasked */
	mb();
bail:
	state->guest_priority = prio;
}
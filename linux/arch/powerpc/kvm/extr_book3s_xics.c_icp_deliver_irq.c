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
typedef  scalar_t__ u32 ;
typedef  size_t u16 ;
struct kvmppc_xics {int /*<<< orphan*/  kvm; } ;
struct kvmppc_ics {int /*<<< orphan*/  lock; int /*<<< orphan*/  icsid; struct ics_irq_state* irq_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  need_resend; } ;
struct kvmppc_icp {scalar_t__ server_num; TYPE_1__ state; int /*<<< orphan*/  resend_map; } ;
struct ics_irq_state {scalar_t__ server; int resend; scalar_t__ priority; int masked_pending; } ;

/* Variables and functions */
 scalar_t__ MASKED ; 
 int /*<<< orphan*/  XICS_DBG (char*,scalar_t__) ; 
 scalar_t__ XICS_IPI ; 
 int /*<<< orphan*/  arch_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  arch_spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ icp_try_to_deliver (struct kvmppc_icp*,scalar_t__,scalar_t__,scalar_t__*) ; 
 struct kvmppc_ics* kvmppc_xics_find_ics (struct kvmppc_xics*,scalar_t__,size_t*) ; 
 struct kvmppc_icp* kvmppc_xics_find_server (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static void icp_deliver_irq(struct kvmppc_xics *xics, struct kvmppc_icp *icp,
			    u32 new_irq, bool check_resend)
{
	struct ics_irq_state *state;
	struct kvmppc_ics *ics;
	u32 reject;
	u16 src;
	unsigned long flags;

	/*
	 * This is used both for initial delivery of an interrupt and
	 * for subsequent rejection.
	 *
	 * Rejection can be racy vs. resends. We have evaluated the
	 * rejection in an atomic ICP transaction which is now complete,
	 * so potentially the ICP can already accept the interrupt again.
	 *
	 * So we need to retry the delivery. Essentially the reject path
	 * boils down to a failed delivery. Always.
	 *
	 * Now the interrupt could also have moved to a different target,
	 * thus we may need to re-do the ICP lookup as well
	 */

 again:
	/* Get the ICS state and lock it */
	ics = kvmppc_xics_find_ics(xics, new_irq, &src);
	if (!ics) {
		XICS_DBG("icp_deliver_irq: IRQ 0x%06x not found !\n", new_irq);
		return;
	}
	state = &ics->irq_state[src];

	/* Get a lock on the ICS */
	local_irq_save(flags);
	arch_spin_lock(&ics->lock);

	/* Get our server */
	if (!icp || state->server != icp->server_num) {
		icp = kvmppc_xics_find_server(xics->kvm, state->server);
		if (!icp) {
			pr_warn("icp_deliver_irq: IRQ 0x%06x server 0x%x not found !\n",
				new_irq, state->server);
			goto out;
		}
	}

	if (check_resend)
		if (!state->resend)
			goto out;

	/* Clear the resend bit of that interrupt */
	state->resend = 0;

	/*
	 * If masked, bail out
	 *
	 * Note: PAPR doesn't mention anything about masked pending
	 * when doing a resend, only when doing a delivery.
	 *
	 * However that would have the effect of losing a masked
	 * interrupt that was rejected and isn't consistent with
	 * the whole masked_pending business which is about not
	 * losing interrupts that occur while masked.
	 *
	 * I don't differentiate normal deliveries and resends, this
	 * implementation will differ from PAPR and not lose such
	 * interrupts.
	 */
	if (state->priority == MASKED) {
		XICS_DBG("irq %#x masked pending\n", new_irq);
		state->masked_pending = 1;
		goto out;
	}

	/*
	 * Try the delivery, this will set the need_resend flag
	 * in the ICP as part of the atomic transaction if the
	 * delivery is not possible.
	 *
	 * Note that if successful, the new delivery might have itself
	 * rejected an interrupt that was "delivered" before we took the
	 * ics spin lock.
	 *
	 * In this case we do the whole sequence all over again for the
	 * new guy. We cannot assume that the rejected interrupt is less
	 * favored than the new one, and thus doesn't need to be delivered,
	 * because by the time we exit icp_try_to_deliver() the target
	 * processor may well have alrady consumed & completed it, and thus
	 * the rejected interrupt might actually be already acceptable.
	 */
	if (icp_try_to_deliver(icp, new_irq, state->priority, &reject)) {
		/*
		 * Delivery was successful, did we reject somebody else ?
		 */
		if (reject && reject != XICS_IPI) {
			arch_spin_unlock(&ics->lock);
			local_irq_restore(flags);
			new_irq = reject;
			check_resend = 0;
			goto again;
		}
	} else {
		/*
		 * We failed to deliver the interrupt we need to set the
		 * resend map bit and mark the ICS state as needing a resend
		 */
		state->resend = 1;

		/*
		 * Make sure when checking resend, we don't miss the resend
		 * if resend_map bit is seen and cleared.
		 */
		smp_wmb();
		set_bit(ics->icsid, icp->resend_map);

		/*
		 * If the need_resend flag got cleared in the ICP some time
		 * between icp_try_to_deliver() atomic update and now, then
		 * we know it might have missed the resend_map bit. So we
		 * retry
		 */
		smp_mb();
		if (!icp->state.need_resend) {
			state->resend = 0;
			arch_spin_unlock(&ics->lock);
			local_irq_restore(flags);
			check_resend = 0;
			goto again;
		}
	}
 out:
	arch_spin_unlock(&ics->lock);
	local_irq_restore(flags);
}
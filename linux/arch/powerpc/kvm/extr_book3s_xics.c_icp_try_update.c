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
union kvmppc_icp_state {int out_ee; scalar_t__ pending_pri; scalar_t__ cppr; scalar_t__ raw; int /*<<< orphan*/  need_resend; scalar_t__ xisr; int /*<<< orphan*/  mfrr; } ;
struct TYPE_2__ {int /*<<< orphan*/  raw; } ;
struct kvmppc_icp {int /*<<< orphan*/  vcpu; int /*<<< orphan*/  server_num; TYPE_1__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_INTERRUPT_EXTERNAL ; 
 int /*<<< orphan*/  XICS_DBG (char*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,...) ; 
 scalar_t__ cmpxchg64 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  kvmppc_book3s_queue_irqprio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_fast_vcpu_kick (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool icp_try_update(struct kvmppc_icp *icp,
				  union kvmppc_icp_state old,
				  union kvmppc_icp_state new,
				  bool change_self)
{
	bool success;

	/* Calculate new output value */
	new.out_ee = (new.xisr && (new.pending_pri < new.cppr));

	/* Attempt atomic update */
	success = cmpxchg64(&icp->state.raw, old.raw, new.raw) == old.raw;
	if (!success)
		goto bail;

	XICS_DBG("UPD [%04lx] - C:%02x M:%02x PP: %02x PI:%06x R:%d O:%d\n",
		 icp->server_num,
		 old.cppr, old.mfrr, old.pending_pri, old.xisr,
		 old.need_resend, old.out_ee);
	XICS_DBG("UPD        - C:%02x M:%02x PP: %02x PI:%06x R:%d O:%d\n",
		 new.cppr, new.mfrr, new.pending_pri, new.xisr,
		 new.need_resend, new.out_ee);
	/*
	 * Check for output state update
	 *
	 * Note that this is racy since another processor could be updating
	 * the state already. This is why we never clear the interrupt output
	 * here, we only ever set it. The clear only happens prior to doing
	 * an update and only by the processor itself. Currently we do it
	 * in Accept (H_XIRR) and Up_Cppr (H_XPPR).
	 *
	 * We also do not try to figure out whether the EE state has changed,
	 * we unconditionally set it if the new state calls for it. The reason
	 * for that is that we opportunistically remove the pending interrupt
	 * flag when raising CPPR, so we need to set it back here if an
	 * interrupt is still pending.
	 */
	if (new.out_ee) {
		kvmppc_book3s_queue_irqprio(icp->vcpu,
					    BOOK3S_INTERRUPT_EXTERNAL);
		if (!change_self)
			kvmppc_fast_vcpu_kick(icp->vcpu);
	}
 bail:
	return success;
}
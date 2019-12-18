#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
union kvmppc_icp_state {int out_ee; scalar_t__ pending_pri; scalar_t__ cppr; scalar_t__ raw; scalar_t__ xisr; } ;
struct TYPE_6__ {int /*<<< orphan*/  raw; } ;
struct kvmppc_icp {int /*<<< orphan*/  vcpu; TYPE_1__ state; } ;
struct TYPE_8__ {TYPE_2__* icp; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;
struct TYPE_9__ {struct kvm_vcpu* kvm_vcpu; } ;
struct TYPE_10__ {TYPE_4__ kvm_hstate; } ;
struct TYPE_7__ {int /*<<< orphan*/  rm_dbgtgt; union kvmppc_icp_state rm_dbgstate; } ;

/* Variables and functions */
 scalar_t__ cmpxchg64 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  icp_rm_set_vcpu_irq (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 TYPE_5__* local_paca ; 

__attribute__((used)) static inline bool icp_rm_try_update(struct kvmppc_icp *icp,
				     union kvmppc_icp_state old,
				     union kvmppc_icp_state new)
{
	struct kvm_vcpu *this_vcpu = local_paca->kvm_hstate.kvm_vcpu;
	bool success;

	/* Calculate new output value */
	new.out_ee = (new.xisr && (new.pending_pri < new.cppr));

	/* Attempt atomic update */
	success = cmpxchg64(&icp->state.raw, old.raw, new.raw) == old.raw;
	if (!success)
		goto bail;

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
	if (new.out_ee)
		icp_rm_set_vcpu_irq(icp->vcpu, this_vcpu);

	/* Expose the state change for debug purposes */
	this_vcpu->arch.icp->rm_dbgstate = new;
	this_vcpu->arch.icp->rm_dbgtgt = icp->vcpu;

 bail:
	return success;
}
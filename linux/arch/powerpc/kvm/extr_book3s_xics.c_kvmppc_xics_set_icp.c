#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union kvmppc_icp_state {int cppr; int xisr; int mfrr; int pending_pri; int need_resend; scalar_t__ raw; } ;
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct kvmppc_xics {int dummy; } ;
struct kvmppc_ics {int dummy; } ;
struct kvmppc_icp {int /*<<< orphan*/  state; int /*<<< orphan*/  vcpu; } ;
struct TYPE_4__ {struct kvmppc_icp* icp; } ;
struct kvm_vcpu {TYPE_3__* kvm; TYPE_1__ arch; } ;
struct TYPE_5__ {struct kvmppc_xics* xics; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_INTERRUPT_EXTERNAL ; 
 int EINVAL ; 
 int ENOENT ; 
 int KVM_REG_PPC_ICP_CPPR_SHIFT ; 
 int KVM_REG_PPC_ICP_MFRR_SHIFT ; 
 int KVM_REG_PPC_ICP_PPRI_SHIFT ; 
 int KVM_REG_PPC_ICP_XISR_MASK ; 
 int KVM_REG_PPC_ICP_XISR_SHIFT ; 
 union kvmppc_icp_state READ_ONCE (int /*<<< orphan*/ ) ; 
 int XICS_IPI ; 
 int /*<<< orphan*/  icp_check_resend (struct kvmppc_xics*,struct kvmppc_icp*) ; 
 int /*<<< orphan*/  icp_try_update (struct kvmppc_icp*,union kvmppc_icp_state,union kvmppc_icp_state,int) ; 
 int /*<<< orphan*/  kvmppc_book3s_dequeue_irqprio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct kvmppc_ics* kvmppc_xics_find_ics (struct kvmppc_xics*,int,int /*<<< orphan*/ *) ; 

int kvmppc_xics_set_icp(struct kvm_vcpu *vcpu, u64 icpval)
{
	struct kvmppc_icp *icp = vcpu->arch.icp;
	struct kvmppc_xics *xics = vcpu->kvm->arch.xics;
	union kvmppc_icp_state old_state, new_state;
	struct kvmppc_ics *ics;
	u8 cppr, mfrr, pending_pri;
	u32 xisr;
	u16 src;
	bool resend;

	if (!icp || !xics)
		return -ENOENT;

	cppr = icpval >> KVM_REG_PPC_ICP_CPPR_SHIFT;
	xisr = (icpval >> KVM_REG_PPC_ICP_XISR_SHIFT) &
		KVM_REG_PPC_ICP_XISR_MASK;
	mfrr = icpval >> KVM_REG_PPC_ICP_MFRR_SHIFT;
	pending_pri = icpval >> KVM_REG_PPC_ICP_PPRI_SHIFT;

	/* Require the new state to be internally consistent */
	if (xisr == 0) {
		if (pending_pri != 0xff)
			return -EINVAL;
	} else if (xisr == XICS_IPI) {
		if (pending_pri != mfrr || pending_pri >= cppr)
			return -EINVAL;
	} else {
		if (pending_pri >= mfrr || pending_pri >= cppr)
			return -EINVAL;
		ics = kvmppc_xics_find_ics(xics, xisr, &src);
		if (!ics)
			return -EINVAL;
	}

	new_state.raw = 0;
	new_state.cppr = cppr;
	new_state.xisr = xisr;
	new_state.mfrr = mfrr;
	new_state.pending_pri = pending_pri;

	/*
	 * Deassert the CPU interrupt request.
	 * icp_try_update will reassert it if necessary.
	 */
	kvmppc_book3s_dequeue_irqprio(icp->vcpu, BOOK3S_INTERRUPT_EXTERNAL);

	/*
	 * Note that if we displace an interrupt from old_state.xisr,
	 * we don't mark it as rejected.  We expect userspace to set
	 * the state of the interrupt sources to be consistent with
	 * the ICP states (either before or afterwards, which doesn't
	 * matter).  We do handle resends due to CPPR becoming less
	 * favoured because that is necessary to end up with a
	 * consistent state in the situation where userspace restores
	 * the ICS states before the ICP states.
	 */
	do {
		old_state = READ_ONCE(icp->state);

		if (new_state.mfrr <= old_state.mfrr) {
			resend = false;
			new_state.need_resend = old_state.need_resend;
		} else {
			resend = old_state.need_resend;
			new_state.need_resend = 0;
		}
	} while (!icp_try_update(icp, old_state, new_state, false));

	if (resend)
		icp_check_resend(xics, icp);

	return 0;
}
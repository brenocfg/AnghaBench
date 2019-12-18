#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
union kvmppc_icp_state {int xisr; int cppr; int pending_pri; } ;
typedef  int u32 ;
struct kvmppc_xics {int /*<<< orphan*/  real_mode; } ;
struct kvmppc_icp {int /*<<< orphan*/  state; int /*<<< orphan*/  vcpu; } ;
struct TYPE_7__ {int* gpr; } ;
struct TYPE_8__ {TYPE_3__ regs; struct kvmppc_icp* icp; } ;
struct kvm_vcpu {TYPE_4__ arch; TYPE_2__* kvm; } ;
struct TYPE_5__ {struct kvmppc_xics* xics; } ;
struct TYPE_6__ {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long H_TOO_HARD ; 
 union kvmppc_icp_state READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned long check_too_hard (struct kvmppc_xics*,struct kvmppc_icp*) ; 
 int /*<<< orphan*/  icp_rm_clr_vcpu_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  icp_rm_try_update (struct kvmppc_icp*,union kvmppc_icp_state,union kvmppc_icp_state) ; 

unsigned long xics_rm_h_xirr(struct kvm_vcpu *vcpu)
{
	union kvmppc_icp_state old_state, new_state;
	struct kvmppc_xics *xics = vcpu->kvm->arch.xics;
	struct kvmppc_icp *icp = vcpu->arch.icp;
	u32 xirr;

	if (!xics || !xics->real_mode)
		return H_TOO_HARD;

	/* First clear the interrupt */
	icp_rm_clr_vcpu_irq(icp->vcpu);

	/*
	 * ICP State: Accept_Interrupt
	 *
	 * Return the pending interrupt (if any) along with the
	 * current CPPR, then clear the XISR & set CPPR to the
	 * pending priority
	 */
	do {
		old_state = new_state = READ_ONCE(icp->state);

		xirr = old_state.xisr | (((u32)old_state.cppr) << 24);
		if (!old_state.xisr)
			break;
		new_state.cppr = new_state.pending_pri;
		new_state.pending_pri = 0xff;
		new_state.xisr = 0;

	} while (!icp_rm_try_update(icp, old_state, new_state));

	/* Return the result in GPR4 */
	vcpu->arch.regs.gpr[4] = xirr;

	return check_too_hard(xics, icp);
}
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
typedef  int u32 ;
typedef  size_t u16 ;
struct kvmppc_xics {int dummy; } ;
struct kvmppc_ics {struct ics_irq_state* irq_state; } ;
struct kvmppc_icp {int dummy; } ;
struct TYPE_5__ {struct kvmppc_icp* icp; } ;
struct kvm_vcpu {TYPE_3__* kvm; TYPE_2__ arch; } ;
struct ics_irq_state {int pq_state; scalar_t__ lsi; } ;
struct TYPE_4__ {struct kvmppc_xics* xics; } ;
struct TYPE_6__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int H_PARAMETER ; 
 int H_SUCCESS ; 
 int PQ_PRESENTED ; 
 int /*<<< orphan*/  XICS_DBG (char*,int) ; 
 int cmpxchg (int*,int,int) ; 
 int /*<<< orphan*/  icp_deliver_irq (struct kvmppc_xics*,struct kvmppc_icp*,int,int) ; 
 int /*<<< orphan*/  kvm_notify_acked_irq (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 struct kvmppc_ics* kvmppc_xics_find_ics (struct kvmppc_xics*,int,size_t*) ; 

__attribute__((used)) static int ics_eoi(struct kvm_vcpu *vcpu, u32 irq)
{
	struct kvmppc_xics *xics = vcpu->kvm->arch.xics;
	struct kvmppc_icp *icp = vcpu->arch.icp;
	struct kvmppc_ics *ics;
	struct ics_irq_state *state;
	u16 src;
	u32 pq_old, pq_new;

	/*
	 * ICS EOI handling: For LSI, if P bit is still set, we need to
	 * resend it.
	 *
	 * For MSI, we move Q bit into P (and clear Q). If it is set,
	 * resend it.
	 */

	ics = kvmppc_xics_find_ics(xics, irq, &src);
	if (!ics) {
		XICS_DBG("ios_eoi: IRQ 0x%06x not found !\n", irq);
		return H_PARAMETER;
	}
	state = &ics->irq_state[src];

	if (state->lsi)
		pq_new = state->pq_state;
	else
		do {
			pq_old = state->pq_state;
			pq_new = pq_old >> 1;
		} while (cmpxchg(&state->pq_state, pq_old, pq_new) != pq_old);

	if (pq_new & PQ_PRESENTED)
		icp_deliver_irq(xics, icp, irq, false);

	kvm_notify_acked_irq(vcpu->kvm, 0, irq);

	return H_SUCCESS;
}
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
struct TYPE_2__ {int /*<<< orphan*/  msg; } ;
union nic_mbx {TYPE_1__ msg; } ;
struct queue_set {int rbdr_cnt; } ;
struct nicvf {struct ifnet* ifp; int /*<<< orphan*/  stats_callout; struct queue_set* qs; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IFF_DRV_OACTIVE ; 
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  NICVF_CORE_LOCK_ASSERT (struct nicvf*) ; 
 int /*<<< orphan*/  NICVF_INTR_MBOX ; 
 int /*<<< orphan*/  NICVF_INTR_QS_ERR ; 
 int /*<<< orphan*/  NICVF_INTR_RBDR ; 
 int /*<<< orphan*/  NIC_MBOX_MSG_SHUTDOWN ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_setdrvflagbits (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_clear_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_config_data_transfer (struct nicvf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_disable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nicvf_qset_config (struct nicvf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_send_msg_to_pf (struct nicvf*,union nic_mbx*) ; 

__attribute__((used)) static int
nicvf_stop_locked(struct nicvf *nic)
{
	struct ifnet *ifp;
	int qidx;
	struct queue_set *qs = nic->qs;
	union nic_mbx mbx = {};

	NICVF_CORE_LOCK_ASSERT(nic);
	/* Stop callout. Can block here since holding SX lock */
	callout_drain(&nic->stats_callout);

	ifp = nic->ifp;

	mbx.msg.msg = NIC_MBOX_MSG_SHUTDOWN;
	nicvf_send_msg_to_pf(nic, &mbx);

	/* Disable RBDR & QS error interrupts */
	for (qidx = 0; qidx < qs->rbdr_cnt; qidx++) {
		nicvf_disable_intr(nic, NICVF_INTR_RBDR, qidx);
		nicvf_clear_intr(nic, NICVF_INTR_RBDR, qidx);
	}
	nicvf_disable_intr(nic, NICVF_INTR_QS_ERR, 0);
	nicvf_clear_intr(nic, NICVF_INTR_QS_ERR, 0);

	/* Deactivate network interface */
	if_setdrvflagbits(ifp, IFF_DRV_OACTIVE, IFF_DRV_RUNNING);

	/* Free resources */
	nicvf_config_data_transfer(nic, FALSE);

	/* Disable HW Qset */
	nicvf_qset_config(nic, FALSE);

	/* disable mailbox interrupt */
	nicvf_disable_intr(nic, NICVF_INTR_MBOX, 0);

	return (0);
}
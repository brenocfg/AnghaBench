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
struct queue_set {int cq_cnt; int rbdr_cnt; } ;
struct TYPE_2__ {scalar_t__ txq_wake; scalar_t__ txq_stop; } ;
struct nicvf {int /*<<< orphan*/  stats_callout; TYPE_1__ drv_stats; int /*<<< orphan*/  hwaddr; struct ifnet* ifp; struct queue_set* qs; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ETHER_ADDR_LEN ; 
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  NICVF_CORE_LOCK_ASSERT (struct nicvf*) ; 
 int /*<<< orphan*/  NICVF_INTR_CQ ; 
 int /*<<< orphan*/  NICVF_INTR_QS_ERR ; 
 int /*<<< orphan*/  NICVF_INTR_RBDR ; 
 int /*<<< orphan*/  NIC_VF_INT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nicvf*) ; 
 int /*<<< orphan*/  hz ; 
 int if_getdrvflags (struct ifnet*) ; 
 int /*<<< orphan*/  if_getlladdr (struct ifnet*) ; 
 int /*<<< orphan*/  if_printf (struct ifnet*,char*) ; 
 int /*<<< orphan*/  if_setdrvflagbits (struct ifnet*,int,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nicvf_enable_intr (struct nicvf*,int /*<<< orphan*/ ,int) ; 
 int nicvf_enable_misc_interrupt (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_hw_set_mac_addr (struct nicvf*,int /*<<< orphan*/ ) ; 
 int nicvf_init_resources (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_reg_write (struct nicvf*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  nicvf_stop_locked (struct nicvf*) ; 
 int /*<<< orphan*/  nicvf_tick_stats ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
nicvf_if_init_locked(struct nicvf *nic)
{
	struct queue_set *qs = nic->qs;
	struct ifnet *ifp;
	int qidx;
	int err;
	caddr_t if_addr;

	NICVF_CORE_LOCK_ASSERT(nic);
	ifp = nic->ifp;

	if ((if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0)
		nicvf_stop_locked(nic);

	err = nicvf_enable_misc_interrupt(nic);
	if (err != 0) {
		if_printf(ifp, "Could not reenable Mbox interrupt\n");
		return;
	}

	/* Get the latest MAC address */
	if_addr = if_getlladdr(ifp);
	/* Update MAC address if changed */
	if (memcmp(nic->hwaddr, if_addr, ETHER_ADDR_LEN) != 0) {
		memcpy(nic->hwaddr, if_addr, ETHER_ADDR_LEN);
		nicvf_hw_set_mac_addr(nic, if_addr);
	}

	/* Initialize the queues */
	err = nicvf_init_resources(nic);
	if (err != 0)
		goto error;

	/* Make sure queue initialization is written */
	wmb();

	nicvf_reg_write(nic, NIC_VF_INT, ~0UL);
	/* Enable Qset err interrupt */
	nicvf_enable_intr(nic, NICVF_INTR_QS_ERR, 0);

	/* Enable completion queue interrupt */
	for (qidx = 0; qidx < qs->cq_cnt; qidx++)
		nicvf_enable_intr(nic, NICVF_INTR_CQ, qidx);

	/* Enable RBDR threshold interrupt */
	for (qidx = 0; qidx < qs->rbdr_cnt; qidx++)
		nicvf_enable_intr(nic, NICVF_INTR_RBDR, qidx);

	nic->drv_stats.txq_stop = 0;
	nic->drv_stats.txq_wake = 0;

	/* Activate network interface */
	if_setdrvflagbits(ifp, IFF_DRV_RUNNING, IFF_DRV_OACTIVE);

	/* Schedule callout to update stats */
	callout_reset(&nic->stats_callout, hz, nicvf_tick_stats, nic);

	return;

error:
	/* Something went very wrong. Disable this ifnet for good */
	if_setdrvflagbits(ifp, IFF_DRV_OACTIVE, IFF_DRV_RUNNING);
}
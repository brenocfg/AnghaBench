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
struct TYPE_4__ {scalar_t__ rsp_cons; TYPE_1__* sring; } ;
struct netfront_rxq {TYPE_2__ ring; } ;
struct netfront_info {int num_queues; struct netfront_rxq* rxq; struct ifnet* xn_ifp; } ;
struct ifnet {int if_drv_flags; } ;
struct TYPE_3__ {scalar_t__ rsp_event; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 scalar_t__ RING_HAS_UNCONSUMED_RESPONSES (TYPE_2__*) ; 
 int /*<<< orphan*/  XN_LOCK_ASSERT (struct netfront_info*) ; 
 int /*<<< orphan*/  XN_RX_LOCK (struct netfront_rxq*) ; 
 int /*<<< orphan*/  XN_RX_UNLOCK (struct netfront_rxq*) ; 
 int /*<<< orphan*/  if_link_state_change (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netfront_carrier_ok (struct netfront_info*) ; 
 int /*<<< orphan*/  xn_alloc_rx_buffers (struct netfront_rxq*) ; 
 int /*<<< orphan*/  xn_rxeof (struct netfront_rxq*) ; 
 int /*<<< orphan*/  xn_stop (struct netfront_info*) ; 

__attribute__((used)) static void
xn_ifinit_locked(struct netfront_info *np)
{
	struct ifnet *ifp;
	int i;
	struct netfront_rxq *rxq;

	XN_LOCK_ASSERT(np);

	ifp = np->xn_ifp;

	if (ifp->if_drv_flags & IFF_DRV_RUNNING || !netfront_carrier_ok(np))
		return;

	xn_stop(np);

	for (i = 0; i < np->num_queues; i++) {
		rxq = &np->rxq[i];
		XN_RX_LOCK(rxq);
		xn_alloc_rx_buffers(rxq);
		rxq->ring.sring->rsp_event = rxq->ring.rsp_cons + 1;
		if (RING_HAS_UNCONSUMED_RESPONSES(&rxq->ring))
			xn_rxeof(rxq);
		XN_RX_UNLOCK(rxq);
	}

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;
	if_link_state_change(ifp, LINK_STATE_UP);
}
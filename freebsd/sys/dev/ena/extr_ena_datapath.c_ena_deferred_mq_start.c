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
struct ifnet {int dummy; } ;
struct ena_ring {scalar_t__ running; int /*<<< orphan*/  br; TYPE_1__* adapter; } ;
struct TYPE_2__ {struct ifnet* ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_RING_MTX_LOCK (struct ena_ring*) ; 
 int /*<<< orphan*/  ENA_RING_MTX_UNLOCK (struct ena_ring*) ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  drbr_empty (struct ifnet*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_start_xmit (struct ena_ring*) ; 
 int if_getdrvflags (struct ifnet*) ; 

void
ena_deferred_mq_start(void *arg, int pending)
{
	struct ena_ring *tx_ring = (struct ena_ring *)arg;
	struct ifnet *ifp = tx_ring->adapter->ifp;

	while (!drbr_empty(ifp, tx_ring->br) &&
	    tx_ring->running &&
	    (if_getdrvflags(ifp) & IFF_DRV_RUNNING) != 0) {
		ENA_RING_MTX_LOCK(tx_ring);
		ena_start_xmit(tx_ring);
		ENA_RING_MTX_UNLOCK(tx_ring);
	}
}
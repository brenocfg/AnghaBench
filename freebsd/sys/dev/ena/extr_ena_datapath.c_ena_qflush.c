#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ena_ring {int /*<<< orphan*/  br; } ;
struct ena_adapter {int num_queues; struct ena_ring* tx_ring; } ;
typedef  TYPE_1__* if_t ;
struct TYPE_6__ {struct ena_adapter* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_RING_MTX_LOCK (struct ena_ring*) ; 
 int /*<<< orphan*/  ENA_RING_MTX_UNLOCK (struct ena_ring*) ; 
 int /*<<< orphan*/  drbr_empty (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbr_flush (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_qflush (TYPE_1__*) ; 

void
ena_qflush(if_t ifp)
{
	struct ena_adapter *adapter = ifp->if_softc;
	struct ena_ring *tx_ring = adapter->tx_ring;
	int i;

	for(i = 0; i < adapter->num_queues; ++i, ++tx_ring)
		if (!drbr_empty(ifp, tx_ring->br)) {
			ENA_RING_MTX_LOCK(tx_ring);
			drbr_flush(ifp, tx_ring->br);
			ENA_RING_MTX_UNLOCK(tx_ring);
		}

	if_qflush(ifp);
}
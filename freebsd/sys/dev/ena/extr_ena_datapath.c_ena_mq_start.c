#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint32_t ;
struct TYPE_6__ {size_t flowid; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct ena_ring {int /*<<< orphan*/  enqueue_task; int /*<<< orphan*/  enqueue_tq; int /*<<< orphan*/  br; } ;
struct ena_adapter {size_t num_queues; struct ena_ring* tx_ring; int /*<<< orphan*/  ifp; } ;
typedef  TYPE_2__* if_t ;
struct TYPE_7__ {struct ena_adapter* if_softc; } ;

/* Variables and functions */
 scalar_t__ ENA_RING_MTX_TRYLOCK (struct ena_ring*) ; 
 int /*<<< orphan*/  ENA_RING_MTX_UNLOCK (struct ena_ring*) ; 
 int ENODEV ; 
 int IFF_DRV_RUNNING ; 
 scalar_t__ M_HASHTYPE_GET (struct mbuf*) ; 
 scalar_t__ M_HASHTYPE_NONE ; 
 size_t curcpu ; 
 int drbr_empty (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int drbr_enqueue (TYPE_2__*,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  ena_start_xmit (struct ena_ring*) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int
ena_mq_start(if_t ifp, struct mbuf *m)
{
	struct ena_adapter *adapter = ifp->if_softc;
	struct ena_ring *tx_ring;
	int ret, is_drbr_empty;
	uint32_t i;

	if (unlikely((if_getdrvflags(adapter->ifp) & IFF_DRV_RUNNING) == 0))
		return (ENODEV);

	/* Which queue to use */
	/*
	 * If everything is setup correctly, it should be the
	 * same bucket that the current CPU we're on is.
	 * It should improve performance.
	 */
	if (M_HASHTYPE_GET(m) != M_HASHTYPE_NONE) {
		i = m->m_pkthdr.flowid % adapter->num_queues;
	} else {
		i = curcpu % adapter->num_queues;
	}
	tx_ring = &adapter->tx_ring[i];

	/* Check if drbr is empty before putting packet */
	is_drbr_empty = drbr_empty(ifp, tx_ring->br);
	ret = drbr_enqueue(ifp, tx_ring->br, m);
	if (unlikely(ret != 0)) {
		taskqueue_enqueue(tx_ring->enqueue_tq, &tx_ring->enqueue_task);
		return (ret);
	}

	if (is_drbr_empty && (ENA_RING_MTX_TRYLOCK(tx_ring) != 0)) {
		ena_start_xmit(tx_ring);
		ENA_RING_MTX_UNLOCK(tx_ring);
	} else {
		taskqueue_enqueue(tx_ring->enqueue_tq, &tx_ring->enqueue_task);
	}

	return (0);
}
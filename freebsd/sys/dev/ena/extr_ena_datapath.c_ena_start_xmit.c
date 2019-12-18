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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {scalar_t__ csum_flags; } ;
struct mbuf {TYPE_2__ m_pkthdr; int /*<<< orphan*/  m_flags; } ;
struct TYPE_7__ {int /*<<< orphan*/  doorbells; } ;
struct ena_ring {scalar_t__ acum_pkts; TYPE_4__* que; int /*<<< orphan*/  running; TYPE_3__ tx_stats; int /*<<< orphan*/  br; struct ena_adapter* adapter; } ;
struct ena_com_io_sq {int dummy; } ;
struct ena_adapter {int /*<<< orphan*/  ifp; TYPE_1__* ena_dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  cleanup_task; int /*<<< orphan*/  cleanup_tq; int /*<<< orphan*/  id; } ;
struct TYPE_5__ {struct ena_com_io_sq* io_sq_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MTAP (int /*<<< orphan*/ ,struct mbuf*) ; 
 int ENA_COM_NO_MEM ; 
 int ENA_COM_NO_SPACE ; 
 int ENA_DBG ; 
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_LINK_UP ; 
 int ENA_IO_TXQ_IDX (int /*<<< orphan*/ ) ; 
 int ENA_TXPTH ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drbr_advance (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mbuf* drbr_peek (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbr_putback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*) ; 
 int /*<<< orphan*/  ena_com_write_sq_doorbell (struct ena_com_io_sq*) ; 
 int /*<<< orphan*/  ena_trace (int,char*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ena_xmit_mbuf (struct ena_ring*,struct mbuf**) ; 
 int if_getdrvflags (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void
ena_start_xmit(struct ena_ring *tx_ring)
{
	struct mbuf *mbuf;
	struct ena_adapter *adapter = tx_ring->adapter;
	struct ena_com_io_sq* io_sq;
	int ena_qid;
	int ret = 0;

	if (unlikely((if_getdrvflags(adapter->ifp) & IFF_DRV_RUNNING) == 0))
		return;

	if (unlikely(!ENA_FLAG_ISSET(ENA_FLAG_LINK_UP, adapter)))
		return;

	ena_qid = ENA_IO_TXQ_IDX(tx_ring->que->id);
	io_sq = &adapter->ena_dev->io_sq_queues[ena_qid];

	while ((mbuf = drbr_peek(adapter->ifp, tx_ring->br)) != NULL) {
		ena_trace(ENA_DBG | ENA_TXPTH, "\ndequeued mbuf %p with flags %#x and"
		    " header csum flags %#jx\n",
		    mbuf, mbuf->m_flags, (uint64_t)mbuf->m_pkthdr.csum_flags);

		if (unlikely(!tx_ring->running)) {
			drbr_putback(adapter->ifp, tx_ring->br, mbuf);
			break;
		}

		if (unlikely((ret = ena_xmit_mbuf(tx_ring, &mbuf)) != 0)) {
			if (ret == ENA_COM_NO_MEM) {
				drbr_putback(adapter->ifp, tx_ring->br, mbuf);
			} else if (ret == ENA_COM_NO_SPACE) {
				drbr_putback(adapter->ifp, tx_ring->br, mbuf);
			} else {
				m_freem(mbuf);
				drbr_advance(adapter->ifp, tx_ring->br);
			}

			break;
		}

		drbr_advance(adapter->ifp, tx_ring->br);

		if (unlikely((if_getdrvflags(adapter->ifp) &
		    IFF_DRV_RUNNING) == 0))
			return;

		tx_ring->acum_pkts++;

		BPF_MTAP(adapter->ifp, mbuf);
	}

	if (likely(tx_ring->acum_pkts != 0)) {
		wmb();
		/* Trigger the dma engine */
		ena_com_write_sq_doorbell(io_sq);
		counter_u64_add(tx_ring->tx_stats.doorbells, 1);
		tx_ring->acum_pkts = 0;
	}

	if (unlikely(!tx_ring->running))
		taskqueue_enqueue(tx_ring->que->cleanup_tq,
		    &tx_ring->que->cleanup_task);
}
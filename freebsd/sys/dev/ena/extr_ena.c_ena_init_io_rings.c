#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ena_ring {scalar_t__ empty_rx_queue; struct ena_que* que; int /*<<< orphan*/  mtx_name; int /*<<< orphan*/  ring_mtx; int /*<<< orphan*/  rx_stats; int /*<<< orphan*/  smoothed_interval; int /*<<< orphan*/  ring_size; int /*<<< orphan*/  tx_stats; int /*<<< orphan*/  buf_ring_size; int /*<<< orphan*/  br; int /*<<< orphan*/  tx_mem_queue_type; int /*<<< orphan*/  tx_max_header_size; } ;
struct ena_que {int id; struct ena_ring* rx_ring; struct ena_ring* tx_ring; struct ena_adapter* adapter; } ;
struct ena_com_dev {int /*<<< orphan*/  tx_mem_queue_type; int /*<<< orphan*/  tx_max_header_size; } ;
struct ena_adapter {int num_queues; struct ena_que* que; int /*<<< orphan*/  pdev; int /*<<< orphan*/  rx_ring_size; int /*<<< orphan*/  buf_ring_size; int /*<<< orphan*/  tx_ring_size; struct ena_ring* rx_ring; struct ena_ring* tx_ring; struct ena_com_dev* ena_dev; } ;
typedef  int /*<<< orphan*/  counter_u64_t ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  buf_ring_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ena_alloc_counters (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ena_com_get_nonadaptive_moderation_interval_rx (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_com_get_nonadaptive_moderation_interval_tx (struct ena_com_dev*) ; 
 int /*<<< orphan*/  ena_init_io_rings_common (struct ena_adapter*,struct ena_ring*,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nitems (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static void
ena_init_io_rings(struct ena_adapter *adapter)
{
	struct ena_com_dev *ena_dev;
	struct ena_ring *txr, *rxr;
	struct ena_que *que;
	int i;

	ena_dev = adapter->ena_dev;

	for (i = 0; i < adapter->num_queues; i++) {
		txr = &adapter->tx_ring[i];
		rxr = &adapter->rx_ring[i];

		/* TX/RX common ring state */
		ena_init_io_rings_common(adapter, txr, i);
		ena_init_io_rings_common(adapter, rxr, i);

		/* TX specific ring state */
		txr->ring_size = adapter->tx_ring_size;
		txr->tx_max_header_size = ena_dev->tx_max_header_size;
		txr->tx_mem_queue_type = ena_dev->tx_mem_queue_type;
		txr->smoothed_interval =
		    ena_com_get_nonadaptive_moderation_interval_tx(ena_dev);

		/* Allocate a buf ring */
		txr->buf_ring_size = adapter->buf_ring_size;
		txr->br = buf_ring_alloc(txr->buf_ring_size, M_DEVBUF,
		    M_WAITOK, &txr->ring_mtx);

		/* Alloc TX statistics. */
		ena_alloc_counters((counter_u64_t *)&txr->tx_stats,
		    sizeof(txr->tx_stats));

		/* RX specific ring state */
		rxr->ring_size = adapter->rx_ring_size;
		rxr->smoothed_interval =
		    ena_com_get_nonadaptive_moderation_interval_rx(ena_dev);

		/* Alloc RX statistics. */
		ena_alloc_counters((counter_u64_t *)&rxr->rx_stats,
		    sizeof(rxr->rx_stats));

		/* Initialize locks */
		snprintf(txr->mtx_name, nitems(txr->mtx_name), "%s:tx(%d)",
		    device_get_nameunit(adapter->pdev), i);
		snprintf(rxr->mtx_name, nitems(rxr->mtx_name), "%s:rx(%d)",
		    device_get_nameunit(adapter->pdev), i);

		mtx_init(&txr->ring_mtx, txr->mtx_name, NULL, MTX_DEF);

		que = &adapter->que[i];
		que->adapter = adapter;
		que->id = i;
		que->tx_ring = txr;
		que->rx_ring = rxr;

		txr->que = que;
		rxr->que = que;

		rxr->empty_rx_queue = 0;
	}
}
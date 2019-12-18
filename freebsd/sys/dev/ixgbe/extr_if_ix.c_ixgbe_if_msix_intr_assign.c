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
struct TYPE_4__ {int /*<<< orphan*/  me; } ;
struct ix_tx_queue {int msix; TYPE_2__ txr; } ;
struct TYPE_3__ {int /*<<< orphan*/  me; } ;
struct ix_rx_queue {int num_rx_queues; int msix; int feat_en; int num_tx_queues; int vector; int /*<<< orphan*/  que_irq; struct ix_rx_queue* rx_queues; int /*<<< orphan*/  irq; struct ix_tx_queue* tx_queues; TYPE_1__ rxr; } ;
struct adapter {int num_rx_queues; int msix; int feat_en; int num_tx_queues; int vector; int /*<<< orphan*/  que_irq; struct adapter* rx_queues; int /*<<< orphan*/  irq; struct ix_tx_queue* tx_queues; TYPE_1__ rxr; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  IFLIB_INTR_ADMIN ; 
 int /*<<< orphan*/  IFLIB_INTR_RX ; 
 int /*<<< orphan*/  IFLIB_INTR_TX ; 
 int IXGBE_FEATURE_RSS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct ix_rx_queue* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int iflib_irq_alloc_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ix_rx_queue*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_irq_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iflib_softirq_alloc_generic (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ix_tx_queue*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ixgbe_msix_link ; 
 int /*<<< orphan*/  ixgbe_msix_que ; 
 int rss_getcpu (int) ; 
 int rss_getnumbuckets () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
ixgbe_if_msix_intr_assign(if_ctx_t ctx, int msix)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	struct ix_rx_queue *rx_que = adapter->rx_queues;
	struct ix_tx_queue *tx_que;
	int                error, rid, vector = 0;
	int                cpu_id = 0;
	char               buf[16];

	/* Admin Que is vector 0*/
	rid = vector + 1;
	for (int i = 0; i < adapter->num_rx_queues; i++, vector++, rx_que++) {
		rid = vector + 1;

		snprintf(buf, sizeof(buf), "rxq%d", i);
		error = iflib_irq_alloc_generic(ctx, &rx_que->que_irq, rid,
		    IFLIB_INTR_RX, ixgbe_msix_que, rx_que, rx_que->rxr.me, buf);

		if (error) {
			device_printf(iflib_get_dev(ctx),
			    "Failed to allocate que int %d err: %d", i, error);
			adapter->num_rx_queues = i + 1;
			goto fail;
		}

		rx_que->msix = vector;
		if (adapter->feat_en & IXGBE_FEATURE_RSS) {
			/*
			 * The queue ID is used as the RSS layer bucket ID.
			 * We look up the queue ID -> RSS CPU ID and select
			 * that.
			 */
			cpu_id = rss_getcpu(i % rss_getnumbuckets());
		} else {
			/*
			 * Bind the MSI-X vector, and thus the
			 * rings to the corresponding cpu.
			 *
			 * This just happens to match the default RSS
			 * round-robin bucket -> queue -> CPU allocation.
			 */
			if (adapter->num_rx_queues > 1)
				cpu_id = i;
		}

	}
	for (int i = 0; i < adapter->num_tx_queues; i++) {
		snprintf(buf, sizeof(buf), "txq%d", i);
		tx_que = &adapter->tx_queues[i];
		tx_que->msix = i % adapter->num_rx_queues;
		iflib_softirq_alloc_generic(ctx,
		    &adapter->rx_queues[tx_que->msix].que_irq,
		    IFLIB_INTR_TX, tx_que, tx_que->txr.me, buf);
	}
	rid = vector + 1;
	error = iflib_irq_alloc_generic(ctx, &adapter->irq, rid,
	    IFLIB_INTR_ADMIN, ixgbe_msix_link, adapter, 0, "aq");
	if (error) {
		device_printf(iflib_get_dev(ctx),
		    "Failed to register admin handler");
		return (error);
	}

	adapter->vector = vector;

	return (0);
fail:
	iflib_irq_free(ctx, &adapter->irq);
	rx_que = adapter->rx_queues;
	for (int i = 0; i < adapter->num_rx_queues; i++, rx_que++)
		iflib_irq_free(ctx, &rx_que->que_irq);

	return (error);
}
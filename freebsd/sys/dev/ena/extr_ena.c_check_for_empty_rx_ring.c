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
struct TYPE_3__ {int /*<<< orphan*/  empty_rx_ring; } ;
struct ena_ring {int ring_size; scalar_t__ empty_rx_queue; TYPE_2__* que; TYPE_1__ rx_stats; int /*<<< orphan*/  ena_com_io_sq; } ;
struct ena_adapter {int num_queues; int /*<<< orphan*/  pdev; struct ena_ring* rx_ring; } ;
struct TYPE_4__ {int /*<<< orphan*/  cleanup_task; int /*<<< orphan*/  cleanup_tq; } ;

/* Variables and functions */
 scalar_t__ EMPTY_RX_REFILL ; 
 int /*<<< orphan*/  ENA_FLAG_DEV_UP ; 
 scalar_t__ ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int ena_com_free_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
check_for_empty_rx_ring(struct ena_adapter *adapter)
{
	struct ena_ring *rx_ring;
	int i, refill_required;

	if (!ENA_FLAG_ISSET(ENA_FLAG_DEV_UP, adapter))
		return;

	if (ENA_FLAG_ISSET(ENA_FLAG_TRIGGER_RESET, adapter))
		return;

	for (i = 0; i < adapter->num_queues; i++) {
		rx_ring = &adapter->rx_ring[i];

		refill_required = ena_com_free_desc(rx_ring->ena_com_io_sq);
		if (unlikely(refill_required == (rx_ring->ring_size - 1))) {
			rx_ring->empty_rx_queue++;

			if (rx_ring->empty_rx_queue >= EMPTY_RX_REFILL)	{
				counter_u64_add(rx_ring->rx_stats.empty_rx_ring,
				    1);

				device_printf(adapter->pdev,
				    "trigger refill for ring %d\n", i);

				taskqueue_enqueue(rx_ring->que->cleanup_tq,
				    &rx_ring->que->cleanup_task);
				rx_ring->empty_rx_queue = 0;
			}
		} else {
			rx_ring->empty_rx_queue = 0;
		}
	}
}
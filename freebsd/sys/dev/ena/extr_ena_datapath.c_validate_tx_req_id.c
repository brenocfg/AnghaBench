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
typedef  size_t uint16_t ;
struct ena_tx_buffer {int /*<<< orphan*/ * mbuf; } ;
struct TYPE_2__ {int /*<<< orphan*/  bad_req_id; } ;
struct ena_ring {size_t ring_size; TYPE_1__ tx_stats; struct ena_tx_buffer* tx_buffer_info; struct ena_adapter* adapter; } ;
struct ena_adapter {int /*<<< orphan*/  reset_reason; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_INV_TX_REQ_ID ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline int
validate_tx_req_id(struct ena_ring *tx_ring, uint16_t req_id)
{
	struct ena_adapter *adapter = tx_ring->adapter;
	struct ena_tx_buffer *tx_info = NULL;

	if (likely(req_id < tx_ring->ring_size)) {
		tx_info = &tx_ring->tx_buffer_info[req_id];
		if (tx_info->mbuf != NULL)
			return (0);
		device_printf(adapter->pdev,
		    "tx_info doesn't have valid mbuf\n");
	}

	device_printf(adapter->pdev, "Invalid req_id: %hu\n", req_id);
	counter_u64_add(tx_ring->tx_stats.bad_req_id, 1);

	/* Trigger device reset */
	adapter->reset_reason = ENA_REGS_RESET_INV_TX_REQ_ID;
	ENA_FLAG_SET_ATOMIC(ENA_FLAG_TRIGGER_RESET, adapter);

	return (EFAULT);
}
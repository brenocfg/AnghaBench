#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  bad_req_id; } ;
struct ena_ring {scalar_t__ ring_size; TYPE_2__* adapter; TYPE_1__ rx_stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  reset_reason; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_INV_RX_REQ_ID ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static inline int
validate_rx_req_id(struct ena_ring *rx_ring, uint16_t req_id)
{
	if (likely(req_id < rx_ring->ring_size))
		return (0);

	device_printf(rx_ring->adapter->pdev, "Invalid rx req_id: %hu\n",
	    req_id);
	counter_u64_add(rx_ring->rx_stats.bad_req_id, 1);

	/* Trigger device reset */
	if (likely(!ENA_FLAG_ISSET(ENA_FLAG_TRIGGER_RESET, rx_ring->adapter))) {
		rx_ring->adapter->reset_reason = ENA_REGS_RESET_INV_RX_REQ_ID;
		ENA_FLAG_SET_ATOMIC(ENA_FLAG_TRIGGER_RESET, rx_ring->adapter);
	}

	return (EFAULT);
}
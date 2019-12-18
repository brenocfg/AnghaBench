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
struct ena_ring {int first_interrupt; scalar_t__ no_interrupt_event_cnt; int /*<<< orphan*/  qid; int /*<<< orphan*/  ena_com_io_cq; } ;
struct ena_adapter {int /*<<< orphan*/  reset_reason; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 scalar_t__ ENA_MAX_NO_INTERRUPT_ITERATIONS ; 
 int /*<<< orphan*/  ENA_REGS_RESET_MISS_INTERRUPT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ena_com_cq_empty (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 

__attribute__((used)) static int
check_for_rx_interrupt_queue(struct ena_adapter *adapter,
    struct ena_ring *rx_ring)
{
	if (likely(rx_ring->first_interrupt))
		return (0);

	if (ena_com_cq_empty(rx_ring->ena_com_io_cq))
		return (0);

	rx_ring->no_interrupt_event_cnt++;

	if (rx_ring->no_interrupt_event_cnt == ENA_MAX_NO_INTERRUPT_ITERATIONS) {
		device_printf(adapter->pdev, "Potential MSIX issue on Rx side "
		    "Queue = %d. Reset the device\n", rx_ring->qid);
		if (likely(!ENA_FLAG_ISSET(ENA_FLAG_TRIGGER_RESET, adapter))) {
			adapter->reset_reason = ENA_REGS_RESET_MISS_INTERRUPT;
			ENA_FLAG_SET_ATOMIC(ENA_FLAG_TRIGGER_RESET, adapter);
		}
		return (EIO);
	}

	return (0);
}
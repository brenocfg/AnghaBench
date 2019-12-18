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
typedef  scalar_t__ uint32_t ;
struct ena_tx_buffer {int print_once; int /*<<< orphan*/  timestamp; } ;
struct TYPE_2__ {int /*<<< orphan*/  missing_tx_comp; } ;
struct ena_ring {int ring_size; TYPE_1__ tx_stats; int /*<<< orphan*/  qid; int /*<<< orphan*/  first_interrupt; struct ena_tx_buffer* tx_buffer_info; } ;
struct ena_adapter {int missing_tx_timeout; int /*<<< orphan*/  reset_reason; scalar_t__ missing_tx_threshold; int /*<<< orphan*/  pdev; } ;
struct bintime {int dummy; } ;
typedef  int sbintime_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ENA_FLAG_ISSET (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_SET_ATOMIC (int /*<<< orphan*/ ,struct ena_adapter*) ; 
 int /*<<< orphan*/  ENA_FLAG_TRIGGER_RESET ; 
 int /*<<< orphan*/  ENA_REGS_RESET_MISS_INTERRUPT ; 
 int /*<<< orphan*/  ENA_REGS_RESET_MISS_TX_CMPL ; 
 int /*<<< orphan*/  ENA_WARNING ; 
 scalar_t__ bintime_isset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bintime_sub (struct bintime*,int /*<<< orphan*/ *) ; 
 int bttosbt (struct bintime) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  ena_trace (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  getbinuptime (struct bintime*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
check_missing_comp_in_tx_queue(struct ena_adapter *adapter,
    struct ena_ring *tx_ring)
{
	struct bintime curtime, time;
	struct ena_tx_buffer *tx_buf;
	sbintime_t time_offset;
	uint32_t missed_tx = 0;
	int i, rc = 0;

	getbinuptime(&curtime);

	for (i = 0; i < tx_ring->ring_size; i++) {
		tx_buf = &tx_ring->tx_buffer_info[i];

		if (bintime_isset(&tx_buf->timestamp) == 0)
			continue;

		time = curtime;
		bintime_sub(&time, &tx_buf->timestamp);
		time_offset = bttosbt(time);

		if (unlikely(!tx_ring->first_interrupt &&
		    time_offset > 2 * adapter->missing_tx_timeout)) {
			/*
			 * If after graceful period interrupt is still not
			 * received, we schedule a reset.
			 */
			device_printf(adapter->pdev,
			    "Potential MSIX issue on Tx side Queue = %d. "
			    "Reset the device\n", tx_ring->qid);
			if (likely(!ENA_FLAG_ISSET(ENA_FLAG_TRIGGER_RESET,
			    adapter))) {
				adapter->reset_reason =
				    ENA_REGS_RESET_MISS_INTERRUPT;
				ENA_FLAG_SET_ATOMIC(ENA_FLAG_TRIGGER_RESET,
				    adapter);
			}
			return (EIO);
		}

		/* Check again if packet is still waiting */
		if (unlikely(time_offset > adapter->missing_tx_timeout)) {

			if (!tx_buf->print_once)
				ena_trace(ENA_WARNING, "Found a Tx that wasn't "
				    "completed on time, qid %d, index %d.\n",
				    tx_ring->qid, i);

			tx_buf->print_once = true;
			missed_tx++;
		}
	}

	if (unlikely(missed_tx > adapter->missing_tx_threshold)) {
		device_printf(adapter->pdev,
		    "The number of lost tx completion is above the threshold "
		    "(%d > %d). Reset the device\n",
		    missed_tx, adapter->missing_tx_threshold);
		if (likely(!ENA_FLAG_ISSET(ENA_FLAG_TRIGGER_RESET, adapter))) {
			adapter->reset_reason = ENA_REGS_RESET_MISS_TX_CMPL;
			ENA_FLAG_SET_ATOMIC(ENA_FLAG_TRIGGER_RESET, adapter);
		}
		rc = EIO;
	}

	counter_u64_add(tx_ring->tx_stats.missing_tx_comp, missed_tx);

	return (rc);
}
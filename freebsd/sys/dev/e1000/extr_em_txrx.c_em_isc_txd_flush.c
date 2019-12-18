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
typedef  size_t uint16_t ;
struct tx_ring {int /*<<< orphan*/  me; } ;
struct em_tx_queue {struct tx_ring txr; } ;
struct adapter {int /*<<< orphan*/  hw; struct em_tx_queue* tx_queues; } ;
typedef  int /*<<< orphan*/  qidx_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_TDT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_isc_txd_flush(void *arg, uint16_t txqid, qidx_t pidx)
{
	struct adapter *adapter = arg;
	struct em_tx_queue *que = &adapter->tx_queues[txqid];
	struct tx_ring *txr = &que->txr;

	E1000_WRITE_REG(&adapter->hw, E1000_TDT(txr->me), pidx);
}
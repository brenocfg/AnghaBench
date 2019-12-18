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
struct em_tx_queue {int /*<<< orphan*/  eims; } ;
struct adapter {int /*<<< orphan*/  hw; struct em_tx_queue* tx_queues; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_IMS ; 
 int /*<<< orphan*/  E1000_WRITE_REG (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
em_if_tx_queue_intr_enable(if_ctx_t ctx, uint16_t txqid)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct em_tx_queue *txq = &adapter->tx_queues[txqid];

	E1000_WRITE_REG(&adapter->hw, E1000_IMS, txq->eims);
	return (0);
}
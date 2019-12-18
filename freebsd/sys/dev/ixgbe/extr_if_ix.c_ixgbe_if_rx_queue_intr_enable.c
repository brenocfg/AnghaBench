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
struct ix_rx_queue {int /*<<< orphan*/  msix; } ;
struct adapter {struct ix_rx_queue* rx_queues; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_enable_queue (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixgbe_if_rx_queue_intr_enable(if_ctx_t ctx, uint16_t rxqid)
{
	struct adapter     *adapter = iflib_get_softc(ctx);
	struct ix_rx_queue *que = &adapter->rx_queues[rxqid];

	ixgbe_enable_queue(adapter, que->msix);

	return (0);
}
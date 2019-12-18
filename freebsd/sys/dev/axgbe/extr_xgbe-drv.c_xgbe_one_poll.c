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
struct xgbe_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGPR (char*,int) ; 
 int xgbe_rx_poll (struct xgbe_channel*,int) ; 
 int /*<<< orphan*/  xgbe_tx_poll (struct xgbe_channel*) ; 

__attribute__((used)) static int xgbe_one_poll(struct xgbe_channel *channel, int budget)
{
	int processed = 0;

	DBGPR("-->xgbe_one_poll: budget=%d\n", budget);

	/* Cleanup Tx ring first */
	xgbe_tx_poll(channel);

	/* Process Rx ring next */
	processed = xgbe_rx_poll(channel, budget);

	DBGPR("<--xgbe_one_poll: received = %d\n", processed);

	return processed;
}
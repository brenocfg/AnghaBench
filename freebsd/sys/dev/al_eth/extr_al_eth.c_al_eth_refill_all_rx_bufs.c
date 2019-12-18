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
struct al_eth_adapter {int num_rx_queues; } ;

/* Variables and functions */
 scalar_t__ AL_ETH_DEFAULT_RX_DESCS ; 
 int /*<<< orphan*/  al_eth_refill_rx_bufs (struct al_eth_adapter*,int,scalar_t__) ; 

__attribute__((used)) static void
al_eth_refill_all_rx_bufs(struct al_eth_adapter *adapter)
{
	int i;

	for (i = 0; i < adapter->num_rx_queues; i++)
		al_eth_refill_rx_bufs(adapter, i, AL_ETH_DEFAULT_RX_DESCS - 1);
}
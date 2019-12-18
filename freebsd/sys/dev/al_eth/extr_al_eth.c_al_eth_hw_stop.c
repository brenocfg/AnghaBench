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
struct al_eth_adapter {int /*<<< orphan*/  flags; int /*<<< orphan*/  hal_adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  AL_ETH_FLAG_RESET_REQUESTED ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  al_eth_adapter_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  al_eth_flow_ctrl_disable (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_eth_mac_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
al_eth_hw_stop(struct al_eth_adapter *adapter)
{

	al_eth_mac_stop(&adapter->hal_adapter);

	/*
	 * wait till pending rx packets written and UDMA becomes idle,
	 * the MAC has ~10KB fifo, 10us should be enought time for the
	 * UDMA to write to the memory
	 */
	DELAY(10);

	al_eth_adapter_stop(&adapter->hal_adapter);

	adapter->flags |= AL_ETH_FLAG_RESET_REQUESTED;

	/* disable flow ctrl to avoid pause packets*/
	al_eth_flow_ctrl_disable(adapter);

	return (0);
}
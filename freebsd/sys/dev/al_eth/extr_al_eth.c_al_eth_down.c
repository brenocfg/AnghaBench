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
struct al_eth_adapter {int up; int /*<<< orphan*/  stats_mtx; int /*<<< orphan*/  stats_callout; int /*<<< orphan*/  wd_mtx; int /*<<< orphan*/  wd_callout; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  al_eth_disable_int_sync (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_eth_free_all_rx_resources (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_eth_free_all_tx_resources (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_eth_free_irq (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  al_eth_hw_stop (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
al_eth_down(struct al_eth_adapter *adapter)
{

	device_printf_dbg(adapter->dev, "al_eth_down: begin\n");

	adapter->up = false;

	mtx_lock(&adapter->wd_mtx);
	callout_stop(&adapter->wd_callout);
	mtx_unlock(&adapter->wd_mtx);

	al_eth_disable_int_sync(adapter);

	mtx_lock(&adapter->stats_mtx);
	callout_stop(&adapter->stats_callout);
	mtx_unlock(&adapter->stats_mtx);

	al_eth_free_irq(adapter);
	al_eth_hw_stop(adapter);

	al_eth_free_all_tx_resources(adapter);
	al_eth_free_all_rx_resources(adapter);
}
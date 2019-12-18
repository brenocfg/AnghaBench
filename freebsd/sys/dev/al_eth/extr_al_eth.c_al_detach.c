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
struct al_eth_adapter {int /*<<< orphan*/  udma_res; int /*<<< orphan*/  mac_res; int /*<<< orphan*/  ec_res; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  wd_mtx; int /*<<< orphan*/  stats_mtx; int /*<<< orphan*/  netdev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  al_eth_down (struct al_eth_adapter*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct al_eth_adapter* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
al_detach(device_t dev)
{
	struct al_eth_adapter *adapter;

	adapter = device_get_softc(dev);
	ether_ifdetach(adapter->netdev);

	mtx_destroy(&adapter->stats_mtx);
	mtx_destroy(&adapter->wd_mtx);

	al_eth_down(adapter);

	bus_release_resource(dev, SYS_RES_IRQ,    0, adapter->irq_res);
	bus_release_resource(dev, SYS_RES_MEMORY, 0, adapter->ec_res);
	bus_release_resource(dev, SYS_RES_MEMORY, 0, adapter->mac_res);
	bus_release_resource(dev, SYS_RES_MEMORY, 0, adapter->udma_res);

	return (0);
}
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
struct nuport_mac_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 unsigned int DMA_CHAN_WIDTH ; 
 scalar_t__ RX_DMA_BASE ; 
 scalar_t__ TX_DMA_BASE ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,...) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  nuport_mac_init_tx_ring (struct nuport_mac_priv*) ; 
 int /*<<< orphan*/  nuport_mac_readl (scalar_t__) ; 
 int /*<<< orphan*/  nuport_mac_reset_tx_dma (struct nuport_mac_priv*) ; 

__attribute__((used)) static void nuport_mac_tx_timeout(struct net_device *dev)
{
	struct nuport_mac_priv *priv = netdev_priv(dev);
	unsigned int i;

	netdev_warn(dev, "transmit timeout, attempting recovery\n");

	netdev_info(dev, "TX DMA regs\n");
	for (i = 0; i < DMA_CHAN_WIDTH; i += 4)
		netdev_info(dev, "[%02x]: 0x%08x\n", i, nuport_mac_readl(TX_DMA_BASE + i));
	netdev_info(dev, "RX DMA regs\n");
	for (i = 0; i < DMA_CHAN_WIDTH; i += 4)
		netdev_info(dev, "[%02x]: 0x%08x\n", i, nuport_mac_readl(RX_DMA_BASE + i));

	nuport_mac_init_tx_ring(priv);
	nuport_mac_reset_tx_dma(priv);

	netif_wake_queue(dev);
}
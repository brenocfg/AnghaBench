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
typedef  int u32 ;
struct nuport_mac_priv {int /*<<< orphan*/  emac_clk; int /*<<< orphan*/  lock; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  phydev; int /*<<< orphan*/  link_irq; int /*<<< orphan*/  napi; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_REG ; 
 int /*<<< orphan*/  LINK_INT_CSR ; 
 int /*<<< orphan*/  LINK_INT_POLL_TIME ; 
 int RX_ENABLE ; 
 int TX_ENABLE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  nuport_mac_free_rx_ring (struct nuport_mac_priv*) ; 
 int nuport_mac_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuport_mac_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_stop (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nuport_mac_close(struct net_device *dev)
{
	u32 reg;
	struct nuport_mac_priv *priv = netdev_priv(dev);

	spin_lock_irq(&priv->lock);
	reg = nuport_mac_readl(CTRL_REG);
	reg &= ~(RX_ENABLE | TX_ENABLE);
	nuport_mac_writel(reg, CTRL_REG);

	napi_disable(&priv->napi);
	netif_stop_queue(dev);

	free_irq(priv->link_irq, dev);
	/* disable PHY polling */
	nuport_mac_writel(0, LINK_INT_CSR);
	nuport_mac_writel(0, LINK_INT_POLL_TIME);
	phy_stop(priv->phydev);

	free_irq(priv->tx_irq, dev);
	free_irq(priv->rx_irq, dev);
	spin_unlock_irq(&priv->lock);

	nuport_mac_free_rx_ring(priv);

	clk_disable(priv->emac_clk);

	return 0;
}
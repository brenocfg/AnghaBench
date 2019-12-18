#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct nuport_mac_priv {int /*<<< orphan*/  emac_clk; int /*<<< orphan*/  link_irq; int /*<<< orphan*/  tx_irq; int /*<<< orphan*/  rx_irq; int /*<<< orphan*/  napi; int /*<<< orphan*/  lock; int /*<<< orphan*/ * rx_skb; TYPE_1__* phydev; } ;
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct TYPE_2__ {int addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_REG ; 
 int DEFER_CHECK ; 
 int DRTRY_DISABLE ; 
 int FULL_DUPLEX ; 
 int HBD_DISABLE ; 
 int LINK_BIT_UP_SHIFT ; 
 int /*<<< orphan*/  LINK_INT_CSR ; 
 int LINK_INT_EN ; 
 int /*<<< orphan*/  LINK_INT_POLL_TIME ; 
 int LINK_PHY_ADDR_SHIFT ; 
 int LINK_PHY_REG_SHIFT ; 
 int LINK_POLL_MASK ; 
 int RX_ENABLE ; 
 int STRIP_PAD ; 
 int TX_ENABLE ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  napi_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  nuport_mac_change_mac_address (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuport_mac_free_rx_ring (struct nuport_mac_priv*) ; 
 int nuport_mac_init_rx_ring (struct net_device*) ; 
 int /*<<< orphan*/  nuport_mac_init_tx_ring (struct nuport_mac_priv*) ; 
 int /*<<< orphan*/  nuport_mac_link_interrupt ; 
 int /*<<< orphan*/  nuport_mac_reset_rx_dma (struct nuport_mac_priv*) ; 
 int /*<<< orphan*/  nuport_mac_reset_tx_dma (struct nuport_mac_priv*) ; 
 int /*<<< orphan*/  nuport_mac_rx_interrupt ; 
 int nuport_mac_start_rx_dma (struct nuport_mac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nuport_mac_tx_interrupt ; 
 int /*<<< orphan*/  nuport_mac_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_start (TYPE_1__*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nuport_mac_open(struct net_device *dev)
{
	int ret;
	struct nuport_mac_priv *priv = netdev_priv(dev);
	unsigned long flags;
	u32 reg = 0;

	ret = clk_enable(priv->emac_clk);
	if (ret) {
		netdev_err(dev, "failed to enable EMAC clock\n");
		return ret;
	}

	/* Set MAC into full duplex mode by default */
	reg |= RX_ENABLE | TX_ENABLE;
	reg |= DEFER_CHECK | STRIP_PAD | DRTRY_DISABLE;
	reg |= FULL_DUPLEX | HBD_DISABLE;
	nuport_mac_writel(reg, CTRL_REG);

	/* set mac address in hardware in case it was not already */
	nuport_mac_change_mac_address(dev, dev->dev_addr);

	ret = request_irq(priv->link_irq, &nuport_mac_link_interrupt,
				0, dev->name, dev);
	if (ret) {
		netdev_err(dev, "unable to request link interrupt\n");
		goto out_emac_clk;
	}

	ret = request_irq(priv->tx_irq, &nuport_mac_tx_interrupt,
				0, dev->name, dev);
	if (ret) {
		netdev_err(dev, "unable to request rx interrupt\n");
		goto out_link_irq;
	}

	/* Enable link interrupt monitoring for our PHY address */
	reg = LINK_INT_EN | (priv->phydev->addr << LINK_PHY_ADDR_SHIFT);
	/* MII_BMSR register to be watched */
	reg |= (1 << LINK_PHY_REG_SHIFT);
	/* BMSR_STATUS to be watched in particular */
	reg |= (2 << LINK_BIT_UP_SHIFT);

	spin_lock_irqsave(&priv->lock, flags);
	nuport_mac_writel(reg, LINK_INT_CSR);
	nuport_mac_writel(LINK_POLL_MASK, LINK_INT_POLL_TIME);
	spin_unlock_irqrestore(&priv->lock, flags);

	phy_start(priv->phydev);

	ret = request_irq(priv->rx_irq, &nuport_mac_rx_interrupt,
				0, dev->name, dev);
	if (ret) {
		netdev_err(dev, "unable to request tx interrupt\n");
		goto out_tx_irq;
	}

	netif_start_queue(dev);

	nuport_mac_init_tx_ring(priv);

	ret = nuport_mac_init_rx_ring(dev);
	if (ret) {
		netdev_err(dev, "rx ring init failed\n");
		goto out_rx_skb;
	}

	nuport_mac_reset_tx_dma(priv);
	nuport_mac_reset_rx_dma(priv);

	/* Start RX DMA */
	spin_lock_irqsave(&priv->lock, flags);
	ret = nuport_mac_start_rx_dma(priv, priv->rx_skb[0]);
	spin_unlock_irqrestore(&priv->lock, flags);

	napi_enable(&priv->napi);

	return ret;

out_rx_skb:
	nuport_mac_free_rx_ring(priv);
	free_irq(priv->rx_irq, dev);
out_tx_irq:
	free_irq(priv->tx_irq, dev);
out_link_irq:
	free_irq(priv->link_irq, dev);
out_emac_clk:
	clk_disable(priv->emac_clk);
	return ret;
}
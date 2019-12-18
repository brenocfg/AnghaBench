#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct nuport_mac_priv {size_t dma_tx; int first_pkt; int /*<<< orphan*/  lock; scalar_t__ tx_full; struct sk_buff** tx_skb; scalar_t__* valid_txskb; int /*<<< orphan*/  rx_addr; TYPE_2__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  tx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  TX_DMA_STATUS ; 
 int TX_DMA_STATUS_AVAIL ; 
 size_t TX_RING_SIZE ; 
 int /*<<< orphan*/  TX_START_DMA ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int nuport_mac_readl (int /*<<< orphan*/ ) ; 
 int nuport_mac_start_tx_dma (struct nuport_mac_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  nuport_mac_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t nuport_mac_tx_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct nuport_mac_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;
	unsigned long flags;
	int ret;
	u32 reg;

	spin_lock_irqsave(&priv->lock, flags);
	/* clear status word available if ready */
	reg = nuport_mac_readl(TX_START_DMA);
	if (reg & TX_DMA_STATUS_AVAIL) {
		nuport_mac_writel(reg, TX_START_DMA);
		reg = nuport_mac_readl(TX_DMA_STATUS);

		if (reg & 1)
			dev->stats.tx_errors++;
	} else
		netdev_dbg(dev, "no status word: %08x\n", reg);

	skb = priv->tx_skb[priv->dma_tx];
	priv->tx_skb[priv->dma_tx] = NULL;
	priv->valid_txskb[priv->dma_tx] = 0;
	dma_unmap_single(&priv->pdev->dev, priv->rx_addr, skb->len,
				DMA_TO_DEVICE);
	dev_kfree_skb_irq(skb);

	priv->dma_tx++;
	if (priv->dma_tx >= TX_RING_SIZE)
		priv->dma_tx = 0;

	if (!priv->valid_txskb[priv->dma_tx])
		priv->first_pkt = 1;
	else {
		ret = nuport_mac_start_tx_dma(priv, priv->tx_skb[priv->dma_tx]);
		if (ret)
			netdev_err(dev, "failed to restart TX dma\n");
	}

	if (priv->tx_full) {
		netdev_dbg(dev, "restarting transmit queue\n");
		netif_wake_queue(dev);
		priv->tx_full = 0;
	}

	spin_unlock_irqrestore(&priv->lock, flags);

	return IRQ_HANDLED;
}
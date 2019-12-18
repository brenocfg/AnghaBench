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
struct nuport_mac_priv {int rx_full; size_t dma_rx; int* irq_rxskb; int /*<<< orphan*/  lock; int /*<<< orphan*/  napi; int /*<<< orphan*/ * rx_skb; scalar_t__* pkt_len; } ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RX_ACT_BYTES ; 
 size_t RX_RING_SIZE ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  nuport_mac_disable_rx_dma (struct nuport_mac_priv*) ; 
 int /*<<< orphan*/  nuport_mac_has_work (struct nuport_mac_priv*) ; 
 scalar_t__ nuport_mac_readl (int /*<<< orphan*/ ) ; 
 int nuport_mac_start_rx_dma (struct nuport_mac_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static irqreturn_t nuport_mac_rx_interrupt(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *)dev_id;
	struct nuport_mac_priv *priv = netdev_priv(dev);
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&priv->lock, flags);
	if (!priv->rx_full) {
		priv->pkt_len[priv->dma_rx] = nuport_mac_readl(RX_ACT_BYTES) - 4;
		priv->irq_rxskb[priv->dma_rx] = 0;
		priv->dma_rx++;

		if (priv->dma_rx >= RX_RING_SIZE)
			priv->dma_rx = 0;
	} else
		priv->rx_full = 0;

	if (priv->irq_rxskb[priv->dma_rx] == 1) {
		ret = nuport_mac_start_rx_dma(priv, priv->rx_skb[priv->dma_rx]);
		if (ret)
			netdev_err(dev, "failed to start rx dma\n");
	} else {
		priv->rx_full = 1;
		netdev_dbg(dev, "RX ring full\n");
	}

	if (likely(nuport_mac_has_work(priv))) {
		/* find a way to disable DMA rx irq */
		nuport_mac_disable_rx_dma(priv);
		napi_schedule(&priv->napi);
	}
	spin_unlock_irqrestore(&priv->lock, flags);

	return IRQ_HANDLED;
}
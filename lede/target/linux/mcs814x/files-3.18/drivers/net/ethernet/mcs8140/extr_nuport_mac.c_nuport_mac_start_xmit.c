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
struct sk_buff {scalar_t__ len; } ;
struct nuport_mac_priv {size_t cur_tx; int* valid_txskb; int tx_full; int /*<<< orphan*/  lock; struct sk_buff** tx_skb; scalar_t__ first_pkt; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct net_device {int /*<<< orphan*/  trans_start; TYPE_1__ stats; } ;

/* Variables and functions */
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 size_t TX_RING_SIZE ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int nuport_mac_start_tx_dma (struct nuport_mac_priv*,struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nuport_mac_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	unsigned long flags;
	struct nuport_mac_priv *priv = netdev_priv(dev);
	int ret;

	if (netif_queue_stopped(dev)) {
		netdev_warn(dev, "netif queue was stopped, restarting\n");
		netif_start_queue(dev);
	}

	spin_lock_irqsave(&priv->lock, flags);
	if (priv->first_pkt) {
		ret = nuport_mac_start_tx_dma(priv, skb);
		if (ret) {
			netif_stop_queue(dev);
			spin_unlock_irqrestore(&priv->lock, flags);
			netdev_err(dev, "transmit path busy\n");
			return NETDEV_TX_BUSY;
		}
		priv->first_pkt = 0;
	}

	priv->tx_skb[priv->cur_tx] = skb;
	dev->stats.tx_bytes += skb->len;
	dev->stats.tx_packets++;
	priv->valid_txskb[priv->cur_tx] = 1;
	priv->cur_tx++;
	dev->trans_start = jiffies;

	if (priv->cur_tx >= TX_RING_SIZE)
		priv->cur_tx = 0;

	spin_unlock_irqrestore(&priv->lock, flags);

	if (priv->valid_txskb[priv->cur_tx]) {
		priv->tx_full = 1;
		netdev_err(dev, "stopping queue\n");
		netif_stop_queue(dev);
	}

	return NETDEV_TX_OK;
}
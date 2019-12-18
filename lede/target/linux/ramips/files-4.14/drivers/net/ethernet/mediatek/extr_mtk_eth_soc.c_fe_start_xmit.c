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
struct sk_buff {int len; } ;
struct net_device_stats {int tx_bytes; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_dropped; } ;
struct net_device {struct net_device_stats stats; } ;
struct fe_tx_ring {int dummy; } ;
struct fe_priv {struct fe_tx_ring tx_ring; } ;

/* Variables and functions */
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 int fe_cal_txd_req (struct sk_buff*) ; 
 int fe_empty_txd (struct fe_tx_ring*) ; 
 scalar_t__ fe_skb_padto (struct sk_buff*,struct fe_priv*) ; 
 scalar_t__ fe_tx_map_dma (struct sk_buff*,struct net_device*,int,struct fe_tx_ring*) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct fe_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_warn (struct fe_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  tx_err ; 
 int /*<<< orphan*/  tx_queued ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int fe_start_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct fe_priv *priv = netdev_priv(dev);
	struct fe_tx_ring *ring = &priv->tx_ring;
	struct net_device_stats *stats = &dev->stats;
	int tx_num;
	int len = skb->len;

	if (fe_skb_padto(skb, priv)) {
		netif_warn(priv, tx_err, dev, "tx padding failed!\n");
		return NETDEV_TX_OK;
	}

	tx_num = fe_cal_txd_req(skb);
	if (unlikely(fe_empty_txd(ring) <= tx_num)) {
		netif_stop_queue(dev);
		netif_err(priv, tx_queued, dev,
			  "Tx Ring full when queue awake!\n");
		return NETDEV_TX_BUSY;
	}

	if (fe_tx_map_dma(skb, dev, tx_num, ring) < 0) {
		stats->tx_dropped++;
	} else {
		stats->tx_packets++;
		stats->tx_bytes += len;
	}

	return NETDEV_TX_OK;
}
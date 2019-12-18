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
struct sk_buff {int dummy; } ;
struct nuport_mac_priv {int* irq_rxskb; struct sk_buff** rx_skb; scalar_t__ rx_full; scalar_t__ dma_rx; scalar_t__ cur_rx; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  RX_ALLOC_SIZE ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  RX_SKB_HEADROOM ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nuport_mac_init_rx_ring(struct net_device *dev)
{
	struct nuport_mac_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;
	int i;

	priv->cur_rx = priv->dma_rx = priv->rx_full = 0;

	for (i = 0; i < RX_RING_SIZE; i++) {
		skb = netdev_alloc_skb(dev, RX_ALLOC_SIZE);
		if (!skb)
			return -ENOMEM;
		skb_reserve(skb, RX_SKB_HEADROOM);
		priv->rx_skb[i] = skb;
		priv->irq_rxskb[i] = 1;
	}

	return 0;
}
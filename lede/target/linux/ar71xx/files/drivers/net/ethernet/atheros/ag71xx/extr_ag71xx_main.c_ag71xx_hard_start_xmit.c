#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int len; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_dropped; } ;
struct net_device {TYPE_3__ stats; int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct ag71xx_ring {int curr; int dirty; scalar_t__ desc_split; TYPE_1__* buf; int /*<<< orphan*/  order; } ;
struct ag71xx_desc {int /*<<< orphan*/  ctrl; } ;
struct ag71xx {int desc_pktlen_mask; TYPE_2__* dev; struct ag71xx_ring tx_ring; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int len; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_TX_CTRL ; 
 int AG71XX_TX_RING_DS_PER_PKT ; 
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DESC_EMPTY ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  TX_CTRL_TXE ; 
 int /*<<< orphan*/  ag71xx_add_ar8216_header (struct ag71xx*,struct sk_buff*) ; 
 int ag71xx_fill_dma_desc (struct ag71xx_ring*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ag71xx_has_ar8216 (struct ag71xx*) ; 
 struct ag71xx_desc* ag71xx_ring_desc (struct ag71xx_ring*,int) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 scalar_t__ dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sent_queue (struct net_device*,int) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static netdev_tx_t ag71xx_hard_start_xmit(struct sk_buff *skb,
					  struct net_device *dev)
{
	struct ag71xx *ag = netdev_priv(dev);
	struct ag71xx_ring *ring = &ag->tx_ring;
	int ring_mask = BIT(ring->order) - 1;
	int ring_size = BIT(ring->order);
	struct ag71xx_desc *desc;
	dma_addr_t dma_addr;
	int i, n, ring_min;

	if (ag71xx_has_ar8216(ag))
		ag71xx_add_ar8216_header(ag, skb);

	if (skb->len <= 4) {
		DBG("%s: packet len is too small\n", ag->dev->name);
		goto err_drop;
	}

	dma_addr = dma_map_single(&dev->dev, skb->data, skb->len,
				  DMA_TO_DEVICE);

	i = ring->curr & ring_mask;
	desc = ag71xx_ring_desc(ring, i);

	/* setup descriptor fields */
	n = ag71xx_fill_dma_desc(ring, (u32) dma_addr, skb->len & ag->desc_pktlen_mask);
	if (n < 0)
		goto err_drop_unmap;

	i = (ring->curr + n - 1) & ring_mask;
	ring->buf[i].len = skb->len;
	ring->buf[i].skb = skb;

	netdev_sent_queue(dev, skb->len);

	skb_tx_timestamp(skb);

	desc->ctrl &= ~DESC_EMPTY;
	ring->curr += n;

	/* flush descriptor */
	wmb();

	ring_min = 2;
	if (ring->desc_split)
	    ring_min *= AG71XX_TX_RING_DS_PER_PKT;

	if (ring->curr - ring->dirty >= ring_size - ring_min) {
		DBG("%s: tx queue full\n", dev->name);
		netif_stop_queue(dev);
	}

	DBG("%s: packet injected into TX queue\n", ag->dev->name);

	/* enable TX engine */
	ag71xx_wr(ag, AG71XX_REG_TX_CTRL, TX_CTRL_TXE);

	return NETDEV_TX_OK;

err_drop_unmap:
	dma_unmap_single(&dev->dev, dma_addr, skb->len, DMA_TO_DEVICE);

err_drop:
	dev->stats.tx_dropped++;

	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}
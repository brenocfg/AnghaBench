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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  pkt_type; int /*<<< orphan*/  protocol; int /*<<< orphan*/  len; scalar_t__ data; } ;
struct nuport_mac_priv {int* irq_rxskb; size_t cur_rx; int* pkt_len; int buffer_shifting_len; struct sk_buff** rx_skb; int /*<<< orphan*/  rx_addr; TYPE_1__* pdev; } ;
struct TYPE_4__ {int rx_bytes; int /*<<< orphan*/  rx_dropped; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_errors; int /*<<< orphan*/  rx_missed_errors; } ;
struct net_device {int /*<<< orphan*/  last_rx; TYPE_2__ stats; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ERROR_FILTER_MASK ; 
 int MAX_ETH_FRAME_SIZE ; 
 int NET_RX_DROP ; 
 int /*<<< orphan*/  PACKET_BROADCAST ; 
 int /*<<< orphan*/  PACKET_MULTICAST ; 
 int /*<<< orphan*/  PACKET_OTHERHOST ; 
 int /*<<< orphan*/  RX_ALLOC_SIZE ; 
 size_t RX_RING_SIZE ; 
 int /*<<< orphan*/  RX_SKB_HEADROOM ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int get_unaligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 struct sk_buff* netdev_alloc_skb (struct net_device*,int /*<<< orphan*/ ) ; 
 struct nuport_mac_priv* netdev_priv (struct net_device*) ; 
 int netif_receive_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nuport_mac_rx(struct net_device *dev, int limit)
{
	struct nuport_mac_priv *priv = netdev_priv(dev);
	struct sk_buff *skb;
	int len, status;
	int count = 0;

	while (count < limit && !priv->irq_rxskb[priv->cur_rx]) {
		skb = priv->rx_skb[priv->cur_rx];
		len = priv->pkt_len[priv->cur_rx];

		/* Remove 2 bytes added by RX buffer shifting */
		len = len - priv->buffer_shifting_len;
		skb->data = skb->data + priv->buffer_shifting_len;

		/* Get packet status */
		status = get_unaligned((u32 *) (skb->data + len));

		dma_unmap_single(&priv->pdev->dev, priv->rx_addr, skb->len,
				DMA_FROM_DEVICE);

		/* packet filter failed */
		if (!(status & (1 << 30))) {
			dev_kfree_skb_irq(skb);
			goto exit;
		}

		/* missed frame */
		if (status & (1 << 31)) {
			dev->stats.rx_missed_errors++;
			dev_kfree_skb_irq(skb);
			goto exit;
		}

		/* Not ethernet type */
		if ((!(status & (1 << 18))) || (status & ERROR_FILTER_MASK))
			dev->stats.rx_errors++;

		if (len > MAX_ETH_FRAME_SIZE) {
			dev_kfree_skb_irq(skb);
			goto exit;
		} else
			skb_put(skb, len);

		skb->protocol = eth_type_trans(skb, dev);
		dev->stats.rx_packets++;

		if (status & (1 << 29))
			skb->pkt_type = PACKET_OTHERHOST;
		if (status & (1 << 27))
			skb->pkt_type = PACKET_MULTICAST;
		if (status & (1 << 28))
			skb->pkt_type = PACKET_BROADCAST;

		skb->ip_summed = CHECKSUM_UNNECESSARY;

		/* Pass the received packet to network layer */
		status = netif_receive_skb(skb);
		if (status != NET_RX_DROP)
			dev->stats.rx_bytes += len - 4;	/* Without CRC */
		else
			dev->stats.rx_dropped++;

		dev->last_rx = jiffies;

exit:
		skb = netdev_alloc_skb(dev, RX_ALLOC_SIZE);
		if (!skb)
			goto out;

		skb_reserve(skb, RX_SKB_HEADROOM);
		priv->rx_skb[priv->cur_rx] = skb;
		priv->irq_rxskb[priv->cur_rx] = 1;
		priv->cur_rx++;

		if (priv->cur_rx >= RX_RING_SIZE)
			priv->cur_rx = 0;
		count++;
	}
out:
	return count;
}
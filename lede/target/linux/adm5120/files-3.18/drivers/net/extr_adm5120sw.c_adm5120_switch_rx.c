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
struct sk_buff {int /*<<< orphan*/  len; scalar_t__ data; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  protocol; struct net_device* dev; } ;
struct TYPE_2__ {int rx_bytes; int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; int /*<<< orphan*/  last_rx; } ;
struct dma_desc {int buf1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int DESC_OWN ; 
 scalar_t__ ETH_CSUM_LEN ; 
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  SW_DBG (char*,int,...) ; 
 struct net_device** adm5120_port ; 
 int /*<<< orphan*/  adm5120_switch_rx_refill () ; 
 int cur_rxl ; 
 int desc_get_pktlen (struct dma_desc*) ; 
 unsigned int desc_get_srcport (struct dma_desc*) ; 
 scalar_t__ desc_ipcsum_fail (struct dma_desc*) ; 
 int dirty_rxl ; 
 int /*<<< orphan*/  dma_cache_wback_inv (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,struct net_device*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 struct dma_desc* rxl_descs ; 
 struct sk_buff** rxl_skbuff ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static int adm5120_switch_rx(int limit)
{
	unsigned int done = 0;

	SW_DBG("rx start, limit=%d, cur_rxl=%u, dirty_rxl=%u\n",
				limit, cur_rxl, dirty_rxl);

	while (done < limit) {
		int entry = cur_rxl % RX_RING_SIZE;
		struct dma_desc *desc = &rxl_descs[entry];
		struct net_device *rdev;
		unsigned int port;

		if (desc->buf1 & DESC_OWN)
			break;

		if (dirty_rxl + RX_RING_SIZE == cur_rxl)
			break;

		port = desc_get_srcport(desc);
		rdev = adm5120_port[port];

		SW_DBG("rx descriptor %u, desc=%p, skb=%p\n", entry, desc,
				rxl_skbuff[entry]);

		if ((rdev) && netif_running(rdev)) {
			struct sk_buff *skb = rxl_skbuff[entry];
			int pktlen;

			pktlen = desc_get_pktlen(desc);
			pktlen -= ETH_CSUM_LEN;

			if ((pktlen == 0) || desc_ipcsum_fail(desc)) {
				rdev->stats.rx_errors++;
				if (pktlen == 0)
					rdev->stats.rx_length_errors++;
				if (desc_ipcsum_fail(desc))
					rdev->stats.rx_crc_errors++;
				SW_DBG("rx error, recycling skb %u\n", entry);
			} else {
				skb_put(skb, pktlen);

				skb->dev = rdev;
				skb->protocol = eth_type_trans(skb, rdev);
				skb->ip_summed = CHECKSUM_UNNECESSARY;

				dma_cache_wback_inv((unsigned long)skb->data,
					skb->len);

#ifdef CONFIG_ADM5120_SWITCH_NAPI
				netif_receive_skb(skb);
#else
				netif_rx(skb);
#endif

				rdev->last_rx = jiffies;
				rdev->stats.rx_packets++;
				rdev->stats.rx_bytes += pktlen;

				rxl_skbuff[entry] = NULL;
				done++;
			}
		} else {
			SW_DBG("no rx device, recycling skb %u\n", entry);
		}

		cur_rxl++;
		if (cur_rxl - dirty_rxl > RX_RING_SIZE / 4)
			adm5120_switch_rx_refill();
	}

	adm5120_switch_rx_refill();

	SW_DBG("rx finished, cur_rxl=%u, dirty_rxl=%u, processed %d\n",
				cur_rxl, dirty_rxl, done);

	return done;
}
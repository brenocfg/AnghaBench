#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct skb_frag_struct {int /*<<< orphan*/  page_offset; } ;
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  xmit_more; int /*<<< orphan*/  len; } ;
struct net_device {int /*<<< orphan*/  dev; } ;
struct fe_tx_ring {size_t tx_next_idx; scalar_t__ tx_thresh; TYPE_2__* tx_dma; struct fe_tx_buf* tx_buf; } ;
struct fe_tx_buf {struct sk_buff* skb; } ;
struct fe_priv {TYPE_1__* soc; } ;
struct TYPE_9__ {int txd4; int /*<<< orphan*/  txd2; } ;
struct fe_map_state {size_t ring_idx; int def_txd4; int i; TYPE_4__ txd; int /*<<< orphan*/ * dev; } ;
struct TYPE_10__ {int gso_type; unsigned int nr_frags; struct skb_frag_struct* frags; int /*<<< orphan*/  gso_size; } ;
struct TYPE_8__ {int /*<<< orphan*/  check; } ;
struct TYPE_7__ {int /*<<< orphan*/  txd2; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* tx_dma ) (TYPE_4__*) ;} ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  CONFIG_SOC_MT7621 ; 
 int /*<<< orphan*/  FE_REG_TX_CTX_IDX0 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int NEXT_TX_DESP_IDX (int) ; 
 int SKB_GSO_TCPV4 ; 
 int SKB_GSO_TCPV6 ; 
 int TX_DMA_CHKSUM ; 
 int /*<<< orphan*/  TX_DMA_DESP2_DEF ; 
 int TX_DMA_DESP4_DEF ; 
 int TX_DMA_INS_VLAN ; 
 int TX_DMA_INS_VLAN_MT7621 ; 
 int /*<<< orphan*/  TX_DMA_LS0 ; 
 int /*<<< orphan*/  TX_DMA_LS1 ; 
 int TX_DMA_TSO ; 
 int VLAN_PRIO_SHIFT ; 
 scalar_t__ fe_empty_txd (struct fe_tx_ring*) ; 
 struct sk_buff* fe_next_frag (struct sk_buff*,struct sk_buff*) ; 
 int /*<<< orphan*/  fe_reg_w32 (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ fe_tx_dma_map_page (struct fe_tx_ring*,struct fe_map_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ fe_tx_dma_map_skb (struct fe_tx_ring*,struct fe_map_state*,struct sk_buff*) ; 
 int /*<<< orphan*/  fe_tx_dma_write_desc (struct fe_tx_ring*,struct fe_map_state*) ; 
 int /*<<< orphan*/  fe_txd_unmap (int /*<<< orphan*/ *,struct fe_tx_buf*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_get_tx_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_sent_queue (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_warn (struct fe_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 scalar_t__ netif_xmit_stopped (int /*<<< orphan*/ ) ; 
 scalar_t__ skb_cow_head (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_page (struct skb_frag_struct*) ; 
 int /*<<< orphan*/  skb_frag_size (struct skb_frag_struct*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 TYPE_5__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tx_timestamp (struct sk_buff*) ; 
 int skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*) ; 
 TYPE_3__* tcp_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  tx_err ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int fe_tx_map_dma(struct sk_buff *skb, struct net_device *dev,
			 int tx_num, struct fe_tx_ring *ring)
{
	struct fe_priv *priv = netdev_priv(dev);
	struct fe_map_state st = {
		.dev = &dev->dev,
		.ring_idx = ring->tx_next_idx,
	};
	struct sk_buff *head = skb;
	struct fe_tx_buf *tx_buf;
	unsigned int nr_frags;
	int i, j;

	/* init tx descriptor */
	if (priv->soc->tx_dma)
		priv->soc->tx_dma(&st.txd);
	else
		st.txd.txd4 = TX_DMA_DESP4_DEF;
	st.def_txd4 = st.txd.txd4;

	/* TX Checksum offload */
	if (skb->ip_summed == CHECKSUM_PARTIAL)
		st.txd.txd4 |= TX_DMA_CHKSUM;

	/* VLAN header offload */
	if (skb_vlan_tag_present(skb)) {
		u16 tag = skb_vlan_tag_get(skb);

		if (IS_ENABLED(CONFIG_SOC_MT7621))
			st.txd.txd4 |= TX_DMA_INS_VLAN_MT7621 | tag;
		else
			st.txd.txd4 |= TX_DMA_INS_VLAN |
				((tag >> VLAN_PRIO_SHIFT) << 4) |
				(tag & 0xF);
	}

	/* TSO: fill MSS info in tcp checksum field */
	if (skb_is_gso(skb)) {
		if (skb_cow_head(skb, 0)) {
			netif_warn(priv, tx_err, dev,
				   "GSO expand head fail.\n");
			goto err_out;
		}
		if (skb_shinfo(skb)->gso_type &
				(SKB_GSO_TCPV4 | SKB_GSO_TCPV6)) {
			st.txd.txd4 |= TX_DMA_TSO;
			tcp_hdr(skb)->check = htons(skb_shinfo(skb)->gso_size);
		}
	}

next_frag:
	if (skb_headlen(skb) && fe_tx_dma_map_skb(ring, &st, skb))
		goto err_dma;

	/* TX SG offload */
	nr_frags = skb_shinfo(skb)->nr_frags;
	for (i = 0; i < nr_frags; i++) {
		struct skb_frag_struct *frag;

		frag = &skb_shinfo(skb)->frags[i];
		if (fe_tx_dma_map_page(ring, &st, skb_frag_page(frag),
				       frag->page_offset, skb_frag_size(frag)))
			goto err_dma;
	}

	skb = fe_next_frag(head, skb);
	if (skb)
		goto next_frag;

	/* set last segment */
	if (st.i & 0x1)
		st.txd.txd2 |= TX_DMA_LS0;
	else
		st.txd.txd2 |= TX_DMA_LS1;

	/* store skb to cleanup */
	tx_buf = &ring->tx_buf[st.ring_idx];
	tx_buf->skb = head;

	netdev_sent_queue(dev, head->len);
	skb_tx_timestamp(head);

	fe_tx_dma_write_desc(ring, &st);
	ring->tx_next_idx = st.ring_idx;

	/* make sure that all changes to the dma ring are flushed before we
	 * continue
	 */
	wmb();
	if (unlikely(fe_empty_txd(ring) <= ring->tx_thresh)) {
		netif_stop_queue(dev);
		smp_mb();
		if (unlikely(fe_empty_txd(ring) > ring->tx_thresh))
			netif_wake_queue(dev);
	}

	if (netif_xmit_stopped(netdev_get_tx_queue(dev, 0)) || !head->xmit_more)
		fe_reg_w32(ring->tx_next_idx, FE_REG_TX_CTX_IDX0);

	return 0;

err_dma:
	j = ring->tx_next_idx;
	for (i = 0; i < tx_num; i++) {
		/* unmap dma */
		fe_txd_unmap(&dev->dev, &ring->tx_buf[j]);
		ring->tx_dma[j].txd2 = TX_DMA_DESP2_DEF;

		j = NEXT_TX_DESP_IDX(j);
	}
	/* make sure that all changes to the dma ring are flushed before we
	 * continue
	 */
	wmb();

err_out:
	return -1;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_10__ {scalar_t__ offload_handle; } ;
struct xfrm_state {TYPE_1__ xso; } ;
struct ulptx_sgl {int dummy; } ;
struct sk_buff {int queue_mapping; } ;
struct TYPE_13__ {size_t pidx; int size; TYPE_3__* sdesc; int /*<<< orphan*/ * desc; scalar_t__ stat; } ;
struct sge_eth_txq {TYPE_4__ q; int /*<<< orphan*/  mapping_err; } ;
struct sec_path {int len; } ;
struct port_info {int first_qset; struct adapter* adapter; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct ipsec_sa_entry {int dummy; } ;
struct TYPE_11__ {struct sge_eth_txq* ethtxq; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_2__ sge; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_12__ {struct ulptx_sgl* sgl; struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_SKB_FRAGS ; 
 int NETDEV_TX_BUSY ; 
 int NETDEV_TX_OK ; 
 unsigned int calc_tx_sec_flits (struct sk_buff*,struct ipsec_sa_entry*,int*) ; 
 scalar_t__ chcr_crypto_wreq (struct sk_buff*,struct net_device*,void*,int,struct ipsec_sa_entry*) ; 
 int /*<<< orphan*/  cxgb4_inline_tx_skb (struct sk_buff*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 scalar_t__ cxgb4_map_skb (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cxgb4_reclaim_completed_tx (struct adapter*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  cxgb4_ring_tx_db (struct adapter*,TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  cxgb4_write_sgl (struct sk_buff*,TYPE_4__*,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_consume_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_txq_stop (struct sge_eth_txq*) ; 
 unsigned int flits_to_desc (unsigned int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 struct sec_path* skb_sec_path (struct sk_buff*) ; 
 int /*<<< orphan*/  txq_advance (TYPE_4__*,unsigned int) ; 
 unsigned int txq_avail (TYPE_4__*) ; 
 scalar_t__ unlikely (int) ; 
 struct xfrm_state* xfrm_input_state (struct sk_buff*) ; 

int chcr_ipsec_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct xfrm_state *x = xfrm_input_state(skb);
	struct ipsec_sa_entry *sa_entry;
	u64 *pos, *end, *before, *sgl;
	int qidx, left, credits;
	unsigned int flits = 0, ndesc;
	struct adapter *adap;
	struct sge_eth_txq *q;
	struct port_info *pi;
	dma_addr_t addr[MAX_SKB_FRAGS + 1];
	struct sec_path *sp;
	bool immediate = false;

	if (!x->xso.offload_handle)
		return NETDEV_TX_BUSY;

	sa_entry = (struct ipsec_sa_entry *)x->xso.offload_handle;

	sp = skb_sec_path(skb);
	if (sp->len != 1) {
out_free:       dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	pi = netdev_priv(dev);
	adap = pi->adapter;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->first_qset];

	cxgb4_reclaim_completed_tx(adap, &q->q, true);

	flits = calc_tx_sec_flits(skb, sa_entry, &immediate);
	ndesc = flits_to_desc(flits);
	credits = txq_avail(&q->q) - ndesc;

	if (unlikely(credits < 0)) {
		eth_txq_stop(q);
		dev_err(adap->pdev_dev,
			"%s: Tx ring %u full while queue awake! cred:%d %d %d flits:%d\n",
			dev->name, qidx, credits, ndesc, txq_avail(&q->q),
			flits);
		return NETDEV_TX_BUSY;
	}

	if (!immediate &&
	    unlikely(cxgb4_map_skb(adap->pdev_dev, skb, addr) < 0)) {
		q->mapping_err++;
		goto out_free;
	}

	pos = (u64 *)&q->q.desc[q->q.pidx];
	before = (u64 *)pos;
	end = (u64 *)pos + flits;
	/* Setup IPSec CPL */
	pos = (void *)chcr_crypto_wreq(skb, dev, (void *)pos,
				       credits, sa_entry);
	if (before > (u64 *)pos) {
		left = (u8 *)end - (u8 *)q->q.stat;
		end = (void *)q->q.desc + left;
	}
	if (pos == (u64 *)q->q.stat) {
		left = (u8 *)end - (u8 *)q->q.stat;
		end = (void *)q->q.desc + left;
		pos = (void *)q->q.desc;
	}

	sgl = (void *)pos;
	if (immediate) {
		cxgb4_inline_tx_skb(skb, &q->q, sgl);
		dev_consume_skb_any(skb);
	} else {
		int last_desc;

		cxgb4_write_sgl(skb, &q->q, (void *)sgl, end,
				0, addr);
		skb_orphan(skb);

		last_desc = q->q.pidx + ndesc - 1;
		if (last_desc >= q->q.size)
			last_desc -= q->q.size;
		q->q.sdesc[last_desc].skb = skb;
		q->q.sdesc[last_desc].sgl = (struct ulptx_sgl *)sgl;
	}
	txq_advance(&q->q, ndesc);

	cxgb4_ring_tx_db(adap, &q->q, ndesc);
	return NETDEV_TX_OK;
}
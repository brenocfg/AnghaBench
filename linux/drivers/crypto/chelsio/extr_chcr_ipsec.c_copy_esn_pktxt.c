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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  size_t u32 ;
struct TYPE_6__ {scalar_t__ hi; } ;
struct xfrm_offload {TYPE_3__ seq; } ;
struct ulptx_idata {int /*<<< orphan*/  len; int /*<<< orphan*/  cmd_more; } ;
struct sk_buff {size_t queue_mapping; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {void* desc; scalar_t__ stat; } ;
struct sge_eth_txq {TYPE_2__ q; } ;
struct port_info {size_t first_qset; struct adapter* adapter; } ;
struct net_device {int dummy; } ;
struct ipsec_sa_entry {int dummy; } ;
struct ip_esp_hdr {int /*<<< orphan*/  seq_no; int /*<<< orphan*/  spi; } ;
struct chcr_ipsec_aadiv {int /*<<< orphan*/  iv; int /*<<< orphan*/  seq_no; int /*<<< orphan*/  spi; } ;
struct TYPE_4__ {struct sge_eth_txq* ethtxq; } ;
struct adapter {TYPE_1__ sge; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int) ; 
 int /*<<< orphan*/  FILL_CMD_MORE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be64 (size_t) ; 
 size_t htonl (int /*<<< orphan*/ ) ; 
 scalar_t__ is_eth_imm (struct sk_buff*,struct ipsec_sa_entry*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 
 struct port_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  skb_is_nonlinear (struct sk_buff*) ; 
 int /*<<< orphan*/ * skb_transport_header (struct sk_buff*) ; 
 struct xfrm_offload* xfrm_offload (struct sk_buff*) ; 

inline void *copy_esn_pktxt(struct sk_buff *skb,
			    struct net_device *dev,
			    void *pos,
			    struct ipsec_sa_entry *sa_entry)
{
	struct chcr_ipsec_aadiv *aadiv;
	struct ulptx_idata *sc_imm;
	struct ip_esp_hdr *esphdr;
	struct xfrm_offload *xo;
	struct sge_eth_txq *q;
	struct adapter *adap;
	struct port_info *pi;
	__be64 seqno;
	u32 qidx;
	u32 seqlo;
	u8 *iv;
	int eoq;
	int len;

	pi = netdev_priv(dev);
	adap = pi->adapter;
	qidx = skb->queue_mapping;
	q = &adap->sge.ethtxq[qidx + pi->first_qset];

	/* end of queue, reset pos to start of queue */
	eoq = (void *)q->q.stat - pos;
	if (!eoq)
		pos = q->q.desc;

	len = DIV_ROUND_UP(sizeof(struct chcr_ipsec_aadiv), 16) << 4;
	memset(pos, 0, len);
	aadiv = (struct chcr_ipsec_aadiv *)pos;
	esphdr = (struct ip_esp_hdr *)skb_transport_header(skb);
	iv = skb_transport_header(skb) + sizeof(struct ip_esp_hdr);
	xo = xfrm_offload(skb);

	aadiv->spi = (esphdr->spi);
	seqlo = htonl(esphdr->seq_no);
	seqno = cpu_to_be64(seqlo + ((u64)xo->seq.hi << 32));
	memcpy(aadiv->seq_no, &seqno, 8);
	iv = skb_transport_header(skb) + sizeof(struct ip_esp_hdr);
	memcpy(aadiv->iv, iv, 8);

	if (is_eth_imm(skb, sa_entry) && !skb_is_nonlinear(skb)) {
		sc_imm = (struct ulptx_idata *)(pos +
			  (DIV_ROUND_UP(sizeof(struct chcr_ipsec_aadiv),
					sizeof(__be64)) << 3));
		sc_imm->cmd_more = FILL_CMD_MORE(0);
		sc_imm->len = cpu_to_be32(skb->len);
	}
	pos += len;
	return pos;
}
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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mbuf {int /*<<< orphan*/  m_len; struct mbuf* m_next; } ;
struct ipoib_tx_buf {int /*<<< orphan*/ * mapping; struct mbuf* mb; } ;
struct TYPE_6__ {int num_sge; unsigned int wr_id; int /*<<< orphan*/  opcode; } ;
struct TYPE_5__ {int hlen; TYPE_3__ wr; void* header; scalar_t__ mss; struct ib_ah* ah; int /*<<< orphan*/  remote_qpn; } ;
struct ipoib_dev_priv {TYPE_2__ tx_wr; int /*<<< orphan*/  qp; TYPE_1__* tx_sge; } ;
struct ib_send_wr {int dummy; } ;
struct ib_ah {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_WR_LSO ; 
 int /*<<< orphan*/  IB_WR_SEND ; 
 int ib_post_send (int /*<<< orphan*/ ,TYPE_3__*,struct ib_send_wr**) ; 

__attribute__((used)) static inline int
post_send(struct ipoib_dev_priv *priv, unsigned int wr_id,
    struct ib_ah *address, u32 qpn, struct ipoib_tx_buf *tx_req, void *head,
    int hlen)
{
	struct ib_send_wr *bad_wr;
	struct mbuf *mb = tx_req->mb;
	u64 *mapping = tx_req->mapping;
	struct mbuf *m;
	int i;

	for (m = mb, i = 0; m != NULL; m = m->m_next, i++) {
		priv->tx_sge[i].addr         = mapping[i];
		priv->tx_sge[i].length       = m->m_len;
	}
	priv->tx_wr.wr.num_sge	= i;
	priv->tx_wr.wr.wr_id	= wr_id;
	priv->tx_wr.remote_qpn	= qpn;
	priv->tx_wr.ah		= address;

	if (head) {
		priv->tx_wr.mss		= 0; /* XXX mb_shinfo(mb)->gso_size; */
		priv->tx_wr.header	= head;
		priv->tx_wr.hlen	= hlen;
		priv->tx_wr.wr.opcode	= IB_WR_LSO;
	} else
		priv->tx_wr.wr.opcode	= IB_WR_SEND;

	return ib_post_send(priv->qp, &priv->tx_wr.wr, &bad_wr);
}
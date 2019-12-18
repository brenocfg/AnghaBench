#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct vector_private {int in_error; TYPE_3__* dev; TYPE_1__* fds; int /*<<< orphan*/  header_txbuffer; } ;
struct sk_buff {scalar_t__ len; } ;
struct iovec {int /*<<< orphan*/  iov_base; } ;
struct TYPE_6__ {int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_bytes; } ;
struct TYPE_7__ {TYPE_2__ stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  tx_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_IOV_SIZE ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_trans_update (TYPE_3__*) ; 
 int /*<<< orphan*/  netif_wake_queue (TYPE_3__*) ; 
 int prep_msg (struct vector_private*,struct sk_buff*,struct iovec*) ; 
 int uml_vector_writev (int /*<<< orphan*/ ,struct iovec*,int) ; 

__attribute__((used)) static int writev_tx(struct vector_private *vp, struct sk_buff *skb)
{
	struct iovec iov[3 + MAX_IOV_SIZE];
	int iov_count, pkt_len = 0;

	iov[0].iov_base = vp->header_txbuffer;
	iov_count = prep_msg(vp, skb, (struct iovec *) &iov);

	if (iov_count < 1)
		goto drop;

	pkt_len = uml_vector_writev(
		vp->fds->tx_fd,
		(struct iovec *) &iov,
		iov_count
	);

	if (pkt_len < 0)
		goto drop;

	netif_trans_update(vp->dev);
	netif_wake_queue(vp->dev);

	if (pkt_len > 0) {
		vp->dev->stats.tx_bytes += skb->len;
		vp->dev->stats.tx_packets++;
	} else {
		vp->dev->stats.tx_dropped++;
	}
	consume_skb(skb);
	return pkt_len;
drop:
	vp->dev->stats.tx_dropped++;
	consume_skb(skb);
	if (pkt_len < 0)
		vp->in_error = true;
	return pkt_len;
}
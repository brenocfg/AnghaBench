#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct vector_queue {void** skbuff_vector; int queue_depth; int /*<<< orphan*/  max_depth; struct mmsghdr* mmsg_vector; } ;
struct TYPE_12__ {int rx_queue_max; int rx_queue_running_average; int /*<<< orphan*/  rx_csum_offload_good; int /*<<< orphan*/  rx_encaps_errors; } ;
struct vector_private {int in_error; scalar_t__ header_size; int (* verify_header ) (int /*<<< orphan*/ ,struct sk_buff*,struct vector_private*) ;scalar_t__ rx_header_size; TYPE_6__ estats; TYPE_5__* dev; TYPE_1__* fds; struct vector_queue* rx_queue; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;
struct TYPE_9__ {TYPE_2__* msg_iov; } ;
struct mmsghdr {scalar_t__ msg_len; TYPE_3__ msg_hdr; } ;
struct TYPE_10__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; } ;
struct TYPE_11__ {TYPE_4__ stats; } ;
struct TYPE_8__ {int /*<<< orphan*/  iov_base; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  prep_queue_for_rx (struct vector_queue*) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*,struct vector_private*) ; 
 int uml_vector_recvmmsg (int /*<<< orphan*/ ,struct mmsghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vector_mmsg_rx(struct vector_private *vp)
{
	int packet_count, i;
	struct vector_queue *qi = vp->rx_queue;
	struct sk_buff *skb;
	struct mmsghdr *mmsg_vector = qi->mmsg_vector;
	void **skbuff_vector = qi->skbuff_vector;
	int header_check;

	/* Refresh the vector and make sure it is with new skbs and the
	 * iovs are updated to point to them.
	 */

	prep_queue_for_rx(qi);

	/* Fire the Lazy Gun - get as many packets as we can in one go. */

	packet_count = uml_vector_recvmmsg(
		vp->fds->rx_fd, qi->mmsg_vector, qi->max_depth, 0);

	if (packet_count < 0)
		vp->in_error = true;

	if (packet_count <= 0)
		return packet_count;

	/* We treat packet processing as enqueue, buffer refresh as dequeue
	 * The queue_depth tells us how many buffers have been used and how
	 * many do we need to prep the next time prep_queue_for_rx() is called.
	 */

	qi->queue_depth = packet_count;

	for (i = 0; i < packet_count; i++) {
		skb = (*skbuff_vector);
		if (mmsg_vector->msg_len > vp->header_size) {
			if (vp->header_size > 0) {
				header_check = vp->verify_header(
					mmsg_vector->msg_hdr.msg_iov->iov_base,
					skb,
					vp
				);
				if (header_check < 0) {
				/* Overlay header failed to verify - discard.
				 * We can actually keep this skb and reuse it,
				 * but that will make the prep logic too
				 * complex.
				 */
					dev_kfree_skb_irq(skb);
					vp->estats.rx_encaps_errors++;
					continue;
				}
				if (header_check > 0) {
					vp->estats.rx_csum_offload_good++;
					skb->ip_summed = CHECKSUM_UNNECESSARY;
				}
			}
			pskb_trim(skb,
				mmsg_vector->msg_len - vp->rx_header_size);
			skb->protocol = eth_type_trans(skb, skb->dev);
			/*
			 * We do not need to lock on updating stats here
			 * The interrupt loop is non-reentrant.
			 */
			vp->dev->stats.rx_bytes += skb->len;
			vp->dev->stats.rx_packets++;
			netif_rx(skb);
		} else {
			/* Overlay header too short to do anything - discard.
			 * We can actually keep this skb and reuse it,
			 * but that will make the prep logic too complex.
			 */
			if (skb != NULL)
				dev_kfree_skb_irq(skb);
		}
		(*skbuff_vector) = NULL;
		/* Move to the next buffer element */
		mmsg_vector++;
		skbuff_vector++;
	}
	if (packet_count > 0) {
		if (vp->estats.rx_queue_max < packet_count)
			vp->estats.rx_queue_max = packet_count;
		vp->estats.rx_queue_running_average =
			(vp->estats.rx_queue_running_average + packet_count) >> 1;
	}
	return packet_count;
}
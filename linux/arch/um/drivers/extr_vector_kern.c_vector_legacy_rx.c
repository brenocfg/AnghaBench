#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rx_csum_offload_good; int /*<<< orphan*/  rx_encaps_errors; } ;
struct vector_private {int header_size; int in_error; int (* verify_header ) (int /*<<< orphan*/ ,struct sk_buff*,struct vector_private*) ;TYPE_4__* dev; scalar_t__ rx_header_size; TYPE_2__ estats; int /*<<< orphan*/  header_rxbuffer; TYPE_1__* fds; } ;
struct user_msghdr {int msg_iovlen; scalar_t__ msg_flags; scalar_t__ msg_controllen; int /*<<< orphan*/ * msg_control; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; int /*<<< orphan*/  ip_summed; } ;
struct iovec {int iov_len; int /*<<< orphan*/  iov_base; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx_packets; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_dropped; } ;
struct TYPE_8__ {TYPE_3__ stats; } ;
struct TYPE_5__ {int /*<<< orphan*/  rx_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_UNNECESSARY ; 
 int DROP_BUFFER_SIZE ; 
 int /*<<< orphan*/  MAX_IOV_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  drop_buffer ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_rx (struct sk_buff*) ; 
 struct sk_buff* prep_skb (struct vector_private*,struct user_msghdr*) ; 
 int /*<<< orphan*/  pskb_trim (struct sk_buff*,scalar_t__) ; 
 int stub1 (int /*<<< orphan*/ ,struct sk_buff*,struct vector_private*) ; 
 int uml_vector_recvmsg (int /*<<< orphan*/ ,struct user_msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vector_legacy_rx(struct vector_private *vp)
{
	int pkt_len;
	struct user_msghdr hdr;
	struct iovec iov[2 + MAX_IOV_SIZE]; /* header + data use case only */
	int iovpos = 0;
	struct sk_buff *skb;
	int header_check;

	hdr.msg_name = NULL;
	hdr.msg_namelen = 0;
	hdr.msg_iov = (struct iovec *) &iov;
	hdr.msg_control = NULL;
	hdr.msg_controllen = 0;
	hdr.msg_flags = 0;

	if (vp->header_size > 0) {
		iov[0].iov_base = vp->header_rxbuffer;
		iov[0].iov_len = vp->header_size;
	}

	skb = prep_skb(vp, &hdr);

	if (skb == NULL) {
		/* Read a packet into drop_buffer and don't do
		 * anything with it.
		 */
		iov[iovpos].iov_base = drop_buffer;
		iov[iovpos].iov_len = DROP_BUFFER_SIZE;
		hdr.msg_iovlen = 1;
		vp->dev->stats.rx_dropped++;
	}

	pkt_len = uml_vector_recvmsg(vp->fds->rx_fd, &hdr, 0);
	if (pkt_len < 0) {
		vp->in_error = true;
		return pkt_len;
	}

	if (skb != NULL) {
		if (pkt_len > vp->header_size) {
			if (vp->header_size > 0) {
				header_check = vp->verify_header(
					vp->header_rxbuffer, skb, vp);
				if (header_check < 0) {
					dev_kfree_skb_irq(skb);
					vp->dev->stats.rx_dropped++;
					vp->estats.rx_encaps_errors++;
					return 0;
				}
				if (header_check > 0) {
					vp->estats.rx_csum_offload_good++;
					skb->ip_summed = CHECKSUM_UNNECESSARY;
				}
			}
			pskb_trim(skb, pkt_len - vp->rx_header_size);
			skb->protocol = eth_type_trans(skb, skb->dev);
			vp->dev->stats.rx_bytes += skb->len;
			vp->dev->stats.rx_packets++;
			netif_rx(skb);
		} else {
			dev_kfree_skb_irq(skb);
		}
	}
	return pkt_len;
}
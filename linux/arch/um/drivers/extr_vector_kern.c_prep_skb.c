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
struct vector_private {int max_packet; int req_size; scalar_t__ header_size; int /*<<< orphan*/  dev; int /*<<< orphan*/  headroom; } ;
struct user_msghdr {int msg_iovlen; struct iovec* msg_iov; } ;
struct sk_buff {int data_len; int /*<<< orphan*/ * data; int /*<<< orphan*/  ip_summed; int /*<<< orphan*/  len; int /*<<< orphan*/  dev; } ;
struct iovec {int iov_len; int /*<<< orphan*/ * iov_base; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
struct TYPE_2__ {int nr_frags; int /*<<< orphan*/ * frags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECKSUM_NONE ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int SAFETY_MARGIN ; 
 struct sk_buff* alloc_skb_with_frags (int,int,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skb_frag_address_safe (int /*<<< orphan*/ *) ; 
 int skb_frag_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_reserve (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static struct sk_buff *prep_skb(
	struct vector_private *vp,
	struct user_msghdr *msg)
{
	int linear = vp->max_packet + vp->headroom + SAFETY_MARGIN;
	struct sk_buff *result;
	int iov_index = 0, len;
	struct iovec *iov = msg->msg_iov;
	int err, nr_frags, frag;
	skb_frag_t *skb_frag;

	if (vp->req_size <= linear)
		len = linear;
	else
		len = vp->req_size;
	result = alloc_skb_with_frags(
		linear,
		len - vp->max_packet,
		3,
		&err,
		GFP_ATOMIC
	);
	if (vp->header_size > 0)
		iov_index++;
	if (result == NULL) {
		iov[iov_index].iov_base = NULL;
		iov[iov_index].iov_len = 0;
		goto done;
	}
	skb_reserve(result, vp->headroom);
	result->dev = vp->dev;
	skb_put(result, vp->max_packet);
	result->data_len = len - vp->max_packet;
	result->len += len - vp->max_packet;
	skb_reset_mac_header(result);
	result->ip_summed = CHECKSUM_NONE;
	iov[iov_index].iov_base = result->data;
	iov[iov_index].iov_len = vp->max_packet;
	iov_index++;

	nr_frags = skb_shinfo(result)->nr_frags;
	for (frag = 0; frag < nr_frags; frag++) {
		skb_frag = &skb_shinfo(result)->frags[frag];
		iov[iov_index].iov_base = skb_frag_address_safe(skb_frag);
		if (iov[iov_index].iov_base != NULL)
			iov[iov_index].iov_len = skb_frag_size(skb_frag);
		else
			iov[iov_index].iov_len = 0;
		iov_index++;
	}
done:
	msg->msg_iovlen = iov_index;
	return result;
}
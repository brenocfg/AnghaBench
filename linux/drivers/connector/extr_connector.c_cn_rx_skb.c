#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct sk_buff {scalar_t__ len; } ;
struct nlmsghdr {scalar_t__ nlmsg_len; } ;
struct cn_msg {int dummy; } ;

/* Variables and functions */
 int CONNECTOR_MAX_MSG_SIZE ; 
 scalar_t__ NLMSG_HDRLEN ; 
 int cn_call_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct nlmsghdr* nlmsg_hdr (struct sk_buff*) ; 
 int nlmsg_len (struct nlmsghdr*) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 

__attribute__((used)) static void cn_rx_skb(struct sk_buff *skb)
{
	struct nlmsghdr *nlh;
	int len, err;

	if (skb->len >= NLMSG_HDRLEN) {
		nlh = nlmsg_hdr(skb);
		len = nlmsg_len(nlh);

		if (len < (int)sizeof(struct cn_msg) ||
		    skb->len < nlh->nlmsg_len ||
		    len > CONNECTOR_MAX_MSG_SIZE)
			return;

		err = cn_call_callback(skb_get(skb));
		if (err < 0)
			kfree_skb(skb);
	}
}
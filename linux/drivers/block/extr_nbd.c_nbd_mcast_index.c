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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NBD_ATTR_INDEX ; 
 int /*<<< orphan*/  NBD_CMD_LINK_DEAD ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int /*<<< orphan*/  genlmsg_multicast (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nbd_genl_family ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_total_size (int) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 

__attribute__((used)) static void nbd_mcast_index(int index)
{
	struct sk_buff *skb;
	void *msg_head;
	int ret;

	skb = genlmsg_new(nla_total_size(sizeof(u32)), GFP_KERNEL);
	if (!skb)
		return;
	msg_head = genlmsg_put(skb, 0, 0, &nbd_genl_family, 0,
				     NBD_CMD_LINK_DEAD);
	if (!msg_head) {
		nlmsg_free(skb);
		return;
	}
	ret = nla_put_u32(skb, NBD_ATTR_INDEX, index);
	if (ret) {
		nlmsg_free(skb);
		return;
	}
	genlmsg_end(skb, msg_head);
	genlmsg_multicast(&nbd_genl_family, skb, 0, 0, GFP_KERNEL);
}
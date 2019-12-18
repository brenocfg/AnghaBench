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
struct genl_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NBD_ATTR_INDEX ; 
 int /*<<< orphan*/  NBD_CMD_CONNECT ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put_reply (struct sk_buff*,struct genl_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  nbd_genl_family ; 
 int nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nla_total_size (int) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 

__attribute__((used)) static void nbd_connect_reply(struct genl_info *info, int index)
{
	struct sk_buff *skb;
	void *msg_head;
	int ret;

	skb = genlmsg_new(nla_total_size(sizeof(u32)), GFP_KERNEL);
	if (!skb)
		return;
	msg_head = genlmsg_put_reply(skb, info, &nbd_genl_family, 0,
				     NBD_CMD_CONNECT);
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
	genlmsg_reply(skb, info);
}
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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NLMSG_GOODSIZE ; 
 struct sk_buff* genlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* genlmsg_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt753x_nl_family ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 

__attribute__((used)) static int mt753x_nl_prepare_reply(struct genl_info *info, u8 cmd,
				   struct sk_buff **skbp)
{
	struct sk_buff *msg;
	void *reply;

	if (!info)
		return -EINVAL;

	msg = genlmsg_new(NLMSG_GOODSIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;

	/* Construct send-back message header */
	reply = genlmsg_put(msg, info->snd_portid, info->snd_seq,
			    &mt753x_nl_family, 0, cmd);
	if (!reply) {
		nlmsg_free(msg);
		return -EINVAL;
	}

	*skbp = msg;
	return 0;
}
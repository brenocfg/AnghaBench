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
typedef  int u32 ;
struct sk_buff {int dummy; } ;
struct mt753x_nl_cmd_item {scalar_t__ cmd; int nr_required_attrs; size_t* required_attrs; int (* process ) (struct genl_info*,struct gsw_mt753x*) ;scalar_t__ require_dev; } ;
struct gsw_mt753x {int dummy; } ;
struct genlmsghdr {scalar_t__ cmd; } ;
struct genl_info {scalar_t__* attrs; int /*<<< orphan*/  nlhdr; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct mt753x_nl_cmd_item*) ; 
 int EINVAL ; 
 struct mt753x_nl_cmd_item* mt753x_nl_cmds ; 
 struct gsw_mt753x* mt753x_nl_parse_find_gsw (struct genl_info*) ; 
 int /*<<< orphan*/  mt753x_put_gsw () ; 
 struct genlmsghdr* nlmsg_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,...) ; 
 int stub1 (struct genl_info*,struct gsw_mt753x*) ; 

__attribute__((used)) static int mt753x_nl_response(struct sk_buff *skb, struct genl_info *info)
{
	struct genlmsghdr *hdr = nlmsg_data(info->nlhdr);
	const struct mt753x_nl_cmd_item *cmditem = NULL;
	struct gsw_mt753x *gsw = NULL;
	u32 sat_req_attrs = 0;
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(mt753x_nl_cmds); i++) {
		if (hdr->cmd == mt753x_nl_cmds[i].cmd) {
			cmditem = &mt753x_nl_cmds[i];
			break;
		}
	}

	if (!cmditem) {
		pr_info("mt753x-nl: unknown cmd %u\n", hdr->cmd);
		return -EINVAL;
	}

	for (i = 0; i < cmditem->nr_required_attrs; i++) {
		if (info->attrs[cmditem->required_attrs[i]])
			sat_req_attrs++;
	}

	if (sat_req_attrs != cmditem->nr_required_attrs) {
		pr_info("mt753x-nl: missing required attr(s) for cmd %u\n",
			hdr->cmd);
		return -EINVAL;
	}

	if (cmditem->require_dev) {
		gsw = mt753x_nl_parse_find_gsw(info);
		if (!gsw) {
			pr_info("mt753x-nl: failed to find switch dev\n");
			return -EINVAL;
		}
	}

	ret = cmditem->process(info, gsw);

	mt753x_put_gsw();

	return ret;
}
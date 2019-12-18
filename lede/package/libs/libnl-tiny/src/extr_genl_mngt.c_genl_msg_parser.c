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
struct sockaddr_nl {int dummy; } ;
struct nlmsghdr {int dummy; } ;
struct nlattr {int dummy; } ;
struct nl_parser_param {int dummy; } ;
struct nl_cache_ops {int /*<<< orphan*/  co_hdrsize; TYPE_1__* co_genl; } ;
struct genlmsghdr {scalar_t__ cmd; } ;
struct genl_info {struct nlattr** attrs; int /*<<< orphan*/  userhdr; struct genlmsghdr* genlhdr; struct nlmsghdr* nlh; struct sockaddr_nl* who; } ;
struct genl_cmd {scalar_t__ c_id; int (* c_msg_parser ) (struct nl_cache_ops*,struct genl_cmd*,struct genl_info*,struct nl_parser_param*) ;int /*<<< orphan*/  c_attr_policy; int /*<<< orphan*/  c_maxattr; } ;
struct TYPE_2__ {int o_ncmds; struct genl_cmd* o_cmds; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int NLE_MSGTYPE_NOSUPPORT ; 
 int NLE_OPNOTSUPP ; 
 int /*<<< orphan*/  genlmsg_data (struct genlmsghdr*) ; 
 struct genlmsghdr* nlmsg_data (struct nlmsghdr*) ; 
 int nlmsg_parse (struct nlmsghdr*,int /*<<< orphan*/ ,struct nlattr**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (struct nl_cache_ops*,struct genl_cmd*,struct genl_info*,struct nl_parser_param*) ; 

__attribute__((used)) static int genl_msg_parser(struct nl_cache_ops *ops, struct sockaddr_nl *who,
			   struct nlmsghdr *nlh, struct nl_parser_param *pp)
{
	int i, err;
	struct genlmsghdr *ghdr;
	struct genl_cmd *cmd;

	ghdr = nlmsg_data(nlh);

	if (ops->co_genl == NULL)
		BUG();

	for (i = 0; i < ops->co_genl->o_ncmds; i++) {
		cmd = &ops->co_genl->o_cmds[i];
		if (cmd->c_id == ghdr->cmd)
			goto found;
	}

	err = -NLE_MSGTYPE_NOSUPPORT;
	goto errout;

found:
	if (cmd->c_msg_parser == NULL)
		err = -NLE_OPNOTSUPP;
	else {
		struct nlattr *tb[cmd->c_maxattr + 1];
		struct genl_info info = {
			.who = who,
			.nlh = nlh,
			.genlhdr = ghdr,
			.userhdr = genlmsg_data(ghdr),
			.attrs = tb,
		};

		err = nlmsg_parse(nlh, ops->co_hdrsize, tb, cmd->c_maxattr,
				  cmd->c_attr_policy);
		if (err < 0)
			goto errout;

		err = cmd->c_msg_parser(ops, cmd, &info, pp);
	}
errout:
	return err;

}
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
struct nlmsghdr {scalar_t__ nlmsg_type; } ;
struct nl_parser_param {int dummy; } ;
struct nl_cache_ops {int (* co_msg_parser ) (struct nl_cache_ops*,struct sockaddr_nl*,struct nlmsghdr*,struct nl_parser_param*) ;TYPE_1__* co_msgtypes; int /*<<< orphan*/  co_hdrsize; } ;
struct TYPE_2__ {scalar_t__ mt_id; } ;

/* Variables and functions */
 int NLE_MSGTYPE_NOSUPPORT ; 
 int NLE_MSG_TOOSHORT ; 
 int NLE_OPNOTSUPP ; 
 int /*<<< orphan*/  nlmsg_valid_hdr (struct nlmsghdr*,int /*<<< orphan*/ ) ; 
 int stub1 (struct nl_cache_ops*,struct sockaddr_nl*,struct nlmsghdr*,struct nl_parser_param*) ; 

int nl_cache_parse(struct nl_cache_ops *ops, struct sockaddr_nl *who,
		   struct nlmsghdr *nlh, struct nl_parser_param *params)
{
	int i, err;

	if (!nlmsg_valid_hdr(nlh, ops->co_hdrsize))
		return -NLE_MSG_TOOSHORT;

	for (i = 0; ops->co_msgtypes[i].mt_id >= 0; i++) {
		if (ops->co_msgtypes[i].mt_id == nlh->nlmsg_type) {
			err = ops->co_msg_parser(ops, who, nlh, params);
			if (err != -NLE_OPNOTSUPP)
				goto errout;
		}
	}


	err = -NLE_MSGTYPE_NOSUPPORT;
errout:
	return err;
}
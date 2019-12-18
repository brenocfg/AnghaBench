#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nl_parser_param {struct dp_xdata* pp_arg; int /*<<< orphan*/  pp_cb; } ;
struct nl_msg {int dummy; } ;
struct nl_cache_ops {int dummy; } ;
struct dp_xdata {void (* cb ) (struct nl_object*,void*) ;void* arg; } ;
struct TYPE_3__ {int /*<<< orphan*/  nlmsg_type; } ;

/* Variables and functions */
 int NLE_MSGTYPE_NOSUPPORT ; 
 struct nl_cache_ops* nl_cache_ops_associate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nl_cache_parse (struct nl_cache_ops*,int /*<<< orphan*/ *,TYPE_1__*,struct nl_parser_param*) ; 
 int /*<<< orphan*/  nlmsg_get_proto (struct nl_msg*) ; 
 TYPE_1__* nlmsg_hdr (struct nl_msg*) ; 
 int /*<<< orphan*/  parse_cb ; 

int nl_msg_parse(struct nl_msg *msg, void (*cb)(struct nl_object *, void *),
		 void *arg)
{
	struct nl_cache_ops *ops;
	struct nl_parser_param p = {
		.pp_cb = parse_cb
	};
	struct dp_xdata x = {
		.cb = cb,
		.arg = arg,
	};

	ops = nl_cache_ops_associate(nlmsg_get_proto(msg),
				     nlmsg_hdr(msg)->nlmsg_type);
	if (ops == NULL)
		return -NLE_MSGTYPE_NOSUPPORT;
	p.pp_arg = &x;

	return nl_cache_parse(ops, NULL, nlmsg_hdr(msg), &p);
}
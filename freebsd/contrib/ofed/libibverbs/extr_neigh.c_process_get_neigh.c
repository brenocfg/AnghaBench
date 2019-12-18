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
struct rtmsg {int /*<<< orphan*/  rtm_dst_len; int /*<<< orphan*/  rtm_family; } ;
struct nl_msg {int dummy; } ;
struct get_neigh_handler {scalar_t__ oif; int /*<<< orphan*/  sock; int /*<<< orphan*/  dst; } ;
typedef  int /*<<< orphan*/  rmsg ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  NLMSG_ALIGNTO ; 
 int /*<<< orphan*/  NL_CB_CUSTOM ; 
 int /*<<< orphan*/  NL_CB_VALID ; 
 int /*<<< orphan*/  RTA_DST ; 
 int /*<<< orphan*/  RTA_OIF ; 
 int /*<<< orphan*/  RTM_GETROUTE ; 
 int /*<<< orphan*/  get_route_cb ; 
 int /*<<< orphan*/  nl_addr_get_family (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_addr_get_prefixlen (int /*<<< orphan*/ ) ; 
 int nl_recvmsgs_default (int /*<<< orphan*/ ) ; 
 int nl_send_auto_complete (int /*<<< orphan*/ ,struct nl_msg*) ; 
 int /*<<< orphan*/  nl_socket_modify_cb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct get_neigh_handler*) ; 
 int /*<<< orphan*/  nla_put_addr (struct nl_msg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put_u32 (struct nl_msg*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct nl_msg* nlmsg_alloc_simple (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_append (struct nl_msg*,struct rtmsg*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct nl_msg*) ; 

int process_get_neigh(struct get_neigh_handler *neigh_handler)
{
	struct nl_msg *m;
	struct rtmsg rmsg = {
		.rtm_family = nl_addr_get_family(neigh_handler->dst),
		.rtm_dst_len = nl_addr_get_prefixlen(neigh_handler->dst),
	};
	int err;

	m = nlmsg_alloc_simple(RTM_GETROUTE, 0);

	if (m == NULL)
		return -ENOMEM;

	nlmsg_append(m, &rmsg, sizeof(rmsg), NLMSG_ALIGNTO);

	nla_put_addr(m, RTA_DST, neigh_handler->dst);

	if (neigh_handler->oif > 0)
		nla_put_u32(m, RTA_OIF, neigh_handler->oif);

	err = nl_send_auto_complete(neigh_handler->sock, m);
	nlmsg_free(m);
	if (err < 0)
		return err;

	nl_socket_modify_cb(neigh_handler->sock, NL_CB_VALID,
			    NL_CB_CUSTOM, &get_route_cb, neigh_handler);

	err = nl_recvmsgs_default(neigh_handler->sock);

	return err;
}
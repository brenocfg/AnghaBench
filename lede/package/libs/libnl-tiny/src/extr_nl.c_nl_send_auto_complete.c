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
struct nlmsghdr {scalar_t__ nlmsg_pid; scalar_t__ nlmsg_seq; int /*<<< orphan*/  nlmsg_flags; } ;
struct TYPE_2__ {scalar_t__ nl_pid; } ;
struct nl_sock {int s_proto; int s_flags; int /*<<< orphan*/  s_seq_next; TYPE_1__ s_local; struct nl_cb* s_cb; } ;
struct nl_msg {int nm_protocol; } ;
struct nl_cb {int (* cb_send_ow ) (struct nl_sock*,struct nl_msg*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_F_ACK ; 
 int /*<<< orphan*/  NLM_F_REQUEST ; 
 int NL_NO_AUTO_ACK ; 
 int nl_send (struct nl_sock*,struct nl_msg*) ; 
 struct nlmsghdr* nlmsg_hdr (struct nl_msg*) ; 
 int stub1 (struct nl_sock*,struct nl_msg*) ; 

int nl_send_auto_complete(struct nl_sock *sk, struct nl_msg *msg)
{
	struct nlmsghdr *nlh;
	struct nl_cb *cb = sk->s_cb;

	nlh = nlmsg_hdr(msg);
	if (nlh->nlmsg_pid == 0)
		nlh->nlmsg_pid = sk->s_local.nl_pid;

	if (nlh->nlmsg_seq == 0)
		nlh->nlmsg_seq = sk->s_seq_next++;

	if (msg->nm_protocol == -1)
		msg->nm_protocol = sk->s_proto;
	
	nlh->nlmsg_flags |= NLM_F_REQUEST;

	if (!(sk->s_flags & NL_NO_AUTO_ACK))
		nlh->nlmsg_flags |= NLM_F_ACK;

	if (cb->cb_send_ow)
		return cb->cb_send_ow(sk, msg);
	else
		return nl_send(sk, msg);
}
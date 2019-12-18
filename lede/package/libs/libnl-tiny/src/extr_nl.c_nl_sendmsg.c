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
struct nl_sock {int /*<<< orphan*/  s_fd; struct nl_cb* s_cb; int /*<<< orphan*/  s_local; } ;
struct nl_msg {int dummy; } ;
struct nl_cb {scalar_t__* cb_set; } ;
struct msghdr {int msg_iovlen; struct iovec* msg_iov; } ;
struct iovec {void* iov_base; int /*<<< orphan*/  iov_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  nlmsg_len; } ;

/* Variables and functions */
 size_t NL_CB_MSG_OUT ; 
 scalar_t__ NL_OK ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ nl_cb_call (struct nl_cb*,size_t,struct nl_msg*) ; 
 int nl_syserr2nlerr (int /*<<< orphan*/ ) ; 
 TYPE_1__* nlmsg_hdr (struct nl_msg*) ; 
 int /*<<< orphan*/  nlmsg_set_src (struct nl_msg*,int /*<<< orphan*/ *) ; 
 int sendmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 

int nl_sendmsg(struct nl_sock *sk, struct nl_msg *msg, struct msghdr *hdr)
{
	struct nl_cb *cb;
	int ret;

	struct iovec iov = {
		.iov_base = (void *) nlmsg_hdr(msg),
		.iov_len = nlmsg_hdr(msg)->nlmsg_len,
	};

	hdr->msg_iov = &iov;
	hdr->msg_iovlen = 1;

	nlmsg_set_src(msg, &sk->s_local);

	cb = sk->s_cb;
	if (cb->cb_set[NL_CB_MSG_OUT])
		if (nl_cb_call(cb, NL_CB_MSG_OUT, msg) != NL_OK)
			return 0;

	ret = sendmsg(sk->s_fd, hdr, 0);
	if (ret < 0)
		return -nl_syserr2nlerr(errno);

	return ret;
}
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
struct nl_sock {int dummy; } ;
struct nl_msg {int dummy; } ;

/* Variables and functions */
 int NLE_NOMEM ; 
 int /*<<< orphan*/  NLMSG_ALIGNTO ; 
 int nl_send_auto_complete (struct nl_sock*,struct nl_msg*) ; 
 struct nl_msg* nlmsg_alloc_simple (int,int) ; 
 int nlmsg_append (struct nl_msg*,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct nl_msg*) ; 

int nl_send_simple(struct nl_sock *sk, int type, int flags, void *buf,
		   size_t size)
{
	int err;
	struct nl_msg *msg;

	msg = nlmsg_alloc_simple(type, flags);
	if (!msg)
		return -NLE_NOMEM;

	if (buf && size) {
		err = nlmsg_append(msg, buf, size, NLMSG_ALIGNTO);
		if (err < 0)
			goto errout;
	}
	

	err = nl_send_auto_complete(sk, msg);
errout:
	nlmsg_free(msg);

	return err;
}
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
struct nl_cb {int (* cb_recvmsgs_ow ) (struct nl_sock*,struct nl_cb*) ;} ;

/* Variables and functions */
 int recvmsgs (struct nl_sock*,struct nl_cb*) ; 
 int stub1 (struct nl_sock*,struct nl_cb*) ; 

int nl_recvmsgs(struct nl_sock *sk, struct nl_cb *cb)
{
	if (cb->cb_recvmsgs_ow)
		return cb->cb_recvmsgs_ow(sk, cb);
	else
		return recvmsgs(sk, cb);
}
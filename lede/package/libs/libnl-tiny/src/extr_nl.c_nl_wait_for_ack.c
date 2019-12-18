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
struct nl_sock {int /*<<< orphan*/  s_cb; } ;
struct nl_cb {int dummy; } ;

/* Variables and functions */
 int NLE_NOMEM ; 
 int /*<<< orphan*/  NL_CB_ACK ; 
 int /*<<< orphan*/  NL_CB_CUSTOM ; 
 int /*<<< orphan*/  ack_wait_handler ; 
 struct nl_cb* nl_cb_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_cb_put (struct nl_cb*) ; 
 int /*<<< orphan*/  nl_cb_set (struct nl_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int nl_recvmsgs (struct nl_sock*,struct nl_cb*) ; 

int nl_wait_for_ack(struct nl_sock *sk)
{
	int err;
	struct nl_cb *cb;

	cb = nl_cb_clone(sk->s_cb);
	if (cb == NULL)
		return -NLE_NOMEM;

	nl_cb_set(cb, NL_CB_ACK, NL_CB_CUSTOM, ack_wait_handler, NULL);
	err = nl_recvmsgs(sk, cb);
	nl_cb_put(cb);

	return err;
}
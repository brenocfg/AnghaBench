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
typedef  scalar_t__ unl_cb ;
struct unl {int /*<<< orphan*/  sock; } ;
struct nl_msg {int dummy; } ;
struct nl_cb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NL_CB_ACK ; 
 int /*<<< orphan*/  NL_CB_CUSTOM ; 
 int /*<<< orphan*/  NL_CB_FINISH ; 
 int /*<<< orphan*/  NL_CB_VALID ; 
 int /*<<< orphan*/  ack_handler ; 
 int /*<<< orphan*/  error_handler ; 
 int /*<<< orphan*/  finish_handler ; 
 struct nl_cb* nl_cb_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nl_cb_err (struct nl_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  nl_cb_put (struct nl_cb*) ; 
 int /*<<< orphan*/  nl_cb_set (struct nl_cb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*) ; 
 int /*<<< orphan*/  nl_recvmsgs (int /*<<< orphan*/ ,struct nl_cb*) ; 
 int nl_send_auto_complete (int /*<<< orphan*/ ,struct nl_msg*) ; 
 int /*<<< orphan*/  nlmsg_free (struct nl_msg*) ; 

int unl_genl_request(struct unl *unl, struct nl_msg *msg, unl_cb handler, void *arg)
{
	struct nl_cb *cb;
	int err;

	cb = nl_cb_alloc(NL_CB_CUSTOM);
	err = nl_send_auto_complete(unl->sock, msg);
	if (err < 0)
		goto out;

	err = 1;
	nl_cb_err(cb, NL_CB_CUSTOM, error_handler, &err);
	nl_cb_set(cb, NL_CB_FINISH, NL_CB_CUSTOM, finish_handler, &err);
	nl_cb_set(cb, NL_CB_ACK, NL_CB_CUSTOM, ack_handler, &err);
	if (handler)
		nl_cb_set(cb, NL_CB_VALID, NL_CB_CUSTOM, handler, arg);

	while (err > 0)
		nl_recvmsgs(unl->sock, cb);

out:
	nlmsg_free(msg);
	nl_cb_put(cb);
	return err;
}
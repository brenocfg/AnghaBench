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
struct ipmi_user {int /*<<< orphan*/  handler_data; TYPE_1__* handler; } ;
struct ipmi_smi {int /*<<< orphan*/  (* null_user_handler ) (struct ipmi_smi*,struct ipmi_recv_msg*) ;} ;
struct ipmi_recv_msg {int /*<<< orphan*/  user; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* ipmi_recv_hndl ) (struct ipmi_recv_msg*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int EINVAL ; 
 struct ipmi_user* acquire_ipmi_user (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ipmi_free_recv_msg (struct ipmi_recv_msg*) ; 
 scalar_t__ oops_in_progress ; 
 int /*<<< orphan*/  release_ipmi_user (struct ipmi_user*,int) ; 
 int /*<<< orphan*/  stub1 (struct ipmi_smi*,struct ipmi_recv_msg*) ; 
 int /*<<< orphan*/  stub2 (struct ipmi_recv_msg*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int deliver_response(struct ipmi_smi *intf, struct ipmi_recv_msg *msg)
{
	int rv = 0;

	if (!msg->user) {
		/* Special handling for NULL users. */
		if (intf->null_user_handler) {
			intf->null_user_handler(intf, msg);
		} else {
			/* No handler, so give up. */
			rv = -EINVAL;
		}
		ipmi_free_recv_msg(msg);
	} else if (oops_in_progress) {
		/*
		 * If we are running in the panic context, calling the
		 * receive handler doesn't much meaning and has a deadlock
		 * risk.  At this moment, simply skip it in that case.
		 */
		ipmi_free_recv_msg(msg);
	} else {
		int index;
		struct ipmi_user *user = acquire_ipmi_user(msg->user, &index);

		if (user) {
			user->handler->ipmi_recv_hndl(msg, user->handler_data);
			release_ipmi_user(user, index);
		} else {
			/* User went away, give up. */
			ipmi_free_recv_msg(msg);
			rv = -EINVAL;
		}
	}

	return rv;
}
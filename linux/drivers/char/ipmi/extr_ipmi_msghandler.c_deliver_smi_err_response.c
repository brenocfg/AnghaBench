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
struct ipmi_smi_msg {int* rsp; int* data; int rsp_size; } ;
struct ipmi_smi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  handle_one_recv_msg (struct ipmi_smi*,struct ipmi_smi_msg*) ; 

__attribute__((used)) static void deliver_smi_err_response(struct ipmi_smi *intf,
				     struct ipmi_smi_msg *msg,
				     unsigned char err)
{
	msg->rsp[0] = msg->data[0] | 4;
	msg->rsp[1] = msg->data[1];
	msg->rsp[2] = err;
	msg->rsp_size = 3;
	/* It's an error, so it will never requeue, no need to check return. */
	handle_one_recv_msg(intf, msg);
}
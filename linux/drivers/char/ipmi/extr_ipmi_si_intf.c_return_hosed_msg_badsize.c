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
struct smi_info {struct ipmi_smi_msg* curr_msg; } ;
struct ipmi_smi_msg {int* rsp; int* data; int rsp_size; } ;

/* Variables and functions */
 int CANNOT_RETURN_REQUESTED_LENGTH ; 
 int /*<<< orphan*/  deliver_recv_msg (struct smi_info*,struct ipmi_smi_msg*) ; 

__attribute__((used)) static void return_hosed_msg_badsize(struct smi_info *smi_info)
{
	struct ipmi_smi_msg *msg = smi_info->curr_msg;

	/* Make it a response */
	msg->rsp[0] = msg->data[0] | 4;
	msg->rsp[1] = msg->data[1];
	msg->rsp[2] = CANNOT_RETURN_REQUESTED_LENGTH;
	msg->rsp_size = 3;
	smi_info->curr_msg = NULL;
	deliver_recv_msg(smi_info, msg);
}
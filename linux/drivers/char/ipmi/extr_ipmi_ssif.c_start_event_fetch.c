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
struct ssif_info {int req_events; int /*<<< orphan*/  ssif_state; struct ipmi_smi_msg* curr_msg; } ;
struct ipmi_smi_msg {int* data; int data_size; } ;

/* Variables and functions */
 int IPMI_NETFN_APP_REQUEST ; 
 int IPMI_READ_EVENT_MSG_BUFFER_CMD ; 
 int /*<<< orphan*/  SSIF_GETTING_EVENTS ; 
 int /*<<< orphan*/  SSIF_NORMAL ; 
 int /*<<< orphan*/  check_start_send (struct ssif_info*,unsigned long*,struct ipmi_smi_msg*) ; 
 struct ipmi_smi_msg* ipmi_alloc_smi_msg () ; 
 int /*<<< orphan*/  ipmi_ssif_unlock_cond (struct ssif_info*,unsigned long*) ; 

__attribute__((used)) static void start_event_fetch(struct ssif_info *ssif_info, unsigned long *flags)
{
	struct ipmi_smi_msg *msg;

	ssif_info->req_events = false;

	msg = ipmi_alloc_smi_msg();
	if (!msg) {
		ssif_info->ssif_state = SSIF_NORMAL;
		ipmi_ssif_unlock_cond(ssif_info, flags);
		return;
	}

	ssif_info->curr_msg = msg;
	ssif_info->ssif_state = SSIF_GETTING_EVENTS;
	ipmi_ssif_unlock_cond(ssif_info, flags);

	msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	msg->data[1] = IPMI_READ_EVENT_MSG_BUFFER_CMD;
	msg->data_size = 2;

	check_start_send(ssif_info, flags, msg);
}
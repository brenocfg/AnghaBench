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
struct smi_info {int /*<<< orphan*/  si_state; TYPE_1__* curr_msg; } ;
struct TYPE_2__ {int* data; int data_size; } ;

/* Variables and functions */
 int IPMI_NETFN_APP_REQUEST ; 
 int IPMI_READ_EVENT_MSG_BUFFER_CMD ; 
 int /*<<< orphan*/  SI_GETTING_EVENTS ; 
 int /*<<< orphan*/  start_new_msg (struct smi_info*,int*,int) ; 

__attribute__((used)) static void start_getting_events(struct smi_info *smi_info)
{
	smi_info->curr_msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	smi_info->curr_msg->data[1] = IPMI_READ_EVENT_MSG_BUFFER_CMD;
	smi_info->curr_msg->data_size = 2;

	start_new_msg(smi_info, smi_info->curr_msg->data,
		      smi_info->curr_msg->data_size);
	smi_info->si_state = SI_GETTING_EVENTS;
}
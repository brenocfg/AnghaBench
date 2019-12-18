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
struct ipmi_system_interface_addr {int lun; int /*<<< orphan*/  channel; int /*<<< orphan*/  addr_type; } ;
struct ipmi_smi_msg {int* rsp; scalar_t__ rsp_size; } ;
struct TYPE_2__ {int netfn; int cmd; scalar_t__ data_len; int /*<<< orphan*/  data; } ;
struct ipmi_recv_msg {TYPE_1__ msg; int /*<<< orphan*/  msg_data; int /*<<< orphan*/  recv_type; int /*<<< orphan*/  addr; scalar_t__ msgid; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPMI_ASYNC_EVENT_RECV_TYPE ; 
 int /*<<< orphan*/  IPMI_BMC_CHANNEL ; 
 int /*<<< orphan*/  IPMI_SYSTEM_INTERFACE_ADDR_TYPE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,scalar_t__) ; 

__attribute__((used)) static void copy_event_into_recv_msg(struct ipmi_recv_msg *recv_msg,
				     struct ipmi_smi_msg  *msg)
{
	struct ipmi_system_interface_addr *smi_addr;

	recv_msg->msgid = 0;
	smi_addr = (struct ipmi_system_interface_addr *) &recv_msg->addr;
	smi_addr->addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr->channel = IPMI_BMC_CHANNEL;
	smi_addr->lun = msg->rsp[0] & 3;
	recv_msg->recv_type = IPMI_ASYNC_EVENT_RECV_TYPE;
	recv_msg->msg.netfn = msg->rsp[0] >> 2;
	recv_msg->msg.cmd = msg->rsp[1];
	memcpy(recv_msg->msg_data, &msg->rsp[3], msg->rsp_size - 3);
	recv_msg->msg.data = recv_msg->msg_data;
	recv_msg->msg.data_len = msg->rsp_size - 3;
}
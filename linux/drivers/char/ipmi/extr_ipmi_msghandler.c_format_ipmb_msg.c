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
struct kernel_ipmi_msg {int netfn; unsigned char cmd; int /*<<< orphan*/  data_len; int /*<<< orphan*/  data; } ;
struct ipmi_smi_msg {int* data; int data_size; long msgid; } ;
struct ipmi_ipmb_addr {int channel; int slave_addr; int lun; } ;

/* Variables and functions */
 int IPMI_NETFN_APP_REQUEST ; 
 int IPMI_SEND_MSG_CMD ; 
 void* ipmb_checksum (int*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void format_ipmb_msg(struct ipmi_smi_msg   *smi_msg,
				   struct kernel_ipmi_msg *msg,
				   struct ipmi_ipmb_addr *ipmb_addr,
				   long                  msgid,
				   unsigned char         ipmb_seq,
				   int                   broadcast,
				   unsigned char         source_address,
				   unsigned char         source_lun)
{
	int i = broadcast;

	/* Format the IPMB header data. */
	smi_msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	smi_msg->data[1] = IPMI_SEND_MSG_CMD;
	smi_msg->data[2] = ipmb_addr->channel;
	if (broadcast)
		smi_msg->data[3] = 0;
	smi_msg->data[i+3] = ipmb_addr->slave_addr;
	smi_msg->data[i+4] = (msg->netfn << 2) | (ipmb_addr->lun & 0x3);
	smi_msg->data[i+5] = ipmb_checksum(&smi_msg->data[i + 3], 2);
	smi_msg->data[i+6] = source_address;
	smi_msg->data[i+7] = (ipmb_seq << 2) | source_lun;
	smi_msg->data[i+8] = msg->cmd;

	/* Now tack on the data to the message. */
	if (msg->data_len > 0)
		memcpy(&smi_msg->data[i + 9], msg->data, msg->data_len);
	smi_msg->data_size = msg->data_len + 9;

	/* Now calculate the checksum and tack it on. */
	smi_msg->data[i+smi_msg->data_size]
		= ipmb_checksum(&smi_msg->data[i + 6], smi_msg->data_size - 6);

	/*
	 * Add on the checksum size and the offset from the
	 * broadcast.
	 */
	smi_msg->data_size += 1 + i;

	smi_msg->msgid = msgid;
}
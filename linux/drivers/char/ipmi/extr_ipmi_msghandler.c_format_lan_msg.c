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
struct kernel_ipmi_msg {int netfn; unsigned char cmd; scalar_t__ data_len; int /*<<< orphan*/  data; } ;
struct ipmi_smi_msg {int* data; scalar_t__ data_size; long msgid; } ;
struct ipmi_lan_addr {int channel; int session_handle; int remote_SWID; int lun; int local_SWID; } ;

/* Variables and functions */
 int IPMI_NETFN_APP_REQUEST ; 
 int IPMI_SEND_MSG_CMD ; 
 void* ipmb_checksum (int*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void format_lan_msg(struct ipmi_smi_msg   *smi_msg,
				  struct kernel_ipmi_msg *msg,
				  struct ipmi_lan_addr  *lan_addr,
				  long                  msgid,
				  unsigned char         ipmb_seq,
				  unsigned char         source_lun)
{
	/* Format the IPMB header data. */
	smi_msg->data[0] = (IPMI_NETFN_APP_REQUEST << 2);
	smi_msg->data[1] = IPMI_SEND_MSG_CMD;
	smi_msg->data[2] = lan_addr->channel;
	smi_msg->data[3] = lan_addr->session_handle;
	smi_msg->data[4] = lan_addr->remote_SWID;
	smi_msg->data[5] = (msg->netfn << 2) | (lan_addr->lun & 0x3);
	smi_msg->data[6] = ipmb_checksum(&smi_msg->data[4], 2);
	smi_msg->data[7] = lan_addr->local_SWID;
	smi_msg->data[8] = (ipmb_seq << 2) | source_lun;
	smi_msg->data[9] = msg->cmd;

	/* Now tack on the data to the message. */
	if (msg->data_len > 0)
		memcpy(&smi_msg->data[10], msg->data, msg->data_len);
	smi_msg->data_size = msg->data_len + 10;

	/* Now calculate the checksum and tack it on. */
	smi_msg->data[smi_msg->data_size]
		= ipmb_checksum(&smi_msg->data[7], smi_msg->data_size - 7);

	/*
	 * Add on the checksum size and the offset from the
	 * broadcast.
	 */
	smi_msg->data_size += 1;

	smi_msg->msgid = msgid;
}
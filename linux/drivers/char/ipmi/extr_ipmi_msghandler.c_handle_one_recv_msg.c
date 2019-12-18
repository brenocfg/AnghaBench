#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipmi_smi_msg {int* rsp; int rsp_size; int data_size; int* data; struct ipmi_recv_msg* user_data; int /*<<< orphan*/  msgid; } ;
struct ipmi_smi {int /*<<< orphan*/  channel_list; int /*<<< orphan*/  channels_ready; int /*<<< orphan*/  si_dev; scalar_t__ in_shutdown; } ;
struct TYPE_3__ {int* data; int data_len; } ;
struct ipmi_recv_msg {int* msg_data; TYPE_1__ msg; int /*<<< orphan*/  recv_type; } ;
struct ipmi_channel {scalar_t__ medium; } ;
struct TYPE_4__ {struct ipmi_channel* c; } ;

/* Variables and functions */
 int IPMI_BUS_ERR ; 
#define  IPMI_CHANNEL_MEDIUM_8023LAN 130 
#define  IPMI_CHANNEL_MEDIUM_ASYNC 129 
#define  IPMI_CHANNEL_MEDIUM_IPMB 128 
 int IPMI_CHANNEL_MEDIUM_OEM_MAX ; 
 int IPMI_CHANNEL_MEDIUM_OEM_MIN ; 
 void* IPMI_ERR_UNSPECIFIED ; 
 int IPMI_GET_MSG_CMD ; 
 int IPMI_LOST_ARBITRATION_ERR ; 
 int IPMI_MAX_CHANNELS ; 
 int IPMI_NAK_ON_WRITE_ERR ; 
 int IPMI_NETFN_APP_REQUEST ; 
 int IPMI_NODE_BUSY_ERR ; 
 int IPMI_READ_EVENT_MSG_BUFFER_CMD ; 
 int /*<<< orphan*/  IPMI_RESPONSE_RESPONSE_TYPE ; 
 int IPMI_SEND_MSG_CMD ; 
 TYPE_2__* READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  deliver_local_response (struct ipmi_smi*,struct ipmi_recv_msg*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int,int,int,...) ; 
 int handle_bmc_rsp (struct ipmi_smi*,struct ipmi_smi_msg*) ; 
 int handle_ipmb_get_msg_cmd (struct ipmi_smi*,struct ipmi_smi_msg*) ; 
 int handle_ipmb_get_msg_rsp (struct ipmi_smi*,struct ipmi_smi_msg*) ; 
 int handle_lan_get_msg_cmd (struct ipmi_smi*,struct ipmi_smi_msg*) ; 
 int handle_lan_get_msg_rsp (struct ipmi_smi*,struct ipmi_smi_msg*) ; 
 int handle_oem_get_msg_cmd (struct ipmi_smi*,struct ipmi_smi_msg*) ; 
 int handle_read_event_rsp (struct ipmi_smi*,struct ipmi_smi_msg*) ; 
 int /*<<< orphan*/  intf_err_seq (struct ipmi_smi*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  intf_start_seq_timer (struct ipmi_smi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipmi_debug_msg (char*,int*,int) ; 
 int /*<<< orphan*/  ipmi_inc_stat (struct ipmi_smi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sent_ipmb_command_errs ; 
 int /*<<< orphan*/  sent_lan_command_errs ; 

__attribute__((used)) static int handle_one_recv_msg(struct ipmi_smi *intf,
			       struct ipmi_smi_msg *msg)
{
	int requeue;
	int chan;

	ipmi_debug_msg("Recv:", msg->rsp, msg->rsp_size);

	if ((msg->data_size >= 2)
	    && (msg->data[0] == (IPMI_NETFN_APP_REQUEST << 2))
	    && (msg->data[1] == IPMI_SEND_MSG_CMD)
	    && (msg->user_data == NULL)) {

		if (intf->in_shutdown)
			goto free_msg;

		/*
		 * This is the local response to a command send, start
		 * the timer for these.  The user_data will not be
		 * NULL if this is a response send, and we will let
		 * response sends just go through.
		 */

		/*
		 * Check for errors, if we get certain errors (ones
		 * that mean basically we can try again later), we
		 * ignore them and start the timer.  Otherwise we
		 * report the error immediately.
		 */
		if ((msg->rsp_size >= 3) && (msg->rsp[2] != 0)
		    && (msg->rsp[2] != IPMI_NODE_BUSY_ERR)
		    && (msg->rsp[2] != IPMI_LOST_ARBITRATION_ERR)
		    && (msg->rsp[2] != IPMI_BUS_ERR)
		    && (msg->rsp[2] != IPMI_NAK_ON_WRITE_ERR)) {
			int ch = msg->rsp[3] & 0xf;
			struct ipmi_channel *chans;

			/* Got an error sending the message, handle it. */

			chans = READ_ONCE(intf->channel_list)->c;
			if ((chans[ch].medium == IPMI_CHANNEL_MEDIUM_8023LAN)
			    || (chans[ch].medium == IPMI_CHANNEL_MEDIUM_ASYNC))
				ipmi_inc_stat(intf, sent_lan_command_errs);
			else
				ipmi_inc_stat(intf, sent_ipmb_command_errs);
			intf_err_seq(intf, msg->msgid, msg->rsp[2]);
		} else
			/* The message was sent, start the timer. */
			intf_start_seq_timer(intf, msg->msgid);
free_msg:
		requeue = 0;
		goto out;

	} else if (msg->rsp_size < 2) {
		/* Message is too small to be correct. */
		dev_warn(intf->si_dev,
			 "BMC returned too small a message for netfn %x cmd %x, got %d bytes\n",
			 (msg->data[0] >> 2) | 1, msg->data[1], msg->rsp_size);

		/* Generate an error response for the message. */
		msg->rsp[0] = msg->data[0] | (1 << 2);
		msg->rsp[1] = msg->data[1];
		msg->rsp[2] = IPMI_ERR_UNSPECIFIED;
		msg->rsp_size = 3;
	} else if (((msg->rsp[0] >> 2) != ((msg->data[0] >> 2) | 1))
		   || (msg->rsp[1] != msg->data[1])) {
		/*
		 * The NetFN and Command in the response is not even
		 * marginally correct.
		 */
		dev_warn(intf->si_dev,
			 "BMC returned incorrect response, expected netfn %x cmd %x, got netfn %x cmd %x\n",
			 (msg->data[0] >> 2) | 1, msg->data[1],
			 msg->rsp[0] >> 2, msg->rsp[1]);

		/* Generate an error response for the message. */
		msg->rsp[0] = msg->data[0] | (1 << 2);
		msg->rsp[1] = msg->data[1];
		msg->rsp[2] = IPMI_ERR_UNSPECIFIED;
		msg->rsp_size = 3;
	}

	if ((msg->rsp[0] == ((IPMI_NETFN_APP_REQUEST|1) << 2))
	    && (msg->rsp[1] == IPMI_SEND_MSG_CMD)
	    && (msg->user_data != NULL)) {
		/*
		 * It's a response to a response we sent.  For this we
		 * deliver a send message response to the user.
		 */
		struct ipmi_recv_msg *recv_msg = msg->user_data;

		requeue = 0;
		if (msg->rsp_size < 2)
			/* Message is too small to be correct. */
			goto out;

		chan = msg->data[2] & 0x0f;
		if (chan >= IPMI_MAX_CHANNELS)
			/* Invalid channel number */
			goto out;

		if (!recv_msg)
			goto out;

		recv_msg->recv_type = IPMI_RESPONSE_RESPONSE_TYPE;
		recv_msg->msg.data = recv_msg->msg_data;
		recv_msg->msg.data_len = 1;
		recv_msg->msg_data[0] = msg->rsp[2];
		deliver_local_response(intf, recv_msg);
	} else if ((msg->rsp[0] == ((IPMI_NETFN_APP_REQUEST|1) << 2))
		   && (msg->rsp[1] == IPMI_GET_MSG_CMD)) {
		struct ipmi_channel   *chans;

		/* It's from the receive queue. */
		chan = msg->rsp[3] & 0xf;
		if (chan >= IPMI_MAX_CHANNELS) {
			/* Invalid channel number */
			requeue = 0;
			goto out;
		}

		/*
		 * We need to make sure the channels have been initialized.
		 * The channel_handler routine will set the "curr_channel"
		 * equal to or greater than IPMI_MAX_CHANNELS when all the
		 * channels for this interface have been initialized.
		 */
		if (!intf->channels_ready) {
			requeue = 0; /* Throw the message away */
			goto out;
		}

		chans = READ_ONCE(intf->channel_list)->c;

		switch (chans[chan].medium) {
		case IPMI_CHANNEL_MEDIUM_IPMB:
			if (msg->rsp[4] & 0x04) {
				/*
				 * It's a response, so find the
				 * requesting message and send it up.
				 */
				requeue = handle_ipmb_get_msg_rsp(intf, msg);
			} else {
				/*
				 * It's a command to the SMS from some other
				 * entity.  Handle that.
				 */
				requeue = handle_ipmb_get_msg_cmd(intf, msg);
			}
			break;

		case IPMI_CHANNEL_MEDIUM_8023LAN:
		case IPMI_CHANNEL_MEDIUM_ASYNC:
			if (msg->rsp[6] & 0x04) {
				/*
				 * It's a response, so find the
				 * requesting message and send it up.
				 */
				requeue = handle_lan_get_msg_rsp(intf, msg);
			} else {
				/*
				 * It's a command to the SMS from some other
				 * entity.  Handle that.
				 */
				requeue = handle_lan_get_msg_cmd(intf, msg);
			}
			break;

		default:
			/* Check for OEM Channels.  Clients had better
			   register for these commands. */
			if ((chans[chan].medium >= IPMI_CHANNEL_MEDIUM_OEM_MIN)
			    && (chans[chan].medium
				<= IPMI_CHANNEL_MEDIUM_OEM_MAX)) {
				requeue = handle_oem_get_msg_cmd(intf, msg);
			} else {
				/*
				 * We don't handle the channel type, so just
				 * free the message.
				 */
				requeue = 0;
			}
		}

	} else if ((msg->rsp[0] == ((IPMI_NETFN_APP_REQUEST|1) << 2))
		   && (msg->rsp[1] == IPMI_READ_EVENT_MSG_BUFFER_CMD)) {
		/* It's an asynchronous event. */
		requeue = handle_read_event_rsp(intf, msg);
	} else {
		/* It's a response from the local BMC. */
		requeue = handle_bmc_rsp(intf, msg);
	}

 out:
	return requeue;
}
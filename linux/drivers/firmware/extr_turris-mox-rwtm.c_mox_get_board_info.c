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
typedef  int u32 ;
struct armada_37xx_rwtm_rx_msg {int* status; int /*<<< orphan*/  retval; } ;
struct mox_rwtm {int serial_number; int board_version; int ram_size; int has_board_info; int has_pubkey; int /*<<< orphan*/  pubkey; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmd_done; int /*<<< orphan*/  mbox; int /*<<< orphan*/  mac_address2; int /*<<< orphan*/  mac_address1; struct armada_37xx_rwtm_rx_msg reply; } ;
struct armada_37xx_rwtm_tx_msg {void* command; } ;

/* Variables and functions */
 int ENODATA ; 
 int HZ ; 
 void* MBOX_CMD_BOARD_INFO ; 
 void* MBOX_CMD_ECDSA_PUB_KEY ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int mbox_send_message (int /*<<< orphan*/ ,struct armada_37xx_rwtm_tx_msg*) ; 
 int mox_get_status (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  reply_to_mac_addr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int) ; 
 int wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mox_get_board_info(struct mox_rwtm *rwtm)
{
	struct armada_37xx_rwtm_tx_msg msg;
	struct armada_37xx_rwtm_rx_msg *reply = &rwtm->reply;
	int ret;

	msg.command = MBOX_CMD_BOARD_INFO;
	ret = mbox_send_message(rwtm->mbox, &msg);
	if (ret < 0)
		return ret;

	ret = wait_for_completion_timeout(&rwtm->cmd_done, HZ / 2);
	if (ret < 0)
		return ret;

	ret = mox_get_status(MBOX_CMD_BOARD_INFO, reply->retval);
	if (ret < 0 && ret != -ENODATA) {
		return ret;
	} else if (ret == -ENODATA) {
		dev_warn(rwtm->dev,
			 "Board does not have manufacturing information burned!\n");
	} else {
		rwtm->serial_number = reply->status[1];
		rwtm->serial_number <<= 32;
		rwtm->serial_number |= reply->status[0];
			rwtm->board_version = reply->status[2];
		rwtm->ram_size = reply->status[3];
		reply_to_mac_addr(rwtm->mac_address1, reply->status[4],
				  reply->status[5]);
		reply_to_mac_addr(rwtm->mac_address2, reply->status[6],
				  reply->status[7]);
		rwtm->has_board_info = 1;

		pr_info("Turris Mox serial number %016llX\n",
			rwtm->serial_number);
		pr_info("           board version %i\n", rwtm->board_version);
		pr_info("           burned RAM size %i MiB\n", rwtm->ram_size);
	}

	msg.command = MBOX_CMD_ECDSA_PUB_KEY;
	ret = mbox_send_message(rwtm->mbox, &msg);
	if (ret < 0)
		return ret;

	ret = wait_for_completion_timeout(&rwtm->cmd_done, HZ / 2);
	if (ret < 0)
		return ret;

	ret = mox_get_status(MBOX_CMD_ECDSA_PUB_KEY, reply->retval);
	if (ret < 0 && ret != -ENODATA) {
		return ret;
	} else if (ret == -ENODATA) {
		dev_warn(rwtm->dev, "Board has no public key burned!\n");
	} else {
		u32 *s = reply->status;

		rwtm->has_pubkey = 1;
		sprintf(rwtm->pubkey,
			"%06x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x%08x",
			ret, s[0], s[1], s[2], s[3], s[4], s[5], s[6], s[7],
			s[8], s[9], s[10], s[11], s[12], s[13], s[14], s[15]);
	}

	return 0;
}
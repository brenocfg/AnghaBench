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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct sk_buff {int dummy; } ;
struct hci_dev {int dummy; } ;
struct hci_command_hdr {size_t plen; int /*<<< orphan*/  opcode; } ;
struct firmware {size_t size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int,size_t,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 

int btbcm_patchram(struct hci_dev *hdev, const struct firmware *fw)
{
	const struct hci_command_hdr *cmd;
	const u8 *fw_ptr;
	size_t fw_size;
	struct sk_buff *skb;
	u16 opcode;
	int err = 0;

	/* Start Download */
	skb = __hci_cmd_sync(hdev, 0xfc2e, 0, NULL, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		err = PTR_ERR(skb);
		bt_dev_err(hdev, "BCM: Download Minidrv command failed (%d)",
			   err);
		goto done;
	}
	kfree_skb(skb);

	/* 50 msec delay after Download Minidrv completes */
	msleep(50);

	fw_ptr = fw->data;
	fw_size = fw->size;

	while (fw_size >= sizeof(*cmd)) {
		const u8 *cmd_param;

		cmd = (struct hci_command_hdr *)fw_ptr;
		fw_ptr += sizeof(*cmd);
		fw_size -= sizeof(*cmd);

		if (fw_size < cmd->plen) {
			bt_dev_err(hdev, "BCM: Patch is corrupted");
			err = -EINVAL;
			goto done;
		}

		cmd_param = fw_ptr;
		fw_ptr += cmd->plen;
		fw_size -= cmd->plen;

		opcode = le16_to_cpu(cmd->opcode);

		skb = __hci_cmd_sync(hdev, opcode, cmd->plen, cmd_param,
				     HCI_INIT_TIMEOUT);
		if (IS_ERR(skb)) {
			err = PTR_ERR(skb);
			bt_dev_err(hdev, "BCM: Patch command %04x failed (%d)",
				   opcode, err);
			goto done;
		}
		kfree_skb(skb);
	}

	/* 250 msec delay after Launch Ram completes */
	msleep(250);

done:
	return err;
}
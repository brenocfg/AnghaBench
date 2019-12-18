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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sk_buff {int dummy; } ;
struct hci_dev {int dummy; } ;
struct ath_vendor_cmd {size_t len; int /*<<< orphan*/  data; int /*<<< orphan*/  index; int /*<<< orphan*/  opcode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int,size_t,struct ath_vendor_cmd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 

__attribute__((used)) static int ath_vendor_cmd(struct hci_dev *hdev, uint8_t opcode, uint16_t index,
			  const void *data, size_t dlen)
{
	struct sk_buff *skb;
	struct ath_vendor_cmd cmd;

	if (dlen > sizeof(cmd.data))
		return -EINVAL;

	cmd.opcode = opcode;
	cmd.index = cpu_to_le16(index);
	cmd.len = dlen;
	memcpy(cmd.data, data, dlen);

	skb = __hci_cmd_sync(hdev, 0xfc0b, dlen + 4, &cmd, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb))
		return PTR_ERR(skb);
	kfree_skb(skb);

	return 0;
}
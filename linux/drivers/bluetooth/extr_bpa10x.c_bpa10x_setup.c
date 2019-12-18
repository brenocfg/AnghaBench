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
typedef  int u8 ;
struct sk_buff {scalar_t__ data; } ;
struct hci_dev {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int,int,int const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,char*) ; 
 int /*<<< orphan*/  hci_set_fw_info (struct hci_dev*,char*,scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static int bpa10x_setup(struct hci_dev *hdev)
{
	static const u8 req[] = { 0x07 };
	struct sk_buff *skb;

	BT_DBG("%s", hdev->name);

	/* Read revision string */
	skb = __hci_cmd_sync(hdev, 0xfc0e, sizeof(req), req, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	bt_dev_info(hdev, "%s", (char *)(skb->data + 1));

	hci_set_fw_info(hdev, "%s", skb->data + 1);

	kfree_skb(skb);
	return 0;
}
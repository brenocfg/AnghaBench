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
struct sk_buff {int dummy; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int) ; 
 int /*<<< orphan*/  btintel_set_event_mask (struct hci_dev*,int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

int btintel_set_diag(struct hci_dev *hdev, bool enable)
{
	struct sk_buff *skb;
	u8 param[3];
	int err;

	if (enable) {
		param[0] = 0x03;
		param[1] = 0x03;
		param[2] = 0x03;
	} else {
		param[0] = 0x00;
		param[1] = 0x00;
		param[2] = 0x00;
	}

	skb = __hci_cmd_sync(hdev, 0xfc43, 3, param, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		err = PTR_ERR(skb);
		if (err == -ENODATA)
			goto done;
		bt_dev_err(hdev, "Changing Intel diagnostic mode failed (%d)",
			   err);
		return err;
	}
	kfree_skb(skb);

done:
	btintel_set_event_mask(hdev, enable);
	return 0;
}
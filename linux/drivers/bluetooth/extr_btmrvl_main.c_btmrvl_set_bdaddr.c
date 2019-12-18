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
struct hci_dev {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  bdaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT_CMD_SET_BDADDR ; 
 int /*<<< orphan*/  BT_ERR (char*,int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int MRVL_VENDOR_PKT ; 
 long PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int btmrvl_set_bdaddr(struct hci_dev *hdev, const bdaddr_t *bdaddr)
{
	struct sk_buff *skb;
	long ret;
	u8 buf[8];

	buf[0] = MRVL_VENDOR_PKT;
	buf[1] = sizeof(bdaddr_t);
	memcpy(buf + 2, bdaddr, sizeof(bdaddr_t));

	skb = __hci_cmd_sync(hdev, BT_CMD_SET_BDADDR, sizeof(buf), buf,
			     HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		ret = PTR_ERR(skb);
		BT_ERR("%s: changing btmrvl device address failed (%ld)",
		       hdev->name, ret);
		return ret;
	}
	kfree_skb(skb);

	return 0;
}
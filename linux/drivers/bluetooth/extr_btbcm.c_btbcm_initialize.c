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
typedef  int u16 ;
struct sk_buff {scalar_t__ data; } ;
struct hci_rp_read_local_version {int /*<<< orphan*/  lmp_subver; int /*<<< orphan*/  hci_rev; } ;
struct hci_dev {scalar_t__ bus; } ;
struct bcm_subver_table {char* name; int subver; } ;

/* Variables and functions */
 scalar_t__ HCI_USB ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct bcm_subver_table* bcm_uart_subver_table ; 
 struct bcm_subver_table* bcm_usb_subver_table ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,char const*,int,int,int,int) ; 
 int btbcm_read_info (struct hci_dev*) ; 
 struct sk_buff* btbcm_read_local_version (struct hci_dev*) ; 
 struct sk_buff* btbcm_read_usb_product (struct hci_dev*) ; 
 int btbcm_reset (struct hci_dev*) ; 
 int get_unaligned_le16 (scalar_t__) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char const*,...) ; 

int btbcm_initialize(struct hci_dev *hdev, char *fw_name, size_t len,
		     bool reinit)
{
	u16 subver, rev, pid, vid;
	const char *hw_name = "BCM";
	struct sk_buff *skb;
	struct hci_rp_read_local_version *ver;
	const struct bcm_subver_table *bcm_subver_table;
	int i, err;

	/* Reset */
	err = btbcm_reset(hdev);
	if (err)
		return err;

	/* Read Local Version Info */
	skb = btbcm_read_local_version(hdev);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	ver = (struct hci_rp_read_local_version *)skb->data;
	rev = le16_to_cpu(ver->hci_rev);
	subver = le16_to_cpu(ver->lmp_subver);
	kfree_skb(skb);

	/* Read controller information */
	if (!reinit) {
		err = btbcm_read_info(hdev);
		if (err)
			return err;
	}

	/* Upper nibble of rev should be between 0 and 3? */
	if (((rev & 0xf000) >> 12) > 3)
		return 0;

	bcm_subver_table = (hdev->bus == HCI_USB) ? bcm_usb_subver_table :
						    bcm_uart_subver_table;

	for (i = 0; bcm_subver_table[i].name; i++) {
		if (subver == bcm_subver_table[i].subver) {
			hw_name = bcm_subver_table[i].name;
			break;
		}
	}

	if (hdev->bus == HCI_USB) {
		/* Read USB Product Info */
		skb = btbcm_read_usb_product(hdev);
		if (IS_ERR(skb))
			return PTR_ERR(skb);

		vid = get_unaligned_le16(skb->data + 1);
		pid = get_unaligned_le16(skb->data + 3);
		kfree_skb(skb);

		snprintf(fw_name, len, "brcm/%s-%4.4x-%4.4x.hcd",
			 hw_name, vid, pid);
	} else {
		snprintf(fw_name, len, "brcm/%s.hcd", hw_name);
	}

	bt_dev_info(hdev, "%s (%3.3u.%3.3u.%3.3u) build %4.4u",
		    hw_name, (subver & 0xe000) >> 13,
		    (subver & 0x1f00) >> 8, (subver & 0x00ff), rev & 0x0fff);

	return 0;
}
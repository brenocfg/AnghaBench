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
struct sk_buff {char** data; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  bt_dev_info (struct hci_dev*,char*,char*) ; 
 struct sk_buff* btbcm_read_controller_features (struct hci_dev*) ; 
 struct sk_buff* btbcm_read_local_name (struct hci_dev*) ; 
 struct sk_buff* btbcm_read_verbose_config (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 

__attribute__((used)) static int btbcm_read_info(struct hci_dev *hdev)
{
	struct sk_buff *skb;

	/* Read Verbose Config Version Info */
	skb = btbcm_read_verbose_config(hdev);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	bt_dev_info(hdev, "BCM: chip id %u", skb->data[1]);
	kfree_skb(skb);

	/* Read Controller Features */
	skb = btbcm_read_controller_features(hdev);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	bt_dev_info(hdev, "BCM: features 0x%2.2x", skb->data[1]);
	kfree_skb(skb);

	/* Read Local Name */
	skb = btbcm_read_local_name(hdev);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	bt_dev_info(hdev, "%s", (char *)(skb->data + 1));
	kfree_skb(skb);

	return 0;
}
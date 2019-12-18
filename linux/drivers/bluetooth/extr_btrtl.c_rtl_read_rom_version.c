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
struct sk_buff {int len; scalar_t__ data; } ;
struct rtl_rom_version_evt {int /*<<< orphan*/  version; int /*<<< orphan*/  status; } ;
struct hci_dev {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HCI_INIT_TIMEOUT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 struct sk_buff* __hci_cmd_sync (struct hci_dev*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  rtl_dev_err (struct hci_dev*,char*,...) ; 
 int /*<<< orphan*/  rtl_dev_info (struct hci_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl_read_rom_version(struct hci_dev *hdev, u8 *version)
{
	struct rtl_rom_version_evt *rom_version;
	struct sk_buff *skb;

	/* Read RTL ROM version command */
	skb = __hci_cmd_sync(hdev, 0xfc6d, 0, NULL, HCI_INIT_TIMEOUT);
	if (IS_ERR(skb)) {
		rtl_dev_err(hdev, "Read ROM version failed (%ld)",
			    PTR_ERR(skb));
		return PTR_ERR(skb);
	}

	if (skb->len != sizeof(*rom_version)) {
		rtl_dev_err(hdev, "version event length mismatch");
		kfree_skb(skb);
		return -EIO;
	}

	rom_version = (struct rtl_rom_version_evt *)skb->data;
	rtl_dev_info(hdev, "rom_version status=%x version=%x",
		     rom_version->status, rom_version->version);

	*version = rom_version->version;

	kfree_skb(skb);
	return 0;
}
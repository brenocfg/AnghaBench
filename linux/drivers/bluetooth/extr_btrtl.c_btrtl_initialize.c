#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ data; } ;
struct hci_rp_read_local_version {int /*<<< orphan*/  lmp_subver; int /*<<< orphan*/  hci_rev; int /*<<< orphan*/  hci_ver; int /*<<< orphan*/  lmp_ver; } ;
struct hci_dev {int /*<<< orphan*/  bus; } ;
struct btrtl_device_info {int fw_len; int cfg_len; TYPE_1__* ic_info; int /*<<< orphan*/  cfg_data; int /*<<< orphan*/  fw_data; int /*<<< orphan*/  rom_version; } ;
typedef  int /*<<< orphan*/  cfg_name ;
struct TYPE_2__ {char* fw_name; char* cfg_name; scalar_t__ config_needed; scalar_t__ has_rom_version; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct btrtl_device_info* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  btrtl_free (struct btrtl_device_info*) ; 
 TYPE_1__* btrtl_match_ic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sk_buff* btrtl_read_local_version (struct hci_dev*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct btrtl_device_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl_dev_err (struct hci_dev*,char*,char*) ; 
 int /*<<< orphan*/  rtl_dev_info (struct hci_dev*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 void* rtl_load_file (struct hci_dev*,char*,int /*<<< orphan*/ *) ; 
 int rtl_read_rom_version (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 

struct btrtl_device_info *btrtl_initialize(struct hci_dev *hdev,
					   const char *postfix)
{
	struct btrtl_device_info *btrtl_dev;
	struct sk_buff *skb;
	struct hci_rp_read_local_version *resp;
	char cfg_name[40];
	u16 hci_rev, lmp_subver;
	u8 hci_ver;
	int ret;

	btrtl_dev = kzalloc(sizeof(*btrtl_dev), GFP_KERNEL);
	if (!btrtl_dev) {
		ret = -ENOMEM;
		goto err_alloc;
	}

	skb = btrtl_read_local_version(hdev);
	if (IS_ERR(skb)) {
		ret = PTR_ERR(skb);
		goto err_free;
	}

	resp = (struct hci_rp_read_local_version *)skb->data;
	rtl_dev_info(hdev, "examining hci_ver=%02x hci_rev=%04x lmp_ver=%02x lmp_subver=%04x",
		     resp->hci_ver, resp->hci_rev,
		     resp->lmp_ver, resp->lmp_subver);

	hci_ver = resp->hci_ver;
	hci_rev = le16_to_cpu(resp->hci_rev);
	lmp_subver = le16_to_cpu(resp->lmp_subver);
	kfree_skb(skb);

	btrtl_dev->ic_info = btrtl_match_ic(lmp_subver, hci_rev, hci_ver,
					    hdev->bus);

	if (!btrtl_dev->ic_info) {
		rtl_dev_info(hdev, "unknown IC info, lmp subver %04x, hci rev %04x, hci ver %04x",
			    lmp_subver, hci_rev, hci_ver);
		return btrtl_dev;
	}

	if (btrtl_dev->ic_info->has_rom_version) {
		ret = rtl_read_rom_version(hdev, &btrtl_dev->rom_version);
		if (ret)
			goto err_free;
	}

	btrtl_dev->fw_len = rtl_load_file(hdev, btrtl_dev->ic_info->fw_name,
					  &btrtl_dev->fw_data);
	if (btrtl_dev->fw_len < 0) {
		rtl_dev_err(hdev, "firmware file %s not found",
			    btrtl_dev->ic_info->fw_name);
		ret = btrtl_dev->fw_len;
		goto err_free;
	}

	if (btrtl_dev->ic_info->cfg_name) {
		if (postfix) {
			snprintf(cfg_name, sizeof(cfg_name), "%s-%s.bin",
				 btrtl_dev->ic_info->cfg_name, postfix);
		} else {
			snprintf(cfg_name, sizeof(cfg_name), "%s.bin",
				 btrtl_dev->ic_info->cfg_name);
		}
		btrtl_dev->cfg_len = rtl_load_file(hdev, cfg_name,
						   &btrtl_dev->cfg_data);
		if (btrtl_dev->ic_info->config_needed &&
		    btrtl_dev->cfg_len <= 0) {
			rtl_dev_err(hdev, "mandatory config file %s not found",
				    btrtl_dev->ic_info->cfg_name);
			ret = btrtl_dev->cfg_len;
			goto err_free;
		}
	}

	return btrtl_dev;

err_free:
	btrtl_free(btrtl_dev);
err_alloc:
	return ERR_PTR(ret);
}
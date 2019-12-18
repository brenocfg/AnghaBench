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
typedef  unsigned char u8 ;
struct hci_dev {int dummy; } ;
struct btrtl_device_info {int cfg_len; unsigned char* cfg_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  rtl_dev_info (struct hci_dev*,char*,int,int) ; 
 int rtl_download_firmware (struct hci_dev*,unsigned char*,int) ; 
 int rtlbt_parse_firmware (struct hci_dev*,struct btrtl_device_info*,unsigned char**) ; 

__attribute__((used)) static int btrtl_setup_rtl8723b(struct hci_dev *hdev,
				struct btrtl_device_info *btrtl_dev)
{
	unsigned char *fw_data = NULL;
	int ret;
	u8 *tbuff;

	ret = rtlbt_parse_firmware(hdev, btrtl_dev, &fw_data);
	if (ret < 0)
		goto out;

	if (btrtl_dev->cfg_len > 0) {
		tbuff = kzalloc(ret + btrtl_dev->cfg_len, GFP_KERNEL);
		if (!tbuff) {
			ret = -ENOMEM;
			goto out;
		}

		memcpy(tbuff, fw_data, ret);
		kfree(fw_data);

		memcpy(tbuff + ret, btrtl_dev->cfg_data, btrtl_dev->cfg_len);
		ret += btrtl_dev->cfg_len;

		fw_data = tbuff;
	}

	rtl_dev_info(hdev, "cfg_sz %d, total sz %d", btrtl_dev->cfg_len, ret);

	ret = rtl_download_firmware(hdev, fw_data, ret);

out:
	kfree(fw_data);
	return ret;
}
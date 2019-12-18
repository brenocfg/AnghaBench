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
struct hci_dev {int dummy; } ;
struct btrtl_device_info {int fw_len; int /*<<< orphan*/  fw_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RTL_EPATCH_SIGNATURE ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_dev_err (struct hci_dev*,char*) ; 
 int rtl_download_firmware (struct hci_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int btrtl_setup_rtl8723a(struct hci_dev *hdev,
				struct btrtl_device_info *btrtl_dev)
{
	if (btrtl_dev->fw_len < 8)
		return -EINVAL;

	/* Check that the firmware doesn't have the epatch signature
	 * (which is only for RTL8723B and newer).
	 */
	if (!memcmp(btrtl_dev->fw_data, RTL_EPATCH_SIGNATURE, 8)) {
		rtl_dev_err(hdev, "unexpected EPATCH signature!");
		return -EINVAL;
	}

	return rtl_download_firmware(hdev, btrtl_dev->fw_data,
				     btrtl_dev->fw_len);
}
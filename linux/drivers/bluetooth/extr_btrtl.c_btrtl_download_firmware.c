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
struct hci_dev {int dummy; } ;
struct btrtl_device_info {TYPE_1__* ic_info; } ;
struct TYPE_2__ {int lmp_subver; } ;

/* Variables and functions */
#define  RTL_ROM_LMP_3499 133 
#define  RTL_ROM_LMP_8723A 132 
#define  RTL_ROM_LMP_8723B 131 
#define  RTL_ROM_LMP_8761A 130 
#define  RTL_ROM_LMP_8821A 129 
#define  RTL_ROM_LMP_8822B 128 
 int btrtl_setup_rtl8723a (struct hci_dev*,struct btrtl_device_info*) ; 
 int btrtl_setup_rtl8723b (struct hci_dev*,struct btrtl_device_info*) ; 
 int /*<<< orphan*/  rtl_dev_info (struct hci_dev*,char*) ; 

int btrtl_download_firmware(struct hci_dev *hdev,
			    struct btrtl_device_info *btrtl_dev)
{
	/* Match a set of subver values that correspond to stock firmware,
	 * which is not compatible with standard btusb.
	 * If matched, upload an alternative firmware that does conform to
	 * standard btusb. Once that firmware is uploaded, the subver changes
	 * to a different value.
	 */
	if (!btrtl_dev->ic_info) {
		rtl_dev_info(hdev, "assuming no firmware upload needed");
		return 0;
	}

	switch (btrtl_dev->ic_info->lmp_subver) {
	case RTL_ROM_LMP_8723A:
	case RTL_ROM_LMP_3499:
		return btrtl_setup_rtl8723a(hdev, btrtl_dev);
	case RTL_ROM_LMP_8723B:
	case RTL_ROM_LMP_8821A:
	case RTL_ROM_LMP_8761A:
	case RTL_ROM_LMP_8822B:
		return btrtl_setup_rtl8723b(hdev, btrtl_dev);
	default:
		rtl_dev_info(hdev, "assuming no firmware upload needed");
		return 0;
	}
}
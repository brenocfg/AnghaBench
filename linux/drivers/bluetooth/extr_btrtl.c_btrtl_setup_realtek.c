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
struct hci_dev {int /*<<< orphan*/  quirks; } ;
struct btrtl_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HCI_QUIRK_SIMULTANEOUS_DISCOVERY ; 
 scalar_t__ IS_ERR (struct btrtl_device_info*) ; 
 int PTR_ERR (struct btrtl_device_info*) ; 
 int btrtl_download_firmware (struct hci_dev*,struct btrtl_device_info*) ; 
 int /*<<< orphan*/  btrtl_free (struct btrtl_device_info*) ; 
 struct btrtl_device_info* btrtl_initialize (struct hci_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrtl_setup_realtek(struct hci_dev *hdev)
{
	struct btrtl_device_info *btrtl_dev;
	int ret;

	btrtl_dev = btrtl_initialize(hdev, NULL);
	if (IS_ERR(btrtl_dev))
		return PTR_ERR(btrtl_dev);

	ret = btrtl_download_firmware(hdev, btrtl_dev);

	btrtl_free(btrtl_dev);

	/* Enable controller to do both LE scan and BR/EDR inquiry
	 * simultaneously.
	 */
	set_bit(HCI_QUIRK_SIMULTANEOUS_DISCOVERY, &hdev->quirks);

	return ret;
}
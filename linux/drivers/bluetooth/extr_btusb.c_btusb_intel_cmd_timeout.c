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
struct gpio_desc {int dummy; } ;
struct btusb_data {int cmd_timeout_cnt; int /*<<< orphan*/  flags; struct gpio_desc* reset_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTUSB_HW_RESET_ACTIVE ; 
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (struct gpio_desc*,int) ; 
 struct btusb_data* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void btusb_intel_cmd_timeout(struct hci_dev *hdev)
{
	struct btusb_data *data = hci_get_drvdata(hdev);
	struct gpio_desc *reset_gpio = data->reset_gpio;

	if (++data->cmd_timeout_cnt < 5)
		return;

	if (!reset_gpio) {
		bt_dev_err(hdev, "No way to reset. Ignoring and continuing");
		return;
	}

	/*
	 * Toggle the hard reset line if the platform provides one. The reset
	 * is going to yank the device off the USB and then replug. So doing
	 * once is enough. The cleanup is handled correctly on the way out
	 * (standard USB disconnect), and the new device is detected cleanly
	 * and bound to the driver again like it should be.
	 */
	if (test_and_set_bit(BTUSB_HW_RESET_ACTIVE, &data->flags)) {
		bt_dev_err(hdev, "last reset failed? Not resetting again");
		return;
	}

	bt_dev_err(hdev, "Initiating HW reset via gpio");
	gpiod_set_value_cansleep(reset_gpio, 1);
	msleep(100);
	gpiod_set_value_cansleep(reset_gpio, 0);
}
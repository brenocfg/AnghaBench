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
struct hci_uart {int /*<<< orphan*/  hdev; scalar_t__ serdev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bt_dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hci_uart_set_baudrate (struct hci_uart*,int) ; 
 int /*<<< orphan*/  hci_uart_set_flow_control (struct hci_uart*,int) ; 
 int /*<<< orphan*/  hci_uart_wait_until_sent (struct hci_uart*) ; 
 int mrvl_load_firmware (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  serdev_device_set_baudrate (scalar_t__,int) ; 

__attribute__((used)) static int mrvl_setup(struct hci_uart *hu)
{
	int err;

	hci_uart_set_flow_control(hu, true);

	err = mrvl_load_firmware(hu->hdev, "mrvl/helper_uart_3000000.bin");
	if (err) {
		bt_dev_err(hu->hdev, "Unable to download firmware helper");
		return -EINVAL;
	}

	/* Let the final ack go out before switching the baudrate */
	hci_uart_wait_until_sent(hu);

	if (hu->serdev)
		serdev_device_set_baudrate(hu->serdev, 3000000);
	else
		hci_uart_set_baudrate(hu, 3000000);

	hci_uart_set_flow_control(hu, false);

	err = mrvl_load_firmware(hu->hdev, "mrvl/uart8897_bt.bin");
	if (err)
		return err;

	return 0;
}
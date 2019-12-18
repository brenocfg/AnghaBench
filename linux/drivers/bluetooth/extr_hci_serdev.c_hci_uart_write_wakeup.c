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
struct serdev_device {int dummy; } ;
struct hci_uart {int /*<<< orphan*/  flags; struct serdev_device* serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*) ; 
 int /*<<< orphan*/  HCI_UART_PROTO_READY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  hci_uart_tx_wakeup (struct hci_uart*) ; 
 struct hci_uart* serdev_device_get_drvdata (struct serdev_device*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hci_uart_write_wakeup(struct serdev_device *serdev)
{
	struct hci_uart *hu = serdev_device_get_drvdata(serdev);

	BT_DBG("");

	if (!hu || serdev != hu->serdev) {
		WARN_ON(1);
		return;
	}

	if (test_bit(HCI_UART_PROTO_READY, &hu->flags))
		hci_uart_tx_wakeup(hu);
}
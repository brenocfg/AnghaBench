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
struct nokia_bt_dev {int /*<<< orphan*/  hu; } ;

/* Variables and functions */
 int /*<<< orphan*/  hci_uart_unregister_device (int /*<<< orphan*/ *) ; 
 struct nokia_bt_dev* serdev_device_get_drvdata (struct serdev_device*) ; 

__attribute__((used)) static void nokia_bluetooth_serdev_remove(struct serdev_device *serdev)
{
	struct nokia_bt_dev *btdev = serdev_device_get_drvdata(serdev);

	hci_uart_unregister_device(&btdev->hu);
}
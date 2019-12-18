#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct nokia_bt_dev {TYPE_1__* serdev; int /*<<< orphan*/  reset; int /*<<< orphan*/  wakeup_host; int /*<<< orphan*/  wakeup_bt; } ;
struct hci_uart {struct nokia_bt_dev* priv; } ;
struct device {int dummy; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int EPROTO ; 
 int /*<<< orphan*/  INIT_BAUD_RATE ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpiod_set_value_cansleep (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  nokia_flow_control (TYPE_1__*,int) ; 
 int /*<<< orphan*/  serdev_device_set_baudrate (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int serdev_device_wait_for_cts (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  serdev_device_write_flush (TYPE_1__*) ; 

__attribute__((used)) static int nokia_reset(struct hci_uart *hu)
{
	struct nokia_bt_dev *btdev = hu->priv;
	struct device *dev = &btdev->serdev->dev;
	int err;

	/* reset routine */
	gpiod_set_value_cansleep(btdev->reset, 1);
	gpiod_set_value_cansleep(btdev->wakeup_bt, 1);

	msleep(100);

	/* safety check */
	err = gpiod_get_value_cansleep(btdev->wakeup_host);
	if (err == 1) {
		dev_err(dev, "reset: host wakeup not low!");
		return -EPROTO;
	}

	/* flush queue */
	serdev_device_write_flush(btdev->serdev);

	/* init uart */
	nokia_flow_control(btdev->serdev, false);
	serdev_device_set_baudrate(btdev->serdev, INIT_BAUD_RATE);

	gpiod_set_value_cansleep(btdev->reset, 0);

	/* wait for cts */
	err = serdev_device_wait_for_cts(btdev->serdev, true, 200);
	if (err < 0) {
		dev_err(dev, "CTS not received: %d", err);
		return err;
	}

	nokia_flow_control(btdev->serdev, true);

	return 0;
}
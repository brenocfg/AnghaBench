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
struct hci_dev {int dummy; } ;
struct device {int dummy; } ;
struct btmtkuart_dev {int curr_speed; int desired_speed; int stp_cursor; TYPE_1__* serdev; int /*<<< orphan*/  clk; scalar_t__ stp_dlen; } ;
struct TYPE_5__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bt_dev_err (struct hci_dev*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ btmtkuart_is_standalone (struct btmtkuart_dev*) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct btmtkuart_dev* hci_get_drvdata (struct hci_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 int /*<<< orphan*/  serdev_device_close (TYPE_1__*) ; 
 int serdev_device_open (TYPE_1__*) ; 
 int serdev_device_set_baudrate (TYPE_1__*,int) ; 
 int /*<<< orphan*/  serdev_device_set_flow_control (TYPE_1__*,int) ; 

__attribute__((used)) static int btmtkuart_open(struct hci_dev *hdev)
{
	struct btmtkuart_dev *bdev = hci_get_drvdata(hdev);
	struct device *dev;
	int err;

	err = serdev_device_open(bdev->serdev);
	if (err) {
		bt_dev_err(hdev, "Unable to open UART device %s",
			   dev_name(&bdev->serdev->dev));
		goto err_open;
	}

	if (btmtkuart_is_standalone(bdev)) {
		if (bdev->curr_speed != bdev->desired_speed)
			err = serdev_device_set_baudrate(bdev->serdev,
							 115200);
		else
			err = serdev_device_set_baudrate(bdev->serdev,
							 bdev->desired_speed);

		if (err < 0) {
			bt_dev_err(hdev, "Unable to set baudrate UART device %s",
				   dev_name(&bdev->serdev->dev));
			goto  err_serdev_close;
		}

		serdev_device_set_flow_control(bdev->serdev, false);
	}

	bdev->stp_cursor = 2;
	bdev->stp_dlen = 0;

	dev = &bdev->serdev->dev;

	/* Enable the power domain and clock the device requires */
	pm_runtime_enable(dev);
	err = pm_runtime_get_sync(dev);
	if (err < 0) {
		pm_runtime_put_noidle(dev);
		goto err_disable_rpm;
	}

	err = clk_prepare_enable(bdev->clk);
	if (err < 0)
		goto err_put_rpm;

	return 0;

err_put_rpm:
	pm_runtime_put_sync(dev);
err_disable_rpm:
	pm_runtime_disable(dev);
err_serdev_close:
	serdev_device_close(bdev->serdev);
err_open:
	return err;
}
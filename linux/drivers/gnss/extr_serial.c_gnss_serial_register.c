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
struct serdev_device {int /*<<< orphan*/  dev; } ;
struct gnss_serial {int /*<<< orphan*/  gdev; struct serdev_device* serdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_PM ; 
 int /*<<< orphan*/  GNSS_SERIAL_ACTIVE ; 
 int /*<<< orphan*/  GNSS_SERIAL_OFF ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int gnss_register_device (int /*<<< orphan*/ ) ; 
 int gnss_serial_set_power (struct gnss_serial*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 

int gnss_serial_register(struct gnss_serial *gserial)
{
	struct serdev_device *serdev = gserial->serdev;
	int ret;

	if (IS_ENABLED(CONFIG_PM)) {
		pm_runtime_enable(&serdev->dev);
	} else {
		ret = gnss_serial_set_power(gserial, GNSS_SERIAL_ACTIVE);
		if (ret < 0)
			return ret;
	}

	ret = gnss_register_device(gserial->gdev);
	if (ret)
		goto err_disable_rpm;

	return 0;

err_disable_rpm:
	if (IS_ENABLED(CONFIG_PM))
		pm_runtime_disable(&serdev->dev);
	else
		gnss_serial_set_power(gserial, GNSS_SERIAL_OFF);

	return ret;
}
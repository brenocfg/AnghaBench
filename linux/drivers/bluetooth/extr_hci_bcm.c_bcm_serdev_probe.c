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
struct serdev_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct serdev_device* serdev; } ;
struct bcm_device {TYPE_1__ serdev_hu; int /*<<< orphan*/  init_speed; int /*<<< orphan*/  oper_speed; int /*<<< orphan*/  shutdown; TYPE_1__* hu; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int bcm_acpi_probe (struct bcm_device*) ; 
 int bcm_get_resources (struct bcm_device*) ; 
 int bcm_gpio_set_power (struct bcm_device*,int) ; 
 int bcm_of_probe (struct bcm_device*) ; 
 int /*<<< orphan*/  bcm_proto ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 struct bcm_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ has_acpi_companion (int /*<<< orphan*/ *) ; 
 int hci_uart_register_device (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serdev_device_set_drvdata (struct serdev_device*,struct bcm_device*) ; 

__attribute__((used)) static int bcm_serdev_probe(struct serdev_device *serdev)
{
	struct bcm_device *bcmdev;
	int err;

	bcmdev = devm_kzalloc(&serdev->dev, sizeof(*bcmdev), GFP_KERNEL);
	if (!bcmdev)
		return -ENOMEM;

	bcmdev->dev = &serdev->dev;
#ifdef CONFIG_PM
	bcmdev->hu = &bcmdev->serdev_hu;
#endif
	bcmdev->serdev_hu.serdev = serdev;
	serdev_device_set_drvdata(serdev, bcmdev);

	if (has_acpi_companion(&serdev->dev))
		err = bcm_acpi_probe(bcmdev);
	else
		err = bcm_of_probe(bcmdev);
	if (err)
		return err;

	err = bcm_get_resources(bcmdev);
	if (err)
		return err;

	if (!bcmdev->shutdown) {
		dev_warn(&serdev->dev,
			 "No reset resource, using default baud rate\n");
		bcmdev->oper_speed = bcmdev->init_speed;
	}

	err = bcm_gpio_set_power(bcmdev, false);
	if (err)
		dev_err(&serdev->dev, "Failed to power down\n");

	return hci_uart_register_device(&bcmdev->serdev_hu, &bcm_proto);
}
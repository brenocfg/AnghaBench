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
struct mrvl_serdev {TYPE_1__ hu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct mrvl_serdev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int hci_uart_register_device (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrvl_proto ; 
 int /*<<< orphan*/  serdev_device_set_drvdata (struct serdev_device*,struct mrvl_serdev*) ; 

__attribute__((used)) static int mrvl_serdev_probe(struct serdev_device *serdev)
{
	struct mrvl_serdev *mrvldev;

	mrvldev = devm_kzalloc(&serdev->dev, sizeof(*mrvldev), GFP_KERNEL);
	if (!mrvldev)
		return -ENOMEM;

	mrvldev->hu.serdev = serdev;
	serdev_device_set_drvdata(serdev, mrvldev);

	return hci_uart_register_device(&mrvldev->hu, &mrvl_proto);
}
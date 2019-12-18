#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct gendisk {int major; int first_minor; int /*<<< orphan*/  queue; TYPE_1__* private_data; int /*<<< orphan*/  disk_name; int /*<<< orphan*/ * fops; } ;
struct device {int /*<<< orphan*/  release; } ;
struct TYPE_5__ {int id; struct device dev; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  queue; TYPE_2__ pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int ENOMEM ; 
 int UBD_MAJOR ; 
 int UBD_SHIFT ; 
 struct gendisk* alloc_disk (int) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  device_add_disk (struct device*,struct gendisk*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ubd_blops ; 
 int /*<<< orphan*/  ubd_device_release ; 
 TYPE_1__* ubd_devs ; 

__attribute__((used)) static int ubd_disk_register(int major, u64 size, int unit,
			     struct gendisk **disk_out)
{
	struct device *parent = NULL;
	struct gendisk *disk;

	disk = alloc_disk(1 << UBD_SHIFT);
	if(disk == NULL)
		return -ENOMEM;

	disk->major = major;
	disk->first_minor = unit << UBD_SHIFT;
	disk->fops = &ubd_blops;
	set_capacity(disk, size / 512);
	if (major == UBD_MAJOR)
		sprintf(disk->disk_name, "ubd%c", 'a' + unit);
	else
		sprintf(disk->disk_name, "ubd_fake%d", unit);

	/* sysfs register (not for ide fake devices) */
	if (major == UBD_MAJOR) {
		ubd_devs[unit].pdev.id   = unit;
		ubd_devs[unit].pdev.name = DRIVER_NAME;
		ubd_devs[unit].pdev.dev.release = ubd_device_release;
		dev_set_drvdata(&ubd_devs[unit].pdev.dev, &ubd_devs[unit]);
		platform_device_register(&ubd_devs[unit].pdev);
		parent = &ubd_devs[unit].pdev.dev;
	}

	disk->private_data = &ubd_devs[unit];
	disk->queue = ubd_devs[unit].queue;
	device_add_disk(parent, disk, NULL);

	*disk_out = disk;
	return 0;
}
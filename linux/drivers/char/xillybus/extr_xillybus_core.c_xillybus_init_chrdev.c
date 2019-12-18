#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  owner; } ;
struct xilly_endpoint {int num_channels; int major; int lowest_minor; TYPE_2__ cdev; int /*<<< orphan*/  dev; TYPE_1__* ephw; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  devname ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_5__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int MAJOR (int /*<<< orphan*/ ) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MKDEV (int,int) ; 
 int alloc_chrdev_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int cdev_add (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cdev_del (TYPE_2__*) ; 
 int /*<<< orphan*/  cdev_init (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,...) ; 
 struct device* device_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  device_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned char const*) ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xillybus_class ; 
 int /*<<< orphan*/  xillybus_fops ; 
 int /*<<< orphan*/  xillyname ; 

__attribute__((used)) static int xillybus_init_chrdev(struct xilly_endpoint *endpoint,
				const unsigned char *idt)
{
	int rc;
	dev_t dev;
	int devnum, i, minor, major;
	char devname[48];
	struct device *device;

	rc = alloc_chrdev_region(&dev, 0, /* minor start */
				 endpoint->num_channels,
				 xillyname);
	if (rc) {
		dev_warn(endpoint->dev, "Failed to obtain major/minors");
		return rc;
	}

	endpoint->major = major = MAJOR(dev);
	endpoint->lowest_minor = minor = MINOR(dev);

	cdev_init(&endpoint->cdev, &xillybus_fops);
	endpoint->cdev.owner = endpoint->ephw->owner;
	rc = cdev_add(&endpoint->cdev, MKDEV(major, minor),
		      endpoint->num_channels);
	if (rc) {
		dev_warn(endpoint->dev, "Failed to add cdev. Aborting.\n");
		goto unregister_chrdev;
	}

	idt++;

	for (i = minor, devnum = 0;
	     devnum < endpoint->num_channels;
	     devnum++, i++) {
		snprintf(devname, sizeof(devname)-1, "xillybus_%s", idt);

		devname[sizeof(devname)-1] = 0; /* Should never matter */

		while (*idt++)
			/* Skip to next */;

		device = device_create(xillybus_class,
				       NULL,
				       MKDEV(major, i),
				       NULL,
				       "%s", devname);

		if (IS_ERR(device)) {
			dev_warn(endpoint->dev,
				 "Failed to create %s device. Aborting.\n",
				 devname);
			rc = -ENODEV;
			goto unroll_device_create;
		}
	}

	dev_info(endpoint->dev, "Created %d device files.\n",
		 endpoint->num_channels);
	return 0; /* succeed */

unroll_device_create:
	devnum--; i--;
	for (; devnum >= 0; devnum--, i--)
		device_destroy(xillybus_class, MKDEV(major, i));

	cdev_del(&endpoint->cdev);
unregister_chrdev:
	unregister_chrdev_region(MKDEV(major, minor), endpoint->num_channels);

	return rc;
}
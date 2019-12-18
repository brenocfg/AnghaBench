#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  devt; int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/ * type; } ;
struct scom_device {TYPE_1__ dev; int /*<<< orphan*/  cdev; struct fsi_device* fsi_dev; int /*<<< orphan*/  lock; } ;
struct fsi_device {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cdev_device_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  cdev_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct scom_device*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (TYPE_1__*) ; 
 int /*<<< orphan*/  fsi_cdev_type ; 
 int /*<<< orphan*/  fsi_dev_scom ; 
 int /*<<< orphan*/  fsi_free_minor (int /*<<< orphan*/ ) ; 
 int fsi_get_new_minor (struct fsi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  kfree (struct scom_device*) ; 
 struct scom_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (TYPE_1__*) ; 
 int /*<<< orphan*/  scom_fops ; 
 int /*<<< orphan*/  scom_free ; 
 struct fsi_device* to_fsi_dev (struct device*) ; 

__attribute__((used)) static int scom_probe(struct device *dev)
{
	struct fsi_device *fsi_dev = to_fsi_dev(dev);
	struct scom_device *scom;
	int rc, didx;

	scom = kzalloc(sizeof(*scom), GFP_KERNEL);
	if (!scom)
		return -ENOMEM;
	dev_set_drvdata(dev, scom);
	mutex_init(&scom->lock);

	/* Grab a reference to the device (parent of our cdev), we'll drop it later */
	if (!get_device(dev)) {
		kfree(scom);
		return -ENODEV;
	}
	scom->fsi_dev = fsi_dev;

	/* Create chardev for userspace access */
	scom->dev.type = &fsi_cdev_type;
	scom->dev.parent = dev;
	scom->dev.release = scom_free;
	device_initialize(&scom->dev);

	/* Allocate a minor in the FSI space */
	rc = fsi_get_new_minor(fsi_dev, fsi_dev_scom, &scom->dev.devt, &didx);
	if (rc)
		goto err;

	dev_set_name(&scom->dev, "scom%d", didx);
	cdev_init(&scom->cdev, &scom_fops);
	rc = cdev_device_add(&scom->cdev, &scom->dev);
	if (rc) {
		dev_err(dev, "Error %d creating char device %s\n",
			rc, dev_name(&scom->dev));
		goto err_free_minor;
	}

	return 0;
 err_free_minor:
	fsi_free_minor(scom->dev.devt);
 err:
	put_device(&scom->dev);
	return rc;
}
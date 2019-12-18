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
struct TYPE_2__ {int /*<<< orphan*/  owner; } ;
struct device {int /*<<< orphan*/  release; struct device* parent; int /*<<< orphan*/  class; scalar_t__ devt; } ;
struct gnss_device {int id; TYPE_1__ cdev; void* write_buf; int /*<<< orphan*/  read_fifo; int /*<<< orphan*/  read_queue; int /*<<< orphan*/  write_mutex; int /*<<< orphan*/  read_mutex; int /*<<< orphan*/  rwsem; struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  GNSS_MINORS ; 
 int /*<<< orphan*/  GNSS_READ_FIFO_SIZE ; 
 int GNSS_WRITE_BUF_SIZE ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct gnss_device*) ; 
 int /*<<< orphan*/  dev_set_name (struct device*,char*,int) ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  gnss_class ; 
 int /*<<< orphan*/  gnss_device_release ; 
 scalar_t__ gnss_first ; 
 int /*<<< orphan*/  gnss_fops ; 
 int /*<<< orphan*/  gnss_minors ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gnss_device*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

struct gnss_device *gnss_allocate_device(struct device *parent)
{
	struct gnss_device *gdev;
	struct device *dev;
	int id;
	int ret;

	gdev = kzalloc(sizeof(*gdev), GFP_KERNEL);
	if (!gdev)
		return NULL;

	id = ida_simple_get(&gnss_minors, 0, GNSS_MINORS, GFP_KERNEL);
	if (id < 0) {
		kfree(gdev);
		return NULL;
	}

	gdev->id = id;

	dev = &gdev->dev;
	device_initialize(dev);
	dev->devt = gnss_first + id;
	dev->class = gnss_class;
	dev->parent = parent;
	dev->release = gnss_device_release;
	dev_set_drvdata(dev, gdev);
	dev_set_name(dev, "gnss%d", id);

	init_rwsem(&gdev->rwsem);
	mutex_init(&gdev->read_mutex);
	mutex_init(&gdev->write_mutex);
	init_waitqueue_head(&gdev->read_queue);

	ret = kfifo_alloc(&gdev->read_fifo, GNSS_READ_FIFO_SIZE, GFP_KERNEL);
	if (ret)
		goto err_put_device;

	gdev->write_buf = kzalloc(GNSS_WRITE_BUF_SIZE, GFP_KERNEL);
	if (!gdev->write_buf)
		goto err_put_device;

	cdev_init(&gdev->cdev, &gnss_fops);
	gdev->cdev.owner = THIS_MODULE;

	return gdev;

err_put_device:
	put_device(dev);

	return NULL;
}
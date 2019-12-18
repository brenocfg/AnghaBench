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
struct wakeup_source {int /*<<< orphan*/  id; } ;
struct device {int /*<<< orphan*/  kobj; int /*<<< orphan*/  release; int /*<<< orphan*/  groups; struct device* parent; int /*<<< orphan*/  class; int /*<<< orphan*/  devt; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct device* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct wakeup_source*) ; 
 int device_add (struct device*) ; 
 int /*<<< orphan*/  device_create_release ; 
 int /*<<< orphan*/  device_initialize (struct device*) ; 
 int /*<<< orphan*/  device_set_pm_not_required (struct device*) ; 
 int kobject_set_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 struct device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  wakeup_class ; 
 int /*<<< orphan*/  wakeup_source_groups ; 

__attribute__((used)) static struct device *wakeup_source_device_create(struct device *parent,
						  struct wakeup_source *ws)
{
	struct device *dev = NULL;
	int retval = -ENODEV;

	dev = kzalloc(sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		retval = -ENOMEM;
		goto error;
	}

	device_initialize(dev);
	dev->devt = MKDEV(0, 0);
	dev->class = wakeup_class;
	dev->parent = parent;
	dev->groups = wakeup_source_groups;
	dev->release = device_create_release;
	dev_set_drvdata(dev, ws);
	device_set_pm_not_required(dev);

	retval = kobject_set_name(&dev->kobj, "wakeup%d", ws->id);
	if (retval)
		goto error;

	retval = device_add(dev);
	if (retval)
		goto error;

	return dev;

error:
	put_device(dev);
	return ERR_PTR(retval);
}
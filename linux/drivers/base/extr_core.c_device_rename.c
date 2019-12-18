#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct kobject {int dummy; } ;
struct device {TYPE_3__* class; struct kobject kobj; } ;
struct TYPE_6__ {TYPE_2__* p; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ subsys; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,char const*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 struct device* get_device (struct device*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  kobject_namespace (struct kobject*) ; 
 int kobject_rename (struct kobject*,char const*) ; 
 char* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int sysfs_rename_link_ns (int /*<<< orphan*/ *,struct kobject*,char*,char const*,int /*<<< orphan*/ ) ; 

int device_rename(struct device *dev, const char *new_name)
{
	struct kobject *kobj = &dev->kobj;
	char *old_device_name = NULL;
	int error;

	dev = get_device(dev);
	if (!dev)
		return -EINVAL;

	dev_dbg(dev, "renaming to %s\n", new_name);

	old_device_name = kstrdup(dev_name(dev), GFP_KERNEL);
	if (!old_device_name) {
		error = -ENOMEM;
		goto out;
	}

	if (dev->class) {
		error = sysfs_rename_link_ns(&dev->class->p->subsys.kobj,
					     kobj, old_device_name,
					     new_name, kobject_namespace(kobj));
		if (error)
			goto out;
	}

	error = kobject_rename(kobj, new_name);
	if (error)
		goto out;

out:
	put_device(dev);

	kfree(old_device_name);

	return error;
}
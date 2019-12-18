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
struct linux_cdev {int /*<<< orphan*/  kobj; struct file_operations const* ops; } ;
struct file_operations {int dummy; } ;

/* Variables and functions */
 int cdev_add (struct linux_cdev*,int /*<<< orphan*/ ,int) ; 
 struct linux_cdev* cdev_alloc () ; 
 int /*<<< orphan*/  kobject_set_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  makedev (unsigned int,int) ; 

int
__register_chrdev(unsigned int major, unsigned int baseminor,
    unsigned int count, const char *name,
    const struct file_operations *fops)
{
	struct linux_cdev *cdev;
	int ret = 0;
	int i;

	for (i = baseminor; i < baseminor + count; i++) {
		cdev = cdev_alloc();
		cdev->ops = fops;
		kobject_set_name(&cdev->kobj, name);

		ret = cdev_add(cdev, makedev(major, i), 1);
		if (ret != 0)
			break;
	}
	return (ret);
}
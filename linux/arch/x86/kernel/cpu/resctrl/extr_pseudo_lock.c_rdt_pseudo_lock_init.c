#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  devnode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_1__* class_create (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* pseudo_lock_class ; 
 int /*<<< orphan*/  pseudo_lock_dev_fops ; 
 int /*<<< orphan*/  pseudo_lock_devnode ; 
 int pseudo_lock_major ; 
 int register_chrdev (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_chrdev (int,char*) ; 

int rdt_pseudo_lock_init(void)
{
	int ret;

	ret = register_chrdev(0, "pseudo_lock", &pseudo_lock_dev_fops);
	if (ret < 0)
		return ret;

	pseudo_lock_major = ret;

	pseudo_lock_class = class_create(THIS_MODULE, "pseudo_lock");
	if (IS_ERR(pseudo_lock_class)) {
		ret = PTR_ERR(pseudo_lock_class);
		unregister_chrdev(pseudo_lock_major, "pseudo_lock");
		return ret;
	}

	pseudo_lock_class->devnode = pseudo_lock_devnode;
	return 0;
}
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
struct device {int dummy; } ;
struct class {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 struct device* class_find_device_by_devt (struct class*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_unregister (struct device*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 

void device_destroy(struct class *class, dev_t devt)
{
	struct device *dev;

	dev = class_find_device_by_devt(class, devt);
	if (dev) {
		put_device(dev);
		device_unregister(dev);
	}
}
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

/* Variables and functions */
 int /*<<< orphan*/  device_lock (struct device*) ; 
 int /*<<< orphan*/  device_unlock (struct device*) ; 
 int /*<<< orphan*/  devres_release_group (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_dev_dax (struct device*) ; 

__attribute__((used)) static int dax_pmem_compat_release(struct device *dev, void *data)
{
	device_lock(dev);
	devres_release_group(dev, to_dev_dax(dev));
	device_unlock(dev);

	return 0;
}
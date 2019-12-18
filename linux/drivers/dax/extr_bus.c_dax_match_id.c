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
struct dax_device_driver {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __dax_match_id (struct dax_device_driver*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dax_bus_lock ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dax_match_id(struct dax_device_driver *dax_drv, struct device *dev)
{
	int match;

	mutex_lock(&dax_bus_lock);
	match = !!__dax_match_id(dax_drv, dev_name(dev));
	mutex_unlock(&dax_bus_lock);

	return match;
}
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
struct device_driver {int dummy; } ;
struct device {int dummy; } ;
struct dax_device_driver {scalar_t__ match_always; } ;

/* Variables and functions */
 int dax_match_id (struct dax_device_driver*,struct device*) ; 
 struct dax_device_driver* to_dax_drv (struct device_driver*) ; 

__attribute__((used)) static int dax_bus_match(struct device *dev, struct device_driver *drv)
{
	struct dax_device_driver *dax_drv = to_dax_drv(drv);

	/*
	 * All but the 'device-dax' driver, which has 'match_always'
	 * set, requires an exact id match.
	 */
	if (dax_drv->match_always)
		return 1;

	return dax_match_id(dax_drv, dev);
}
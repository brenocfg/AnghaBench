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

/* Variables and functions */
 struct device* bus_find_device (int /*<<< orphan*/ *,struct device*,struct device_driver const*,void*) ; 
 int /*<<< orphan*/  platform_bus_type ; 
 scalar_t__ platform_match ; 

struct device *platform_find_device_by_driver(struct device *start,
					      const struct device_driver *drv)
{
	return bus_find_device(&platform_bus_type, start, drv,
			       (void *)platform_match);
}
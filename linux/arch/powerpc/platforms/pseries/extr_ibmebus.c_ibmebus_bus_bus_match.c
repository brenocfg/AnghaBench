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
struct of_device_id {int dummy; } ;
struct device_driver {struct of_device_id* of_match_table; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * of_match_device (struct of_device_id const*,struct device*) ; 

__attribute__((used)) static int ibmebus_bus_bus_match(struct device *dev, struct device_driver *drv)
{
	const struct of_device_id *matches = drv->of_match_table;

	if (!matches)
		return 0;

	return of_match_device(matches, dev) != NULL;
}
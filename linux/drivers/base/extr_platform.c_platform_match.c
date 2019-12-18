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
struct platform_driver {scalar_t__ id_table; } ;
struct platform_device {scalar_t__ name; scalar_t__ driver_override; } ;
struct device_driver {int /*<<< orphan*/  name; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ acpi_driver_match_device (struct device*,struct device_driver*) ; 
 scalar_t__ of_driver_match_device (struct device*,struct device_driver*) ; 
 int /*<<< orphan*/ * platform_match_id (scalar_t__,struct platform_device*) ; 
 scalar_t__ strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (struct device*) ; 
 struct platform_driver* to_platform_driver (struct device_driver*) ; 

__attribute__((used)) static int platform_match(struct device *dev, struct device_driver *drv)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct platform_driver *pdrv = to_platform_driver(drv);

	/* When driver_override is set, only bind to the matching driver */
	if (pdev->driver_override)
		return !strcmp(pdev->driver_override, drv->name);

	/* Attempt an OF style match first */
	if (of_driver_match_device(dev, drv))
		return 1;

	/* Then try ACPI style match */
	if (acpi_driver_match_device(dev, drv))
		return 1;

	/* Then try to match against the id table */
	if (pdrv->id_table)
		return platform_match_id(pdrv->id_table, pdev) != NULL;

	/* fall-back to driver name match */
	return (strcmp(pdev->name, drv->name) == 0);
}
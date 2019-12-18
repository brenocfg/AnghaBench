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
 scalar_t__ is_fw_unit (struct device*) ; 
 int /*<<< orphan*/ * unit_match (struct device*,struct device_driver*) ; 

__attribute__((used)) static int fw_unit_match(struct device *dev, struct device_driver *drv)
{
	/* We only allow binding to fw_units. */
	return is_fw_unit(dev) && unit_match(dev, drv) != NULL;
}
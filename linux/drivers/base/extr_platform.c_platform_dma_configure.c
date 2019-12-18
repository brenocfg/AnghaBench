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
struct device {int /*<<< orphan*/  fwnode; scalar_t__ of_node; } ;
typedef  enum dev_dma_attr { ____Placeholder_dev_dma_attr } dev_dma_attr ;

/* Variables and functions */
 int acpi_dma_configure (struct device*,int) ; 
 int acpi_get_dma_attr (int /*<<< orphan*/ ) ; 
 scalar_t__ has_acpi_companion (struct device*) ; 
 int of_dma_configure (struct device*,scalar_t__,int) ; 
 int /*<<< orphan*/  to_acpi_device_node (int /*<<< orphan*/ ) ; 

int platform_dma_configure(struct device *dev)
{
	enum dev_dma_attr attr;
	int ret = 0;

	if (dev->of_node) {
		ret = of_dma_configure(dev, dev->of_node, true);
	} else if (has_acpi_companion(dev)) {
		attr = acpi_get_dma_attr(to_acpi_device_node(dev->fwnode));
		ret = acpi_dma_configure(dev, attr);
	}

	return ret;
}
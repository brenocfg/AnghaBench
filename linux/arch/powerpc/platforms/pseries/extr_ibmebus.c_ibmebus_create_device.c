#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * dma_ops; int /*<<< orphan*/ * bus; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  ibmebus_bus_device ; 
 int /*<<< orphan*/  ibmebus_bus_type ; 
 int /*<<< orphan*/  ibmebus_dma_ops ; 
 int of_device_add (struct platform_device*) ; 
 struct platform_device* of_device_alloc (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 

__attribute__((used)) static int ibmebus_create_device(struct device_node *dn)
{
	struct platform_device *dev;
	int ret;

	dev = of_device_alloc(dn, NULL, &ibmebus_bus_device);
	if (!dev)
		return -ENOMEM;

	dev->dev.bus = &ibmebus_bus_type;
	dev->dev.dma_ops = &ibmebus_dma_ops;

	ret = of_device_add(dev);
	if (ret)
		platform_device_put(dev);
	return ret;
}
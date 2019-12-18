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
struct resource {int start; } ;
struct TYPE_2__ {scalar_t__ of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_OF_IRQ ; 
 int ENXIO ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  IORESOURCE_IRQ ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int of_irq_get_byname (scalar_t__,char const*) ; 
 struct resource* platform_get_resource_byname (struct platform_device*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int __platform_get_irq_byname(struct platform_device *dev,
				     const char *name)
{
	struct resource *r;

	if (IS_ENABLED(CONFIG_OF_IRQ) && dev->dev.of_node) {
		int ret;

		ret = of_irq_get_byname(dev->dev.of_node, name);
		if (ret > 0 || ret == -EPROBE_DEFER)
			return ret;
	}

	r = platform_get_resource_byname(dev, IORESOURCE_IRQ, name);
	if (r)
		return r->start;

	return -ENXIO;
}
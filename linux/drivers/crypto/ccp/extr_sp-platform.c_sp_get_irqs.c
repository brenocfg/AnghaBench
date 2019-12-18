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
struct sp_platform {unsigned int irq_count; } ;
struct sp_device {int psp_irq; int ccp_irq; struct device* dev; struct sp_platform* dev_specific; } ;
struct resource {int dummy; } ;
struct platform_device {unsigned int num_resources; struct resource* resource; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IORESOURCE_IRQ ; 
 int /*<<< orphan*/  dev_notice (struct device*,char*,int) ; 
 int platform_get_irq (struct platform_device*,int) ; 
 scalar_t__ resource_type (struct resource*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int sp_get_irqs(struct sp_device *sp)
{
	struct sp_platform *sp_platform = sp->dev_specific;
	struct device *dev = sp->dev;
	struct platform_device *pdev = to_platform_device(dev);
	unsigned int i, count;
	int ret;

	for (i = 0, count = 0; i < pdev->num_resources; i++) {
		struct resource *res = &pdev->resource[i];

		if (resource_type(res) == IORESOURCE_IRQ)
			count++;
	}

	sp_platform->irq_count = count;

	ret = platform_get_irq(pdev, 0);
	if (ret < 0) {
		dev_notice(dev, "unable to get IRQ (%d)\n", ret);
		return ret;
	}

	sp->psp_irq = ret;
	if (count == 1) {
		sp->ccp_irq = ret;
	} else {
		ret = platform_get_irq(pdev, 1);
		if (ret < 0) {
			dev_notice(dev, "unable to get IRQ (%d)\n", ret);
			return ret;
		}

		sp->ccp_irq = ret;
	}

	return 0;
}
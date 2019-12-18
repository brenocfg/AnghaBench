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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct omap3_l3 {int /*<<< orphan*/  rt; void* debug_irq; void* app_irq; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  IRQF_TRIGGER_RISING ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free_irq (void*,struct omap3_l3*) ; 
 int /*<<< orphan*/  ioremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct omap3_l3*) ; 
 struct omap3_l3* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap3_l3_app_irq ; 
 void* platform_get_irq (struct platform_device*,int) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap3_l3*) ; 
 int request_irq (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct omap3_l3*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 

__attribute__((used)) static int omap3_l3_probe(struct platform_device *pdev)
{
	struct omap3_l3 *l3;
	struct resource *res;
	int ret;

	l3 = kzalloc(sizeof(*l3), GFP_KERNEL);
	if (!l3)
		return -ENOMEM;

	platform_set_drvdata(pdev, l3);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "couldn't find resource\n");
		ret = -ENODEV;
		goto err0;
	}
	l3->rt = ioremap(res->start, resource_size(res));
	if (!l3->rt) {
		dev_err(&pdev->dev, "ioremap failed\n");
		ret = -ENOMEM;
		goto err0;
	}

	l3->debug_irq = platform_get_irq(pdev, 0);
	ret = request_irq(l3->debug_irq, omap3_l3_app_irq, IRQF_TRIGGER_RISING,
			  "l3-debug-irq", l3);
	if (ret) {
		dev_err(&pdev->dev, "couldn't request debug irq\n");
		goto err1;
	}

	l3->app_irq = platform_get_irq(pdev, 1);
	ret = request_irq(l3->app_irq, omap3_l3_app_irq, IRQF_TRIGGER_RISING,
			  "l3-app-irq", l3);
	if (ret) {
		dev_err(&pdev->dev, "couldn't request app irq\n");
		goto err2;
	}

	return 0;

err2:
	free_irq(l3->debug_irq, l3);
err1:
	iounmap(l3->rt);
err0:
	kfree(l3);
	return ret;
}
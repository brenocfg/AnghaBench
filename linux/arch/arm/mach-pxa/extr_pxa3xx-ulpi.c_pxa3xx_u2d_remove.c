#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int /*<<< orphan*/  start; } ;
struct pxa3xx_u2d_platform_data {int /*<<< orphan*/  (* exit ) (TYPE_2__*) ;} ;
struct TYPE_5__ {struct pxa3xx_u2d_platform_data* platform_data; } ;
struct platform_device {TYPE_2__ dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  clk; int /*<<< orphan*/  mmio_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_is_pxa310 () ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pxa310_otg_exit () ; 
 int /*<<< orphan*/  pxa310_stop_otg_hc () ; 
 int /*<<< orphan*/  release_mem_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 TYPE_1__* u2d ; 

__attribute__((used)) static int pxa3xx_u2d_remove(struct platform_device *pdev)
{
	struct pxa3xx_u2d_platform_data *pdata = pdev->dev.platform_data;
	struct resource *r;

	if (cpu_is_pxa310()) {
		pxa310_stop_otg_hc();
		pxa310_otg_exit();
	}

	if (pdata->exit)
		pdata->exit(&pdev->dev);

	platform_set_drvdata(pdev, NULL);
	iounmap(u2d->mmio_base);
	r = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	release_mem_region(r->start, resource_size(r));

	clk_put(u2d->clk);

	kfree(u2d);

	return 0;
}
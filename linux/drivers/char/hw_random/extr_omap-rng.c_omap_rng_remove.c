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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct omap_rng_dev {int /*<<< orphan*/  clk_reg; int /*<<< orphan*/  clk; TYPE_1__* pdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cleanup ) (struct omap_rng_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct omap_rng_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct omap_rng_dev*) ; 

__attribute__((used)) static int omap_rng_remove(struct platform_device *pdev)
{
	struct omap_rng_dev *priv = platform_get_drvdata(pdev);


	priv->pdata->cleanup(priv);

	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	clk_disable_unprepare(priv->clk);
	clk_disable_unprepare(priv->clk_reg);

	return 0;
}
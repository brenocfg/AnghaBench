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
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epll ; 
 int /*<<< orphan*/  exynos_audss_clk_teardown () ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_disable (TYPE_1__*) ; 

__attribute__((used)) static int exynos_audss_clk_remove(struct platform_device *pdev)
{
	of_clk_del_provider(pdev->dev.of_node);

	exynos_audss_clk_teardown();
	pm_runtime_disable(&pdev->dev);

	if (!IS_ERR(epll))
		clk_disable_unprepare(epll);

	return 0;
}
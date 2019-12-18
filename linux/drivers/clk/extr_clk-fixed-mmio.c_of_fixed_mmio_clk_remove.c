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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_unregister_fixed_rate (struct clk_hw*) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 struct clk_hw* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int of_fixed_mmio_clk_remove(struct platform_device *pdev)
{
	struct clk_hw *clk = platform_get_drvdata(pdev);

	of_clk_del_provider(pdev->dev.of_node);
	clk_hw_unregister_fixed_rate(clk);

	return 0;
}
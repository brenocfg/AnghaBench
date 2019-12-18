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
struct platform_device {int dummy; } ;
struct clk_plt_data {int /*<<< orphan*/  mclk_lookup; int /*<<< orphan*/  ether_clk_lookup; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMC_CLK_NUM ; 
 int /*<<< orphan*/  clkdev_drop (int /*<<< orphan*/ ) ; 
 struct clk_plt_data* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  plt_clk_unregister_loop (struct clk_plt_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plt_clk_unregister_parents (struct clk_plt_data*) ; 

__attribute__((used)) static int plt_clk_remove(struct platform_device *pdev)
{
	struct clk_plt_data *data;

	data = platform_get_drvdata(pdev);

	clkdev_drop(data->ether_clk_lookup);
	clkdev_drop(data->mclk_lookup);
	plt_clk_unregister_loop(data, PMC_CLK_NUM);
	plt_clk_unregister_parents(data);
	return 0;
}
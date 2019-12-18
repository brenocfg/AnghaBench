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
struct clk_periph_driver_data {struct clk_hw_onecell_data* hw_data; } ;
struct clk_hw_onecell_data {int num; int /*<<< orphan*/ * hws; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 struct clk_periph_driver_data* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int armada_3700_periph_clock_remove(struct platform_device *pdev)
{
	struct clk_periph_driver_data *data = platform_get_drvdata(pdev);
	struct clk_hw_onecell_data *hw_data = data->hw_data;
	int i;

	of_clk_del_provider(pdev->dev.of_node);

	for (i = 0; i < hw_data->num; i++)
		clk_hw_unregister(hw_data->hws[i]);

	return 0;
}
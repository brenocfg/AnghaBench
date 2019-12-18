#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_4__ {int num; int /*<<< orphan*/ * hws; } ;
struct clk_bcm63xx_hw {TYPE_2__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_unregister_gate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 struct clk_bcm63xx_hw* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int clk_bcm63xx_remove(struct platform_device *pdev)
{
	struct clk_bcm63xx_hw *hw = platform_get_drvdata(pdev);
	int i;

	of_clk_del_provider(pdev->dev.of_node);

	for (i = 0; i < hw->data.num; i++) {
		if (!IS_ERR(hw->data.hws[i]))
			clk_hw_unregister_gate(hw->data.hws[i]);
	}

	return 0;
}
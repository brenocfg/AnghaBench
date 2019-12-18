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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct owl_clk_desc {int /*<<< orphan*/  hw_clks; } ;

/* Variables and functions */
 int owl_clk_probe (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owl_clk_regmap_init (struct platform_device*,struct owl_clk_desc*) ; 
 struct owl_clk_desc s500_clk_desc ; 

__attribute__((used)) static int s500_clk_probe(struct platform_device *pdev)
{
	struct owl_clk_desc *desc;

	desc = &s500_clk_desc;
	owl_clk_regmap_init(pdev, desc);

	return owl_clk_probe(&pdev->dev, desc->hw_clks);
}
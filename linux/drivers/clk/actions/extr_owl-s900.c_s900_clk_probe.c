#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  nr_resets; int /*<<< orphan*/ * ops; int /*<<< orphan*/  of_node; } ;
struct owl_reset {TYPE_3__ rcdev; int /*<<< orphan*/  regmap; int /*<<< orphan*/  reset_map; } ;
struct owl_clk_desc {int /*<<< orphan*/  hw_clks; int /*<<< orphan*/  regmap; int /*<<< orphan*/  resets; int /*<<< orphan*/  num_resets; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct owl_reset* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (TYPE_1__*,TYPE_3__*) ; 
 int owl_clk_probe (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  owl_clk_regmap_init (struct platform_device*,struct owl_clk_desc*) ; 
 int /*<<< orphan*/  owl_reset_ops ; 
 struct owl_clk_desc s900_clk_desc ; 

__attribute__((used)) static int s900_clk_probe(struct platform_device *pdev)
{
	struct owl_clk_desc *desc;
	struct owl_reset *reset;
	int ret;

	desc = &s900_clk_desc;
	owl_clk_regmap_init(pdev, desc);

	/*
	 * FIXME: Reset controller registration should be moved to
	 * common code, once all SoCs of Owl family supports it.
	 */
	reset = devm_kzalloc(&pdev->dev, sizeof(*reset), GFP_KERNEL);
	if (!reset)
		return -ENOMEM;

	reset->rcdev.of_node = pdev->dev.of_node;
	reset->rcdev.ops = &owl_reset_ops;
	reset->rcdev.nr_resets = desc->num_resets;
	reset->reset_map = desc->resets;
	reset->regmap = desc->regmap;

	ret = devm_reset_controller_register(&pdev->dev, &reset->rcdev);
	if (ret)
		dev_err(&pdev->dev, "Failed to register reset controller\n");

	return owl_clk_probe(&pdev->dev, desc->hw_clks);
}
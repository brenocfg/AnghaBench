#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {TYPE_1__* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {struct clk_init_data* init; } ;
struct hsdk_pll_clk {TYPE_4__ hw; int /*<<< orphan*/  pll_devdata; struct device* dev; int /*<<< orphan*/  regs; } ;
struct clk_init_data {unsigned int name; char const** parent_names; unsigned int num_parents; int /*<<< orphan*/ * ops; } ;
struct TYPE_6__ {unsigned int name; } ;

/* Variables and functions */
 unsigned int CGU_PLL_SOURCE_MAX ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int devm_clk_hw_register (struct device*,TYPE_4__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 struct hsdk_pll_clk* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsdk_pll_ops ; 
 int of_clk_add_hw_provider (TYPE_1__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 unsigned int of_clk_get_parent_count (TYPE_1__*) ; 
 char* of_clk_get_parent_name (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_hw_simple_get ; 
 int /*<<< orphan*/  of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hsdk_pll_clk_probe(struct platform_device *pdev)
{
	int ret;
	struct resource *mem;
	const char *parent_name;
	unsigned int num_parents;
	struct hsdk_pll_clk *pll_clk;
	struct clk_init_data init = { };
	struct device *dev = &pdev->dev;

	pll_clk = devm_kzalloc(dev, sizeof(*pll_clk), GFP_KERNEL);
	if (!pll_clk)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pll_clk->regs = devm_ioremap_resource(dev, mem);
	if (IS_ERR(pll_clk->regs))
		return PTR_ERR(pll_clk->regs);

	init.name = dev->of_node->name;
	init.ops = &hsdk_pll_ops;
	parent_name = of_clk_get_parent_name(dev->of_node, 0);
	init.parent_names = &parent_name;
	num_parents = of_clk_get_parent_count(dev->of_node);
	if (num_parents == 0 || num_parents > CGU_PLL_SOURCE_MAX) {
		dev_err(dev, "wrong clock parents number: %u\n", num_parents);
		return -EINVAL;
	}
	init.num_parents = num_parents;

	pll_clk->hw.init = &init;
	pll_clk->dev = dev;
	pll_clk->pll_devdata = of_device_get_match_data(dev);

	if (!pll_clk->pll_devdata) {
		dev_err(dev, "No OF match data provided\n");
		return -EINVAL;
	}

	ret = devm_clk_hw_register(dev, &pll_clk->hw);
	if (ret) {
		dev_err(dev, "failed to register %s clock\n", init.name);
		return ret;
	}

	return of_clk_add_hw_provider(dev->of_node, of_clk_hw_simple_get,
			&pll_clk->hw);
}
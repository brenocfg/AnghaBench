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
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct i2s_pll_clk {TYPE_1__ hw; struct device* dev; struct clk* base; } ;
struct device_node {char* name; } ;
struct clk_init_data {char const* name; char const** parent_names; int num_parents; int /*<<< orphan*/ * ops; } ;
struct clk {int dummy; } ;
typedef  int /*<<< orphan*/  init ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,int) ; 
 struct clk* devm_clk_register (struct device*,TYPE_1__*) ; 
 struct clk* devm_ioremap_resource (struct device*,struct resource*) ; 
 struct i2s_pll_clk* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2s_pll_ops ; 
 int /*<<< orphan*/  memset (struct clk_init_data*,int /*<<< orphan*/ ,int) ; 
 int of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,struct clk*) ; 
 char* of_clk_get_parent_name (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_src_simple_get ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i2s_pll_clk_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device_node *node = dev->of_node;
	const char *clk_name;
	const char *parent_name;
	struct clk *clk;
	struct i2s_pll_clk *pll_clk;
	struct clk_init_data init;
	struct resource *mem;

	pll_clk = devm_kzalloc(dev, sizeof(*pll_clk), GFP_KERNEL);
	if (!pll_clk)
		return -ENOMEM;

	mem = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	pll_clk->base = devm_ioremap_resource(dev, mem);
	if (IS_ERR(pll_clk->base))
		return PTR_ERR(pll_clk->base);

	memset(&init, 0, sizeof(init));
	clk_name = node->name;
	init.name = clk_name;
	init.ops = &i2s_pll_ops;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = &parent_name;
	init.num_parents = 1;
	pll_clk->hw.init = &init;
	pll_clk->dev = dev;

	clk = devm_clk_register(dev, &pll_clk->hw);
	if (IS_ERR(clk)) {
		dev_err(dev, "failed to register %s clock (%ld)\n",
				clk_name, PTR_ERR(clk));
		return PTR_ERR(clk);
	}

	return of_clk_add_provider(node, of_clk_src_simple_get, clk);
}
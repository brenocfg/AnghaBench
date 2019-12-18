#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  detach_dev; int /*<<< orphan*/  attach_dev; int /*<<< orphan*/  name; } ;
struct TYPE_6__ {struct clk_init_data* init; } ;
struct davinci_lpsc_clk {int md; int pd; int flags; TYPE_1__ pm_domain; TYPE_2__ hw; struct regmap* regmap; struct device* dev; } ;
struct clk_init_data {char const* name; char const** parent_names; int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_IS_CRITICAL ; 
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int ENOMEM ; 
 struct davinci_lpsc_clk* ERR_PTR (int) ; 
 int /*<<< orphan*/  GENPD_FLAG_PM_CLK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LPSC_ALWAYS_ENABLED ; 
 int LPSC_SET_RATE_PARENT ; 
 int /*<<< orphan*/  best_dev_name (struct device*) ; 
 int clk_hw_register (struct device*,TYPE_2__*) ; 
 int clk_hw_register_clkdev (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int davinci_lpsc_clk_is_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  davinci_lpsc_clk_ops ; 
 int /*<<< orphan*/  davinci_psc_genpd_attach_dev ; 
 int /*<<< orphan*/  davinci_psc_genpd_detach_dev ; 
 int /*<<< orphan*/  devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  kfree (struct davinci_lpsc_clk*) ; 
 struct davinci_lpsc_clk* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_genpd_init (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct davinci_lpsc_clk *
davinci_lpsc_clk_register(struct device *dev, const char *name,
			  const char *parent_name, struct regmap *regmap,
			  u32 md, u32 pd, u32 flags)
{
	struct clk_init_data init;
	struct davinci_lpsc_clk *lpsc;
	int ret;
	bool is_on;

	lpsc = kzalloc(sizeof(*lpsc), GFP_KERNEL);
	if (!lpsc)
		return ERR_PTR(-ENOMEM);

	init.name = name;
	init.ops = &davinci_lpsc_clk_ops;
	init.parent_names = (parent_name ? &parent_name : NULL);
	init.num_parents = (parent_name ? 1 : 0);
	init.flags = 0;

	if (flags & LPSC_ALWAYS_ENABLED)
		init.flags |= CLK_IS_CRITICAL;

	if (flags & LPSC_SET_RATE_PARENT)
		init.flags |= CLK_SET_RATE_PARENT;

	lpsc->dev = dev;
	lpsc->regmap = regmap;
	lpsc->hw.init = &init;
	lpsc->md = md;
	lpsc->pd = pd;
	lpsc->flags = flags;

	ret = clk_hw_register(dev, &lpsc->hw);
	if (ret < 0) {
		kfree(lpsc);
		return ERR_PTR(ret);
	}

	/* for now, genpd is only registered when using device-tree */
	if (!dev || !dev->of_node)
		return lpsc;

	/* genpd attach needs a way to look up this clock */
	ret = clk_hw_register_clkdev(&lpsc->hw, name, best_dev_name(dev));

	lpsc->pm_domain.name = devm_kasprintf(dev, GFP_KERNEL, "%s: %s",
					      best_dev_name(dev), name);
	lpsc->pm_domain.attach_dev = davinci_psc_genpd_attach_dev;
	lpsc->pm_domain.detach_dev = davinci_psc_genpd_detach_dev;
	lpsc->pm_domain.flags = GENPD_FLAG_PM_CLK;

	is_on = davinci_lpsc_clk_is_enabled(&lpsc->hw);
	pm_genpd_init(&lpsc->pm_domain, NULL, is_on);

	return lpsc;
}
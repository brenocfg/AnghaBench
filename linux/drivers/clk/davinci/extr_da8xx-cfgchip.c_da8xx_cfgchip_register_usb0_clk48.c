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
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct clk_init_data* init; } ;
struct da8xx_usb0_clk48 {TYPE_1__ hw; struct regmap* regmap; struct clk* fck; } ;
struct clk_init_data {char* name; char const* const* parent_names; int num_parents; int /*<<< orphan*/ * ops; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct da8xx_usb0_clk48* ERR_CAST (struct clk*) ; 
 struct da8xx_usb0_clk48* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int /*<<< orphan*/  PTR_ERR (struct clk*) ; 
 int /*<<< orphan*/  da8xx_usb0_clk48_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct clk* devm_clk_get (struct device*,char*) ; 
 int devm_clk_hw_register (struct device*,TYPE_1__*) ; 
 struct da8xx_usb0_clk48* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct da8xx_usb0_clk48 *
da8xx_cfgchip_register_usb0_clk48(struct device *dev,
				  struct regmap *regmap)
{
	const char * const parent_names[] = { "usb_refclkin", "pll0_auxclk" };
	struct clk *fck_clk;
	struct da8xx_usb0_clk48 *usb0;
	struct clk_init_data init;
	int ret;

	fck_clk = devm_clk_get(dev, "fck");
	if (IS_ERR(fck_clk)) {
		if (PTR_ERR(fck_clk) != -EPROBE_DEFER)
			dev_err(dev, "Missing fck clock\n");
		return ERR_CAST(fck_clk);
	}

	usb0 = devm_kzalloc(dev, sizeof(*usb0), GFP_KERNEL);
	if (!usb0)
		return ERR_PTR(-ENOMEM);

	init.name = "usb0_clk48";
	init.ops = &da8xx_usb0_clk48_ops;
	init.parent_names = parent_names;
	init.num_parents = 2;

	usb0->hw.init = &init;
	usb0->fck = fck_clk;
	usb0->regmap = regmap;

	ret = devm_clk_hw_register(dev, &usb0->hw);
	if (ret < 0)
		return ERR_PTR(ret);

	return usb0;
}
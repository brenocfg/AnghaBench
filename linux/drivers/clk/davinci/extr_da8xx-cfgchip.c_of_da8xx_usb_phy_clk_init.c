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
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct da8xx_usb1_clk48 {int /*<<< orphan*/  hw; } ;
struct da8xx_usb0_clk48 {int /*<<< orphan*/  hw; } ;
struct clk_hw_onecell_data {int num; int /*<<< orphan*/ ** hws; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 void* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct da8xx_usb1_clk48*) ; 
 int PTR_ERR (struct da8xx_usb1_clk48*) ; 
 struct da8xx_usb1_clk48* da8xx_cfgchip_register_usb0_clk48 (struct device*,struct regmap*) ; 
 struct da8xx_usb1_clk48* da8xx_cfgchip_register_usb1_clk48 (struct device*,struct regmap*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,int) ; 
 struct clk_hw_onecell_data* devm_kzalloc (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,struct clk_hw_onecell_data*) ; 
 int /*<<< orphan*/  hws ; 
 int /*<<< orphan*/  of_clk_hw_onecell_get ; 
 int /*<<< orphan*/  struct_size (struct clk_hw_onecell_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int of_da8xx_usb_phy_clk_init(struct device *dev, struct regmap *regmap)
{
	struct clk_hw_onecell_data *clk_data;
	struct da8xx_usb0_clk48 *usb0;
	struct da8xx_usb1_clk48 *usb1;

	clk_data = devm_kzalloc(dev, struct_size(clk_data, hws, 2),
				GFP_KERNEL);
	if (!clk_data)
		return -ENOMEM;

	clk_data->num = 2;

	usb0 = da8xx_cfgchip_register_usb0_clk48(dev, regmap);
	if (IS_ERR(usb0)) {
		if (PTR_ERR(usb0) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_warn(dev, "Failed to register usb0_clk48 (%ld)\n",
			 PTR_ERR(usb0));

		clk_data->hws[0] = ERR_PTR(-ENOENT);
	} else {
		clk_data->hws[0] = &usb0->hw;
	}

	usb1 = da8xx_cfgchip_register_usb1_clk48(dev, regmap);
	if (IS_ERR(usb1)) {
		if (PTR_ERR(usb1) == -EPROBE_DEFER)
			return -EPROBE_DEFER;

		dev_warn(dev, "Failed to register usb1_clk48 (%ld)\n",
			 PTR_ERR(usb1));

		clk_data->hws[1] = ERR_PTR(-ENOENT);
	} else {
		clk_data->hws[1] = &usb1->hw;
	}

	return devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get, clk_data);
}
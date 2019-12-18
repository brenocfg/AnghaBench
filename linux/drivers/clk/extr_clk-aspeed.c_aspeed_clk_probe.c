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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
typedef  struct regmap clk_hw ;
struct TYPE_3__ {int nr_resets; int /*<<< orphan*/  of_node; int /*<<< orphan*/ * ops; int /*<<< orphan*/  owner; } ;
struct aspeed_reset {TYPE_1__ rcdev; struct regmap* map; } ;
struct aspeed_gate_data {int clock_idx; int /*<<< orphan*/  reset_idx; int /*<<< orphan*/  flags; int /*<<< orphan*/  parent_name; int /*<<< orphan*/  name; } ;
struct aspeed_clk_soc_data {int /*<<< orphan*/  eclk_div_table; int /*<<< orphan*/  div_table; int /*<<< orphan*/  mac_div_table; struct regmap* (* calc_pll ) (char*,int) ;} ;
struct TYPE_4__ {struct regmap** hws; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct aspeed_gate_data*) ; 
 size_t ASPEED_CLK_24M ; 
 size_t ASPEED_CLK_BCLK ; 
 size_t ASPEED_CLK_ECLK ; 
 size_t ASPEED_CLK_ECLK_MUX ; 
 size_t ASPEED_CLK_LHCLK ; 
 size_t ASPEED_CLK_MAC ; 
 size_t ASPEED_CLK_MPLL ; 
 size_t ASPEED_CLK_SDIO ; 
 scalar_t__ ASPEED_CLK_SELECTION ; 
 scalar_t__ ASPEED_CLK_SELECTION_2 ; 
 size_t ASPEED_CLK_UART ; 
 int /*<<< orphan*/  ASPEED_MISC_CTRL ; 
 int /*<<< orphan*/  ASPEED_MPLL_PARAM ; 
 int CLK_GATE_SET_TO_DISABLE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int UART_DIV13_EN ; 
 TYPE_2__* aspeed_clk_data ; 
 struct regmap* aspeed_clk_hw_register_gate (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regmap*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aspeed_clk_lock ; 
 struct aspeed_gate_data* aspeed_gates ; 
 int /*<<< orphan*/  aspeed_reset_ops ; 
 struct aspeed_gate_data* aspeed_resets ; 
 struct regmap* clk_hw_register_divider_table (struct device*,char*,char*,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* clk_hw_register_fixed_rate (struct device*,char*,char*,int /*<<< orphan*/ ,int) ; 
 struct regmap* clk_hw_register_gate (struct device*,char*,char*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* clk_hw_register_mux (struct device*,char*,struct aspeed_gate_data*,int,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct aspeed_reset* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (struct device*,TYPE_1__*) ; 
 struct aspeed_gate_data* eclk_parent_names ; 
 struct aspeed_clk_soc_data* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ scu_base ; 
 struct regmap* stub1 (char*,int) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int aspeed_clk_probe(struct platform_device *pdev)
{
	const struct aspeed_clk_soc_data *soc_data;
	struct device *dev = &pdev->dev;
	struct aspeed_reset *ar;
	struct regmap *map;
	struct clk_hw *hw;
	u32 val, rate;
	int i, ret;

	map = syscon_node_to_regmap(dev->of_node);
	if (IS_ERR(map)) {
		dev_err(dev, "no syscon regmap\n");
		return PTR_ERR(map);
	}

	ar = devm_kzalloc(dev, sizeof(*ar), GFP_KERNEL);
	if (!ar)
		return -ENOMEM;

	ar->map = map;
	ar->rcdev.owner = THIS_MODULE;
	ar->rcdev.nr_resets = ARRAY_SIZE(aspeed_resets);
	ar->rcdev.ops = &aspeed_reset_ops;
	ar->rcdev.of_node = dev->of_node;

	ret = devm_reset_controller_register(dev, &ar->rcdev);
	if (ret) {
		dev_err(dev, "could not register reset controller\n");
		return ret;
	}

	/* SoC generations share common layouts but have different divisors */
	soc_data = of_device_get_match_data(dev);
	if (!soc_data) {
		dev_err(dev, "no match data for platform\n");
		return -EINVAL;
	}

	/* UART clock div13 setting */
	regmap_read(map, ASPEED_MISC_CTRL, &val);
	if (val & UART_DIV13_EN)
		rate = 24000000 / 13;
	else
		rate = 24000000;
	/* TODO: Find the parent data for the uart clock */
	hw = clk_hw_register_fixed_rate(dev, "uart", NULL, 0, rate);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_UART] = hw;

	/*
	 * Memory controller (M-PLL) PLL. This clock is configured by the
	 * bootloader, and is exposed to Linux as a read-only clock rate.
	 */
	regmap_read(map, ASPEED_MPLL_PARAM, &val);
	hw = soc_data->calc_pll("mpll", val);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_MPLL] =	hw;

	/* SD/SDIO clock divider and gate */
	hw = clk_hw_register_gate(dev, "sd_extclk_gate", "hpll", 0,
				  scu_base + ASPEED_CLK_SELECTION, 15, 0,
				  &aspeed_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	hw = clk_hw_register_divider_table(dev, "sd_extclk", "sd_extclk_gate",
			0, scu_base + ASPEED_CLK_SELECTION, 12, 3, 0,
			soc_data->div_table,
			&aspeed_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_SDIO] = hw;

	/* MAC AHB bus clock divider */
	hw = clk_hw_register_divider_table(dev, "mac", "hpll", 0,
			scu_base + ASPEED_CLK_SELECTION, 16, 3, 0,
			soc_data->mac_div_table,
			&aspeed_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_MAC] = hw;

	/* LPC Host (LHCLK) clock divider */
	hw = clk_hw_register_divider_table(dev, "lhclk", "hpll", 0,
			scu_base + ASPEED_CLK_SELECTION, 20, 3, 0,
			soc_data->div_table,
			&aspeed_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_LHCLK] = hw;

	/* P-Bus (BCLK) clock divider */
	hw = clk_hw_register_divider_table(dev, "bclk", "hpll", 0,
			scu_base + ASPEED_CLK_SELECTION_2, 0, 2, 0,
			soc_data->div_table,
			&aspeed_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_BCLK] = hw;

	/* Fixed 24MHz clock */
	hw = clk_hw_register_fixed_rate(NULL, "fixed-24m", "clkin",
					0, 24000000);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_24M] = hw;

	hw = clk_hw_register_mux(dev, "eclk-mux", eclk_parent_names,
				 ARRAY_SIZE(eclk_parent_names), 0,
				 scu_base + ASPEED_CLK_SELECTION, 2, 0x3, 0,
				 &aspeed_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_ECLK_MUX] = hw;

	hw = clk_hw_register_divider_table(dev, "eclk", "eclk-mux", 0,
					   scu_base + ASPEED_CLK_SELECTION, 28,
					   3, 0, soc_data->eclk_div_table,
					   &aspeed_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_clk_data->hws[ASPEED_CLK_ECLK] = hw;

	/*
	 * TODO: There are a number of clocks that not included in this driver
	 * as more information is required:
	 *   D2-PLL
	 *   D-PLL
	 *   YCLK
	 *   RGMII
	 *   RMII
	 *   UART[1..5] clock source mux
	 */

	for (i = 0; i < ARRAY_SIZE(aspeed_gates); i++) {
		const struct aspeed_gate_data *gd = &aspeed_gates[i];
		u32 gate_flags;

		/* Special case: the USB port 1 clock (bit 14) is always
		 * working the opposite way from the other ones.
		 */
		gate_flags = (gd->clock_idx == 14) ? 0 : CLK_GATE_SET_TO_DISABLE;
		hw = aspeed_clk_hw_register_gate(dev,
				gd->name,
				gd->parent_name,
				gd->flags,
				map,
				gd->clock_idx,
				gd->reset_idx,
				gate_flags,
				&aspeed_clk_lock);
		if (IS_ERR(hw))
			return PTR_ERR(hw);
		aspeed_clk_data->hws[i] = hw;
	}

	return 0;
}
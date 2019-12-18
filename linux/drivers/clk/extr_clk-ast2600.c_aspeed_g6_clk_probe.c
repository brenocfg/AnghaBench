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
struct TYPE_4__ {struct regmap** hws; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct aspeed_gate_data*) ; 
 size_t ASPEED_CLK_BCLK ; 
 size_t ASPEED_CLK_D1CLK ; 
 size_t ASPEED_CLK_ECLK ; 
 size_t ASPEED_CLK_EMMC ; 
 size_t ASPEED_CLK_LHCLK ; 
 size_t ASPEED_CLK_MAC12 ; 
 size_t ASPEED_CLK_MAC34 ; 
 size_t ASPEED_CLK_SDIO ; 
 size_t ASPEED_CLK_UART ; 
 size_t ASPEED_CLK_UARTX ; 
 size_t ASPEED_CLK_VCLK ; 
 scalar_t__ ASPEED_G6_CLK_SELECTION1 ; 
 scalar_t__ ASPEED_G6_CLK_SELECTION2 ; 
 scalar_t__ ASPEED_G6_CLK_SELECTION4 ; 
 int ASPEED_G6_MISC_CTRL ; 
 int BIT (int) ; 
 int CLK_GATE_SET_TO_DISABLE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GENMASK (int,int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int UART_DIV13_EN ; 
 TYPE_2__* aspeed_g6_clk_data ; 
 struct regmap* aspeed_g6_clk_hw_register_gate (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct regmap*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  aspeed_g6_clk_lock ; 
 struct aspeed_gate_data* aspeed_g6_gates ; 
 int /*<<< orphan*/  aspeed_g6_reset_ops ; 
 int /*<<< orphan*/  ast2600_div_table ; 
 int /*<<< orphan*/  ast2600_eclk_div_table ; 
 int /*<<< orphan*/  ast2600_mac_div_table ; 
 struct regmap* clk_hw_register_divider_table (struct device*,char*,char*,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* clk_hw_register_fixed_rate (struct device*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct regmap* clk_hw_register_gate (struct device*,char*,char*,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct regmap* clk_hw_register_mux (struct device*,char*,struct aspeed_gate_data*,int,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct aspeed_gate_data* d1clk_parent_names ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct aspeed_reset* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_reset_controller_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,int,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,int,int) ; 
 scalar_t__ scu_g6_base ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 
 struct aspeed_gate_data* vclk_parent_names ; 

__attribute__((used)) static int aspeed_g6_clk_probe(struct platform_device *pdev)
{
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
	ar->rcdev.nr_resets = 64;
	ar->rcdev.ops = &aspeed_g6_reset_ops;
	ar->rcdev.of_node = dev->of_node;

	ret = devm_reset_controller_register(dev, &ar->rcdev);
	if (ret) {
		dev_err(dev, "could not register reset controller\n");
		return ret;
	}

	/* UART clock div13 setting */
	regmap_read(map, ASPEED_G6_MISC_CTRL, &val);
	if (val & UART_DIV13_EN)
		rate = 24000000 / 13;
	else
		rate = 24000000;
	hw = clk_hw_register_fixed_rate(dev, "uart", NULL, 0, rate);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_UART] = hw;

	/* UART6~13 clock div13 setting */
	regmap_read(map, 0x80, &val);
	if (val & BIT(31))
		rate = 24000000 / 13;
	else
		rate = 24000000;
	hw = clk_hw_register_fixed_rate(dev, "uartx", NULL, 0, rate);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_UARTX] = hw;

	/* EMMC ext clock divider */
	hw = clk_hw_register_gate(dev, "emmc_extclk_gate", "hpll", 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 15, 0,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	hw = clk_hw_register_divider_table(dev, "emmc_extclk", "emmc_extclk_gate", 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 12, 3, 0,
			ast2600_div_table,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_EMMC] = hw;

	/* SD/SDIO clock divider and gate */
	hw = clk_hw_register_gate(dev, "sd_extclk_gate", "hpll", 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION4, 31, 0,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	hw = clk_hw_register_divider_table(dev, "sd_extclk", "sd_extclk_gate",
			0, scu_g6_base + ASPEED_G6_CLK_SELECTION4, 28, 3, 0,
			ast2600_div_table,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_SDIO] = hw;

	/* MAC1/2 AHB bus clock divider */
	hw = clk_hw_register_divider_table(dev, "mac12", "hpll", 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 16, 3, 0,
			ast2600_mac_div_table,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_MAC12] = hw;

	/* MAC3/4 AHB bus clock divider */
	hw = clk_hw_register_divider_table(dev, "mac34", "hpll", 0,
			scu_g6_base + 0x310, 24, 3, 0,
			ast2600_mac_div_table,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_MAC34] = hw;

	/* LPC Host (LHCLK) clock divider */
	hw = clk_hw_register_divider_table(dev, "lhclk", "hpll", 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 20, 3, 0,
			ast2600_div_table,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_LHCLK] = hw;

	/* gfx d1clk : use dp clk */
	regmap_update_bits(map, ASPEED_G6_CLK_SELECTION1, GENMASK(10, 8), BIT(10));
	/* SoC Display clock selection */
	hw = clk_hw_register_mux(dev, "d1clk", d1clk_parent_names,
			ARRAY_SIZE(d1clk_parent_names), 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 8, 3, 0,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_D1CLK] = hw;

	/* d1 clk div 0x308[17:15] x [14:12] - 8,7,6,5,4,3,2,1 */
	regmap_write(map, 0x308, 0x12000); /* 3x3 = 9 */

	/* P-Bus (BCLK) clock divider */
	hw = clk_hw_register_divider_table(dev, "bclk", "hpll", 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 20, 3, 0,
			ast2600_div_table,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_BCLK] = hw;

	/* Video Capture clock selection */
	hw = clk_hw_register_mux(dev, "vclk", vclk_parent_names,
			ARRAY_SIZE(vclk_parent_names), 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION2, 12, 3, 0,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_VCLK] = hw;

	/* Video Engine clock divider */
	hw = clk_hw_register_divider_table(dev, "eclk", NULL, 0,
			scu_g6_base + ASPEED_G6_CLK_SELECTION1, 28, 3, 0,
			ast2600_eclk_div_table,
			&aspeed_g6_clk_lock);
	if (IS_ERR(hw))
		return PTR_ERR(hw);
	aspeed_g6_clk_data->hws[ASPEED_CLK_ECLK] = hw;

	for (i = 0; i < ARRAY_SIZE(aspeed_g6_gates); i++) {
		const struct aspeed_gate_data *gd = &aspeed_g6_gates[i];
		u32 gate_flags;

		/*
		 * Special case: the USB port 1 clock (bit 14) is always
		 * working the opposite way from the other ones.
		 */
		gate_flags = (gd->clock_idx == 14) ? 0 : CLK_GATE_SET_TO_DISABLE;
		hw = aspeed_g6_clk_hw_register_gate(dev,
				gd->name,
				gd->parent_name,
				gd->flags,
				map,
				gd->clock_idx,
				gd->reset_idx,
				gate_flags,
				&aspeed_g6_clk_lock);
		if (IS_ERR(hw))
			return PTR_ERR(hw);
		aspeed_g6_clk_data->hws[i] = hw;
	}

	return 0;
}
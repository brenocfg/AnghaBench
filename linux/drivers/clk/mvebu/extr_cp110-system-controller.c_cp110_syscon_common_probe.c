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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct clk_hw_onecell_data {int num; struct regmap** hws; } ;
typedef  struct regmap clk_hw ;

/* Variables and functions */
 int ARRAY_SIZE (char**) ; 
 int CP110_CLK_NUM ; 
 size_t CP110_CORE_CORE ; 
 size_t CP110_CORE_NAND ; 
 size_t CP110_CORE_PLL0 ; 
 size_t CP110_CORE_PPV2 ; 
 size_t CP110_CORE_SDIO ; 
 size_t CP110_CORE_X2CORE ; 
#define  CP110_GATE_EIP150 137 
#define  CP110_GATE_EIP197 136 
#define  CP110_GATE_GOP_DP 135 
#define  CP110_GATE_MAIN 134 
#define  CP110_GATE_MG 133 
#define  CP110_GATE_NAND 132 
#define  CP110_GATE_PCIE_X4 131 
#define  CP110_GATE_PCIE_XOR 130 
#define  CP110_GATE_PPV2 129 
#define  CP110_GATE_SDIO 128 
 int CP110_MAX_CORE_CLOCKS ; 
 int CP110_MAX_GATABLE_CLOCKS ; 
 int /*<<< orphan*/  CP110_NAND_FLASH_CLK_CTRL_REG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int NF_CLOCK_SEL_400_MASK ; 
 int PTR_ERR (struct regmap*) ; 
 void* ap_cp_unique_name (struct device*,struct device_node*,char*) ; 
 struct regmap* clk_hw_register_fixed_factor (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ ,int,int) ; 
 struct regmap* clk_hw_register_fixed_rate (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clk_hw_unregister_fixed_factor (struct regmap*) ; 
 int /*<<< orphan*/  clk_hw_unregister_fixed_rate (struct regmap*) ; 
 int /*<<< orphan*/  cp110_of_clk_get ; 
 struct regmap* cp110_register_gate (char*,char const*,struct regmap*,int) ; 
 int /*<<< orphan*/  cp110_unregister_gate (struct regmap*) ; 
 struct clk_hw_onecell_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 char** gate_base_names ; 
 int of_clk_add_hw_provider (struct device_node*,int /*<<< orphan*/ ,struct clk_hw_onecell_data*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct regmap**) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 

__attribute__((used)) static int cp110_syscon_common_probe(struct platform_device *pdev,
				     struct device_node *syscon_node)
{
	struct regmap *regmap;
	struct device *dev = &pdev->dev;
	struct device_node *np = dev->of_node;
	const char *ppv2_name, *pll0_name, *core_name, *x2core_name, *nand_name,
		*sdio_name;
	struct clk_hw_onecell_data *cp110_clk_data;
	struct clk_hw *hw, **cp110_clks;
	u32 nand_clk_ctrl;
	int i, ret;
	char *gate_name[ARRAY_SIZE(gate_base_names)];

	regmap = syscon_node_to_regmap(syscon_node);
	if (IS_ERR(regmap))
		return PTR_ERR(regmap);

	ret = regmap_read(regmap, CP110_NAND_FLASH_CLK_CTRL_REG,
			  &nand_clk_ctrl);
	if (ret)
		return ret;

	cp110_clk_data = devm_kzalloc(dev, sizeof(*cp110_clk_data) +
				      sizeof(struct clk_hw *) * CP110_CLK_NUM,
				      GFP_KERNEL);
	if (!cp110_clk_data)
		return -ENOMEM;

	cp110_clks = cp110_clk_data->hws;
	cp110_clk_data->num = CP110_CLK_NUM;

	/* Register the PLL0 which is the root of the hw tree */
	pll0_name = ap_cp_unique_name(dev, syscon_node, "pll0");
	hw = clk_hw_register_fixed_rate(NULL, pll0_name, NULL, 0,
					1000 * 1000 * 1000);
	if (IS_ERR(hw)) {
		ret = PTR_ERR(hw);
		goto fail_pll0;
	}

	cp110_clks[CP110_CORE_PLL0] = hw;

	/* PPv2 is PLL0/3 */
	ppv2_name = ap_cp_unique_name(dev, syscon_node, "ppv2-core");
	hw = clk_hw_register_fixed_factor(NULL, ppv2_name, pll0_name, 0, 1, 3);
	if (IS_ERR(hw)) {
		ret = PTR_ERR(hw);
		goto fail_ppv2;
	}

	cp110_clks[CP110_CORE_PPV2] = hw;

	/* X2CORE clock is PLL0/2 */
	x2core_name = ap_cp_unique_name(dev, syscon_node, "x2core");
	hw = clk_hw_register_fixed_factor(NULL, x2core_name, pll0_name,
					  0, 1, 2);
	if (IS_ERR(hw)) {
		ret = PTR_ERR(hw);
		goto fail_eip;
	}

	cp110_clks[CP110_CORE_X2CORE] = hw;

	/* Core clock is X2CORE/2 */
	core_name = ap_cp_unique_name(dev, syscon_node, "core");
	hw = clk_hw_register_fixed_factor(NULL, core_name, x2core_name,
					  0, 1, 2);
	if (IS_ERR(hw)) {
		ret = PTR_ERR(hw);
		goto fail_core;
	}

	cp110_clks[CP110_CORE_CORE] = hw;
	/* NAND can be either PLL0/2.5 or core clock */
	nand_name = ap_cp_unique_name(dev, syscon_node, "nand-core");
	if (nand_clk_ctrl & NF_CLOCK_SEL_400_MASK)
		hw = clk_hw_register_fixed_factor(NULL, nand_name,
						   pll0_name, 0, 2, 5);
	else
		hw = clk_hw_register_fixed_factor(NULL, nand_name,
						   core_name, 0, 1, 1);
	if (IS_ERR(hw)) {
		ret = PTR_ERR(hw);
		goto fail_nand;
	}

	cp110_clks[CP110_CORE_NAND] = hw;

	/* SDIO clock is PLL0/2.5 */
	sdio_name = ap_cp_unique_name(dev, syscon_node, "sdio-core");
	hw = clk_hw_register_fixed_factor(NULL, sdio_name,
					  pll0_name, 0, 2, 5);
	if (IS_ERR(hw)) {
		ret = PTR_ERR(hw);
		goto fail_sdio;
	}

	cp110_clks[CP110_CORE_SDIO] = hw;

	/* create the unique name for all the gate clocks */
	for (i = 0; i < ARRAY_SIZE(gate_base_names); i++)
		gate_name[i] =	ap_cp_unique_name(dev, syscon_node,
						  gate_base_names[i]);

	for (i = 0; i < ARRAY_SIZE(gate_base_names); i++) {
		const char *parent;

		if (gate_name[i] == NULL)
			continue;

		switch (i) {
		case CP110_GATE_NAND:
			parent = nand_name;
			break;
		case CP110_GATE_MG:
		case CP110_GATE_GOP_DP:
		case CP110_GATE_PPV2:
			parent = ppv2_name;
			break;
		case CP110_GATE_SDIO:
			parent = sdio_name;
			break;
		case CP110_GATE_MAIN:
		case CP110_GATE_PCIE_XOR:
		case CP110_GATE_PCIE_X4:
		case CP110_GATE_EIP150:
		case CP110_GATE_EIP197:
			parent = x2core_name;
			break;
		default:
			parent = core_name;
			break;
		}
		hw = cp110_register_gate(gate_name[i], parent, regmap, i);

		if (IS_ERR(hw)) {
			ret = PTR_ERR(hw);
			goto fail_gate;
		}

		cp110_clks[CP110_MAX_CORE_CLOCKS + i] = hw;
	}

	ret = of_clk_add_hw_provider(np, cp110_of_clk_get, cp110_clk_data);
	if (ret)
		goto fail_clk_add;

	platform_set_drvdata(pdev, cp110_clks);

	return 0;

fail_clk_add:
fail_gate:
	for (i = 0; i < CP110_MAX_GATABLE_CLOCKS; i++) {
		hw = cp110_clks[CP110_MAX_CORE_CLOCKS + i];

		if (hw)
			cp110_unregister_gate(hw);
	}

	clk_hw_unregister_fixed_factor(cp110_clks[CP110_CORE_SDIO]);
fail_sdio:
	clk_hw_unregister_fixed_factor(cp110_clks[CP110_CORE_NAND]);
fail_nand:
	clk_hw_unregister_fixed_factor(cp110_clks[CP110_CORE_CORE]);
fail_core:
	clk_hw_unregister_fixed_factor(cp110_clks[CP110_CORE_X2CORE]);
fail_eip:
	clk_hw_unregister_fixed_factor(cp110_clks[CP110_CORE_PPV2]);
fail_ppv2:
	clk_hw_unregister_fixed_rate(cp110_clks[CP110_CORE_PLL0]);
fail_pll0:
	return ret;
}
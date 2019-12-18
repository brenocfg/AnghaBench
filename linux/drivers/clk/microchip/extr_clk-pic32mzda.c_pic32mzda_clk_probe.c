#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct device_node* of_node; } ;
struct platform_device {TYPE_3__ dev; } ;
struct TYPE_8__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_9__ {int clk_num; struct clk** clks; } ;
struct pic32_clk_common {int /*<<< orphan*/  reg_lock; struct clk* iobase; TYPE_3__* dev; } ;
struct pic32mzda_clk_data {TYPE_1__ failsafe_notifier; TYPE_2__ onecell_data; struct clk** clks; struct pic32_clk_common core; } ;
struct device_node {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (size_t*) ; 
 size_t BFRCCLK ; 
 int /*<<< orphan*/  CLK_DIVIDER_POWER_OF_TWO ; 
 int ENOMEM ; 
 size_t FRCCLK ; 
 size_t FRCDIVCLK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 size_t LPRCCLK ; 
 int MAXCLKS ; 
 int /*<<< orphan*/  OSC_FRCDIV_MASK ; 
 int /*<<< orphan*/  OSC_FRCDIV_SHIFT ; 
 int PB1CLK ; 
 int PB7CLK ; 
 size_t PLLCLK ; 
 int /*<<< orphan*/  PLL_ICLK_SHIFT ; 
 size_t POSCCLK ; 
 int PTR_ERR (struct clk*) ; 
 int REF1CLK ; 
 int REF5CLK ; 
 size_t SCLK ; 
 size_t SOSCCLK ; 
 size_t UPLLCLK ; 
 int /*<<< orphan*/  __clk_get_name (struct clk*) ; 
 scalar_t__ clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  clk_register_clkdev (struct clk*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct clk* clk_register_divider (TYPE_3__*,char*,char*,int /*<<< orphan*/ ,struct clk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk* clk_register_fixed_rate (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct clk* clk_register_mux (TYPE_3__*,char*,char const* const*,int,int /*<<< orphan*/ ,struct clk*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (TYPE_3__*,char*,...) ; 
 struct pic32mzda_clk_data* devm_kzalloc (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int of_clk_add_provider (struct device_node*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_clk_src_onecell_get ; 
 scalar_t__ of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 struct clk* of_io_request_and_map (struct device_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_full_name (struct device_node*) ; 
 int /*<<< orphan*/ * periph_clocks ; 
 int /*<<< orphan*/  pic32_fscm_nmi ; 
 struct clk* pic32_periph_clk_register (int /*<<< orphan*/ *,struct pic32_clk_common*) ; 
 struct clk* pic32_refo_clk_register (int /*<<< orphan*/ *,struct pic32_clk_common*) ; 
 struct clk* pic32_sosc_clk_register (int /*<<< orphan*/ *,struct pic32_clk_common*) ; 
 struct clk* pic32_spll_clk_register (int /*<<< orphan*/ *,struct pic32_clk_common*) ; 
 struct clk* pic32_sys_clk_register (int /*<<< orphan*/ *,struct pic32_clk_common*) ; 
 size_t* pic32mzda_critical_clks ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/ * ref_clks ; 
 int register_nmi_notifier (TYPE_1__*) ; 
 int /*<<< orphan*/  sosc_clk ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sys_mux_clk ; 
 int /*<<< orphan*/  sys_pll ; 

__attribute__((used)) static int pic32mzda_clk_probe(struct platform_device *pdev)
{
	const char *const pll_mux_parents[] = {"posc_clk", "frc_clk"};
	struct device_node *np = pdev->dev.of_node;
	struct pic32mzda_clk_data *cd;
	struct pic32_clk_common *core;
	struct clk *pll_mux_clk, *clk;
	struct clk **clks;
	int nr_clks, i, ret;

	cd = devm_kzalloc(&pdev->dev, sizeof(*cd), GFP_KERNEL);
	if (!cd)
		return -ENOMEM;

	core = &cd->core;
	core->iobase = of_io_request_and_map(np, 0, of_node_full_name(np));
	if (IS_ERR(core->iobase)) {
		dev_err(&pdev->dev, "pic32-clk: failed to map registers\n");
		return PTR_ERR(core->iobase);
	}

	spin_lock_init(&core->reg_lock);
	core->dev = &pdev->dev;
	clks = &cd->clks[0];

	/* register fixed rate clocks */
	clks[POSCCLK] = clk_register_fixed_rate(&pdev->dev, "posc_clk", NULL,
						0, 24000000);
	clks[FRCCLK] =  clk_register_fixed_rate(&pdev->dev, "frc_clk", NULL,
						0, 8000000);
	clks[BFRCCLK] = clk_register_fixed_rate(&pdev->dev, "bfrc_clk", NULL,
						0, 8000000);
	clks[LPRCCLK] = clk_register_fixed_rate(&pdev->dev, "lprc_clk", NULL,
						0, 32000);
	clks[UPLLCLK] = clk_register_fixed_rate(&pdev->dev, "usbphy_clk", NULL,
						0, 24000000);
	/* fixed rate (optional) clock */
	if (of_find_property(np, "microchip,pic32mzda-sosc", NULL)) {
		pr_info("pic32-clk: dt requests SOSC.\n");
		clks[SOSCCLK] = pic32_sosc_clk_register(&sosc_clk, core);
	}
	/* divider clock */
	clks[FRCDIVCLK] = clk_register_divider(&pdev->dev, "frcdiv_clk",
					       "frc_clk", 0,
					       core->iobase,
					       OSC_FRCDIV_SHIFT,
					       OSC_FRCDIV_MASK,
					       CLK_DIVIDER_POWER_OF_TWO,
					       &core->reg_lock);
	/* PLL ICLK mux */
	pll_mux_clk = clk_register_mux(&pdev->dev, "spll_mux_clk",
				       pll_mux_parents, 2, 0,
				       core->iobase + 0x020,
				       PLL_ICLK_SHIFT, 1, 0, &core->reg_lock);
	if (IS_ERR(pll_mux_clk))
		pr_err("spll_mux_clk: clk register failed\n");

	/* PLL */
	clks[PLLCLK] = pic32_spll_clk_register(&sys_pll, core);
	/* SYSTEM clock */
	clks[SCLK] = pic32_sys_clk_register(&sys_mux_clk, core);
	/* Peripheral bus clocks */
	for (nr_clks = PB1CLK, i = 0; nr_clks <= PB7CLK; i++, nr_clks++)
		clks[nr_clks] = pic32_periph_clk_register(&periph_clocks[i],
							  core);
	/* Reference oscillator clock */
	for (nr_clks = REF1CLK, i = 0; nr_clks <= REF5CLK; i++, nr_clks++)
		clks[nr_clks] = pic32_refo_clk_register(&ref_clks[i], core);

	/* register clkdev */
	for (i = 0; i < MAXCLKS; i++) {
		if (IS_ERR(clks[i]))
			continue;
		clk_register_clkdev(clks[i], NULL, __clk_get_name(clks[i]));
	}

	/* register clock provider */
	cd->onecell_data.clks = clks;
	cd->onecell_data.clk_num = MAXCLKS;
	ret = of_clk_add_provider(np, of_clk_src_onecell_get,
				  &cd->onecell_data);
	if (ret)
		return ret;

	/* force enable critical clocks */
	for (i = 0; i < ARRAY_SIZE(pic32mzda_critical_clks); i++) {
		clk = clks[pic32mzda_critical_clks[i]];
		if (clk_prepare_enable(clk))
			dev_err(&pdev->dev, "clk_prepare_enable(%s) failed\n",
				__clk_get_name(clk));
	}

	/* register NMI for failsafe clock monitor */
	cd->failsafe_notifier.notifier_call = pic32_fscm_nmi;
	return register_nmi_notifier(&cd->failsafe_notifier);
}
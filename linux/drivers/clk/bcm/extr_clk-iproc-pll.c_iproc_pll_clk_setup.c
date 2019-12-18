#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iproc_pll_vco_param {int dummy; } ;
struct iproc_pll_ctrl {int flags; } ;
struct TYPE_3__ {struct clk_init_data* init; } ;
struct iproc_pll {unsigned int num; scalar_t__ control_base; scalar_t__ pwr_base; scalar_t__ asiu_base; scalar_t__ status_base; unsigned int num_vco_entries; TYPE_1__** hws; TYPE_1__ hw; struct iproc_pll_ctrl const* ctrl; struct iproc_pll* pll; struct iproc_pll_vco_param const* vco_param; } ;
struct iproc_clk_ctrl {int flags; } ;
struct iproc_clk {unsigned int num; scalar_t__ control_base; scalar_t__ pwr_base; scalar_t__ asiu_base; scalar_t__ status_base; unsigned int num_vco_entries; TYPE_1__** hws; TYPE_1__ hw; struct iproc_pll_ctrl const* ctrl; struct iproc_clk* pll; struct iproc_pll_vco_param const* vco_param; } ;
struct device_node {char* name; } ;
struct clk_init_data {char* name; char const** parent_names; int num_parents; scalar_t__ flags; int /*<<< orphan*/ * ops; } ;
struct clk_hw_onecell_data {unsigned int num; scalar_t__ control_base; scalar_t__ pwr_base; scalar_t__ asiu_base; scalar_t__ status_base; unsigned int num_vco_entries; TYPE_1__** hws; TYPE_1__ hw; struct iproc_pll_ctrl const* ctrl; struct clk_hw_onecell_data* pll; struct iproc_pll_vco_param const* vco_param; } ;
typedef  int /*<<< orphan*/  init ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IPROC_CLK_PLL_ASIU ; 
 int IPROC_CLK_PLL_SPLIT_STAT_CTRL ; 
 scalar_t__ WARN_ON (int) ; 
 int clk_hw_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  clk_hw_unregister (TYPE_1__*) ; 
 int /*<<< orphan*/  hws ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  iproc_clk_ops ; 
 int /*<<< orphan*/  iproc_pll_ops ; 
 int /*<<< orphan*/  iproc_pll_sw_cfg (struct iproc_pll*) ; 
 struct iproc_pll* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iproc_pll*) ; 
 struct iproc_pll* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct clk_init_data*,int /*<<< orphan*/ ,int) ; 
 int of_clk_add_hw_provider (struct device_node*,int /*<<< orphan*/ ,struct iproc_pll*) ; 
 char* of_clk_get_parent_name (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_clk_hw_onecell_get ; 
 void* of_iomap (struct device_node*,int) ; 
 int of_property_read_string_index (struct device_node*,char*,int,char const**) ; 
 int struct_size (struct iproc_pll*,int /*<<< orphan*/ ,unsigned int) ; 

void iproc_pll_clk_setup(struct device_node *node,
			 const struct iproc_pll_ctrl *pll_ctrl,
			 const struct iproc_pll_vco_param *vco,
			 unsigned int num_vco_entries,
			 const struct iproc_clk_ctrl *clk_ctrl,
			 unsigned int num_clks)
{
	int i, ret;
	struct iproc_pll *pll;
	struct iproc_clk *iclk;
	struct clk_init_data init;
	const char *parent_name;
	struct iproc_clk *iclk_array;
	struct clk_hw_onecell_data *clk_data;

	if (WARN_ON(!pll_ctrl) || WARN_ON(!clk_ctrl))
		return;

	pll = kzalloc(sizeof(*pll), GFP_KERNEL);
	if (WARN_ON(!pll))
		return;

	clk_data = kzalloc(struct_size(clk_data, hws, num_clks), GFP_KERNEL);
	if (WARN_ON(!clk_data))
		goto err_clk_data;
	clk_data->num = num_clks;

	iclk_array = kcalloc(num_clks, sizeof(struct iproc_clk), GFP_KERNEL);
	if (WARN_ON(!iclk_array))
		goto err_clks;

	pll->control_base = of_iomap(node, 0);
	if (WARN_ON(!pll->control_base))
		goto err_pll_iomap;

	/* Some SoCs do not require the pwr_base, thus failing is not fatal */
	pll->pwr_base = of_iomap(node, 1);

	/* some PLLs require gating control at the top ASIU level */
	if (pll_ctrl->flags & IPROC_CLK_PLL_ASIU) {
		pll->asiu_base = of_iomap(node, 2);
		if (WARN_ON(!pll->asiu_base))
			goto err_asiu_iomap;
	}

	if (pll_ctrl->flags & IPROC_CLK_PLL_SPLIT_STAT_CTRL) {
		/* Some SoCs have a split status/control.  If this does not
		 * exist, assume they are unified.
		 */
		pll->status_base = of_iomap(node, 2);
		if (!pll->status_base)
			goto err_status_iomap;
	} else
		pll->status_base = pll->control_base;

	/* initialize and register the PLL itself */
	pll->ctrl = pll_ctrl;

	iclk = &iclk_array[0];
	iclk->pll = pll;

	init.name = node->name;
	init.ops = &iproc_pll_ops;
	init.flags = 0;
	parent_name = of_clk_get_parent_name(node, 0);
	init.parent_names = (parent_name ? &parent_name : NULL);
	init.num_parents = (parent_name ? 1 : 0);
	iclk->hw.init = &init;

	if (vco) {
		pll->num_vco_entries = num_vco_entries;
		pll->vco_param = vco;
	}

	iproc_pll_sw_cfg(pll);

	ret = clk_hw_register(NULL, &iclk->hw);
	if (WARN_ON(ret))
		goto err_pll_register;

	clk_data->hws[0] = &iclk->hw;

	/* now initialize and register all leaf clocks */
	for (i = 1; i < num_clks; i++) {
		const char *clk_name;

		memset(&init, 0, sizeof(init));
		parent_name = node->name;

		ret = of_property_read_string_index(node, "clock-output-names",
						    i, &clk_name);
		if (WARN_ON(ret))
			goto err_clk_register;

		iclk = &iclk_array[i];
		iclk->pll = pll;
		iclk->ctrl = &clk_ctrl[i];

		init.name = clk_name;
		init.ops = &iproc_clk_ops;
		init.flags = 0;
		init.parent_names = (parent_name ? &parent_name : NULL);
		init.num_parents = (parent_name ? 1 : 0);
		iclk->hw.init = &init;

		ret = clk_hw_register(NULL, &iclk->hw);
		if (WARN_ON(ret))
			goto err_clk_register;

		clk_data->hws[i] = &iclk->hw;
	}

	ret = of_clk_add_hw_provider(node, of_clk_hw_onecell_get, clk_data);
	if (WARN_ON(ret))
		goto err_clk_register;

	return;

err_clk_register:
	while (--i >= 0)
		clk_hw_unregister(clk_data->hws[i]);

err_pll_register:
	if (pll->status_base != pll->control_base)
		iounmap(pll->status_base);

err_status_iomap:
	if (pll->asiu_base)
		iounmap(pll->asiu_base);

err_asiu_iomap:
	if (pll->pwr_base)
		iounmap(pll->pwr_base);

	iounmap(pll->control_base);

err_pll_iomap:
	kfree(iclk_array);

err_clks:
	kfree(clk_data);

err_clk_data:
	kfree(pll);
}
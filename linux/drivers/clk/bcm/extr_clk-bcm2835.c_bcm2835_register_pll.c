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
struct clk_init_data {int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  name; int /*<<< orphan*/ * parent_names; } ;
struct clk_hw {struct clk_init_data* init; } ;
struct bcm2835_pll_data {int /*<<< orphan*/  name; } ;
struct bcm2835_pll {struct clk_hw hw; struct bcm2835_pll_data const* data; struct bcm2835_cprman* cprman; } ;
struct bcm2835_cprman {int /*<<< orphan*/  dev; int /*<<< orphan*/ * real_parent_names; } ;
typedef  int /*<<< orphan*/  init ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_IGNORE_UNUSED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bcm2835_pll_clk_ops ; 
 int devm_clk_hw_register (int /*<<< orphan*/ ,struct clk_hw*) ; 
 struct bcm2835_pll* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct clk_init_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct clk_hw *bcm2835_register_pll(struct bcm2835_cprman *cprman,
					   const struct bcm2835_pll_data *data)
{
	struct bcm2835_pll *pll;
	struct clk_init_data init;
	int ret;

	memset(&init, 0, sizeof(init));

	/* All of the PLLs derive from the external oscillator. */
	init.parent_names = &cprman->real_parent_names[0];
	init.num_parents = 1;
	init.name = data->name;
	init.ops = &bcm2835_pll_clk_ops;
	init.flags = CLK_IGNORE_UNUSED;

	pll = kzalloc(sizeof(*pll), GFP_KERNEL);
	if (!pll)
		return NULL;

	pll->cprman = cprman;
	pll->data = data;
	pll->hw.init = &init;

	ret = devm_clk_hw_register(cprman->dev, &pll->hw);
	if (ret)
		return NULL;
	return &pll->hw;
}
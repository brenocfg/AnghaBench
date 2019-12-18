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
struct dentry {int dummy; } ;
struct debugfs_reg32 {char* name; int /*<<< orphan*/  offset; } ;
struct clk_hw {int dummy; } ;
struct bcm2835_pll_divider_data {int /*<<< orphan*/  a2w_reg; int /*<<< orphan*/  cm_reg; } ;
struct bcm2835_pll_divider {struct bcm2835_pll_divider_data* data; struct bcm2835_cprman* cprman; } ;
struct bcm2835_cprman {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  bcm2835_debugfs_regset (struct bcm2835_cprman*,int /*<<< orphan*/ ,struct debugfs_reg32*,int,struct dentry*) ; 
 struct bcm2835_pll_divider* bcm2835_pll_divider_from_hw (struct clk_hw*) ; 
 struct debugfs_reg32* devm_kcalloc (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bcm2835_pll_divider_debug_init(struct clk_hw *hw,
					   struct dentry *dentry)
{
	struct bcm2835_pll_divider *divider = bcm2835_pll_divider_from_hw(hw);
	struct bcm2835_cprman *cprman = divider->cprman;
	const struct bcm2835_pll_divider_data *data = divider->data;
	struct debugfs_reg32 *regs;

	regs = devm_kcalloc(cprman->dev, 7, sizeof(*regs), GFP_KERNEL);
	if (!regs)
		return;

	regs[0].name = "cm";
	regs[0].offset = data->cm_reg;
	regs[1].name = "a2w";
	regs[1].offset = data->a2w_reg;

	bcm2835_debugfs_regset(cprman, 0, regs, 2, dentry);
}
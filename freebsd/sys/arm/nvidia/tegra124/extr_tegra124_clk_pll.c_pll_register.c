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
struct pll_sc {int /*<<< orphan*/  mnp_bits; int /*<<< orphan*/  pdiv_table; int /*<<< orphan*/  flags; int /*<<< orphan*/  iddq_mask; int /*<<< orphan*/  iddq_reg; int /*<<< orphan*/  lock_enable; int /*<<< orphan*/  lock_mask; int /*<<< orphan*/  misc_reg; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  type; int /*<<< orphan*/  clkdev; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
struct clk_pll_def {int /*<<< orphan*/  mnp_bits; int /*<<< orphan*/  pdiv_table; int /*<<< orphan*/  flags; int /*<<< orphan*/  iddq_mask; int /*<<< orphan*/  iddq_reg; int /*<<< orphan*/  lock_enable; int /*<<< orphan*/  lock_mask; int /*<<< orphan*/  misc_reg; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  type; int /*<<< orphan*/  clkdef; } ;

/* Variables and functions */
 int ENXIO ; 
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clknode_get_device (struct clknode*) ; 
 struct pll_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 
 int /*<<< orphan*/  tegra124_pll_class ; 

__attribute__((used)) static int
pll_register(struct clkdom *clkdom, struct clk_pll_def *clkdef)
{
	struct clknode *clk;
	struct pll_sc *sc;

	clk = clknode_create(clkdom, &tegra124_pll_class, &clkdef->clkdef);
	if (clk == NULL)
		return (ENXIO);

	sc = clknode_get_softc(clk);
	sc->clkdev = clknode_get_device(clk);
	sc->type = clkdef->type;
	sc->base_reg = clkdef->base_reg;
	sc->misc_reg = clkdef->misc_reg;
	sc->lock_mask = clkdef->lock_mask;
	sc->lock_enable = clkdef->lock_enable;
	sc->iddq_reg = clkdef->iddq_reg;
	sc->iddq_mask = clkdef->iddq_mask;
	sc->flags = clkdef->flags;
	sc->pdiv_table = clkdef->pdiv_table;
	sc->mnp_bits = clkdef->mnp_bits;
	clknode_register(clkdom, clk);
	return (0);
}
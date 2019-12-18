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
struct pgate_sc {int /*<<< orphan*/  flags; int /*<<< orphan*/  idx; int /*<<< orphan*/  clkdev; } ;
struct pgate_def {int /*<<< orphan*/  flags; int /*<<< orphan*/  idx; int /*<<< orphan*/  clkdef; } ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;

/* Variables and functions */
 struct clknode* clknode_create (struct clkdom*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clknode_get_device (struct clknode*) ; 
 struct pgate_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_register (struct clkdom*,struct clknode*) ; 
 int /*<<< orphan*/  tegra124_pgate_class ; 

__attribute__((used)) static int
pgate_register(struct clkdom *clkdom, struct pgate_def *clkdef)
{
	struct clknode *clk;
	struct pgate_sc *sc;

	clk = clknode_create(clkdom, &tegra124_pgate_class, &clkdef->clkdef);
	if (clk == NULL)
		return (1);

	sc = clknode_get_softc(clk);
	sc->clkdev = clknode_get_device(clk);
	sc->idx = clkdef->idx;
	sc->flags = clkdef->flags;

	clknode_register(clkdom, clk);
	return (0);
}
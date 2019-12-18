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
struct pll_sc {scalar_t__ type; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 scalar_t__ PLL_E ; 
 struct pll_sc* clknode_get_softc (struct clknode*) ; 
 int pll_disable (struct pll_sc*) ; 
 int pll_enable (struct pll_sc*) ; 
 int plle_enable (struct pll_sc*) ; 

__attribute__((used)) static int
tegra124_pll_set_gate(struct clknode *clknode, bool enable)
{
	int rv;
	struct pll_sc *sc;

	sc = clknode_get_softc(clknode);
	if (enable == 0) {
		rv = pll_disable(sc);
		return(rv);
	}

	if (sc->type == PLL_E)
		rv = plle_enable(sc);
	else
		rv = pll_enable(sc);
	return (rv);
}
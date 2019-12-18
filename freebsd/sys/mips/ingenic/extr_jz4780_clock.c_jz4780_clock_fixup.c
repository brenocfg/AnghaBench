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
struct jz4780_clock_softc {int /*<<< orphan*/  clkdom; int /*<<< orphan*/  dev; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  JZ4780_CLK_UHC ; 
 int /*<<< orphan*/  clkdom_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkdom_xlock (int /*<<< orphan*/ ) ; 
 struct clknode* clknode_find_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clknode_set_freq (struct clknode*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int clknode_set_parent_by_name (struct clknode*,char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
jz4780_clock_fixup(struct jz4780_clock_softc *sc)
{
	struct clknode *clk_uhc;
	int ret;

	/*
	 * Make UHC mux use MPLL as the source. It defaults to OTG_PHY
	 * and that somehow just does not work.
	 */
	clkdom_xlock(sc->clkdom);

	/* Assume the worst */
	ret = ENXIO;

	clk_uhc = clknode_find_by_id(sc->clkdom, JZ4780_CLK_UHC);
	if (clk_uhc != NULL) {
		ret = clknode_set_parent_by_name(clk_uhc, "mpll");
		if (ret != 0)
			device_printf(sc->dev,
			    "unable to reparent uhc clock\n");
		else
			ret = clknode_set_freq(clk_uhc, 48000000, 0, 0);
		if (ret != 0)
			device_printf(sc->dev, "unable to init uhc clock\n");
	} else
		device_printf(sc->dev, "unable to lookup uhc clock\n");

	clkdom_unlock(sc->clkdom);
	return (ret);
}
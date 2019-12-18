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
typedef  int /*<<< orphan*/  uint64_t ;
struct jz4780_clock_softc {int /*<<< orphan*/  clkdom; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/ * clk_t ;

/* Variables and functions */
 int /*<<< orphan*/  JZ4780_CLK_OTGPHY ; 
 scalar_t__ clk_get_by_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ clk_get_freq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ clk_get_parent (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 scalar_t__ clk_set_freq (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_ehci_clk_config(struct jz4780_clock_softc *sc)
{
	clk_t phy_clk, ext_clk;
	uint64_t phy_freq;
	int err;

	phy_clk = NULL;
	ext_clk = NULL;
	err = -1;

	/* Set phy timing by copying it from ext */
	if (clk_get_by_id(sc->dev, sc->clkdom, JZ4780_CLK_OTGPHY,
	    &phy_clk) != 0)
		goto done;
	if (clk_get_parent(phy_clk, &ext_clk) != 0)
		goto done;
	if (clk_get_freq(ext_clk, &phy_freq) != 0)
		goto done;
	if (clk_set_freq(phy_clk, phy_freq, 0) != 0)
		goto done;
	err = 0;
done:
	clk_release(ext_clk);
	clk_release(phy_clk);

	return (err);
}
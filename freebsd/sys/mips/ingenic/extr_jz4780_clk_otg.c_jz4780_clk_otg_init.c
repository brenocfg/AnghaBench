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
typedef  int /*<<< orphan*/  uint32_t ;
struct jz4780_clk_otg_sc {int dummy; } ;
struct clknode {int dummy; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLK_LOCK (struct jz4780_clk_otg_sc*) ; 
 int /*<<< orphan*/  CLK_RD_4 (struct jz4780_clk_otg_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_UNLOCK (struct jz4780_clk_otg_sc*) ; 
 int /*<<< orphan*/  CLK_WR_4 (struct jz4780_clk_otg_sc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JZ_USBPCR1 ; 
 int /*<<< orphan*/  PCR_REFCLK_CORE ; 
 int /*<<< orphan*/  PCR_REFCLK_M ; 
 struct jz4780_clk_otg_sc* clknode_get_softc (struct clknode*) ; 
 int /*<<< orphan*/  clknode_init_parent_idx (struct clknode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_clk_otg_init(struct clknode *clk, device_t dev)
{
	struct jz4780_clk_otg_sc *sc;
	uint32_t reg;

	sc = clknode_get_softc(clk);
	CLK_LOCK(sc);
	/* Force the use fo the core clock */
	reg = CLK_RD_4(sc, JZ_USBPCR1);
	reg &= ~PCR_REFCLK_M;
	reg |= PCR_REFCLK_CORE;
	CLK_WR_4(sc, JZ_USBPCR1, reg);
	CLK_UNLOCK(sc);

	clknode_init_parent_idx(clk, 0);
	return (0);
}
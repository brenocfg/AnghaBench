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
struct jz4780_clk_pll_sc {int /*<<< orphan*/  clk_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGU_PLL_LOCK ; 
 int CLK_RD_4 (struct jz4780_clk_pll_sc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ETIMEDOUT ; 
 int PLL_TIMEOUT ; 
 int REG_VAL (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
jz4780_clk_pll_wait_lock(struct jz4780_clk_pll_sc *sc)
{
	int i;

	for (i = 0;  i < PLL_TIMEOUT; i++) {
		if (CLK_RD_4(sc, sc->clk_reg) & REG_VAL(CGU_PLL_LOCK, 1))
			return (0);
		DELAY(1000);
	}
	return (ETIMEDOUT);
}
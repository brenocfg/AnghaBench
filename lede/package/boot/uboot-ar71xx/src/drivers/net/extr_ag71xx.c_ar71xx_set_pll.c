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
typedef  int uint32_t ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_PLL_BASE ; 
 int KSEG1ADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug (char*,unsigned int,int) ; 
 int readl (int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void ar71xx_set_pll(u32 cfg_reg, u32 pll_reg, u32 pll_val, u32 shift)
{
	uint32_t base = KSEG1ADDR(AR71XX_PLL_BASE);
	u32 t;

	t = readl(base + cfg_reg);
	t &= ~(3 << shift);
	t |=  (2 << shift);
	writel(t, base + cfg_reg);
	udelay(100);

	writel(pll_val, base + pll_reg);

	t |= (3 << shift);
	writel(t, base + cfg_reg);
	udelay(100);

	t &= ~(3 << shift);
	writel(t, base + cfg_reg);
	udelay(100);

	debug("ar71xx: pll_reg %#x: %#x\n", (unsigned int)(base + pll_reg),
       readl(base + pll_reg));
}
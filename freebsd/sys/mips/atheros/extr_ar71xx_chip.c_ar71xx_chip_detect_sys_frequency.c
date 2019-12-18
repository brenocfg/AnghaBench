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

/* Variables and functions */
 int AR71XX_AHB_DIV_MASK ; 
 int AR71XX_AHB_DIV_SHIFT ; 
 int AR71XX_BASE_FREQ ; 
 int AR71XX_CPU_DIV_MASK ; 
 int AR71XX_CPU_DIV_SHIFT ; 
 int AR71XX_DDR_DIV_MASK ; 
 int AR71XX_DDR_DIV_SHIFT ; 
 int AR71XX_PLL_DIV_MASK ; 
 int AR71XX_PLL_DIV_SHIFT ; 
 int /*<<< orphan*/  AR71XX_PLL_REG_CPU_CONFIG ; 
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int u_ar71xx_ahb_freq ; 
 int u_ar71xx_cpu_freq ; 
 int u_ar71xx_ddr_freq ; 
 int u_ar71xx_mdio_freq ; 
 int u_ar71xx_refclk ; 
 int u_ar71xx_uart_freq ; 
 int u_ar71xx_wdt_freq ; 

__attribute__((used)) static void
ar71xx_chip_detect_sys_frequency(void)
{
	uint32_t pll;
	uint32_t freq;
	uint32_t div;

	u_ar71xx_mdio_freq = u_ar71xx_refclk = AR71XX_BASE_FREQ;

	pll = ATH_READ_REG(AR71XX_PLL_REG_CPU_CONFIG);

	div = ((pll >> AR71XX_PLL_DIV_SHIFT) & AR71XX_PLL_DIV_MASK) + 1;
	freq = div * AR71XX_BASE_FREQ;

	div = ((pll >> AR71XX_CPU_DIV_SHIFT) & AR71XX_CPU_DIV_MASK) + 1;
	u_ar71xx_cpu_freq = freq / div;

	div = ((pll >> AR71XX_DDR_DIV_SHIFT) & AR71XX_DDR_DIV_MASK) + 1;
	u_ar71xx_ddr_freq = freq / div;

	div = (((pll >> AR71XX_AHB_DIV_SHIFT) & AR71XX_AHB_DIV_MASK) + 1) * 2;
	u_ar71xx_ahb_freq = u_ar71xx_cpu_freq / div;
	u_ar71xx_wdt_freq = u_ar71xx_cpu_freq / div;
	u_ar71xx_uart_freq = u_ar71xx_cpu_freq / div;
}
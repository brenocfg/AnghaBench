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
 int AR933X_BOOTSTRAP_REF_CLK_40 ; 
 int AR933X_PLL_CLOCK_CTRL_AHB_DIV_MASK ; 
 int AR933X_PLL_CLOCK_CTRL_AHB_DIV_SHIFT ; 
 int AR933X_PLL_CLOCK_CTRL_BYPASS ; 
 int AR933X_PLL_CLOCK_CTRL_CPU_DIV_MASK ; 
 int AR933X_PLL_CLOCK_CTRL_CPU_DIV_SHIFT ; 
 int AR933X_PLL_CLOCK_CTRL_DDR_DIV_MASK ; 
 int AR933X_PLL_CLOCK_CTRL_DDR_DIV_SHIFT ; 
 int /*<<< orphan*/  AR933X_PLL_CLOCK_CTRL_REG ; 
 int AR933X_PLL_CPU_CONFIG_NINT_MASK ; 
 int AR933X_PLL_CPU_CONFIG_NINT_SHIFT ; 
 int AR933X_PLL_CPU_CONFIG_OUTDIV_MASK ; 
 int AR933X_PLL_CPU_CONFIG_OUTDIV_SHIFT ; 
 int AR933X_PLL_CPU_CONFIG_REFDIV_MASK ; 
 int AR933X_PLL_CPU_CONFIG_REFDIV_SHIFT ; 
 int /*<<< orphan*/  AR933X_PLL_CPU_CONFIG_REG ; 
 int /*<<< orphan*/  AR933X_RESET_REG_BOOTSTRAP ; 
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int u_ar71xx_ahb_freq ; 
 int u_ar71xx_cpu_freq ; 
 int u_ar71xx_ddr_freq ; 
 int u_ar71xx_mdio_freq ; 
 int u_ar71xx_refclk ; 
 int u_ar71xx_uart_freq ; 
 int u_ar71xx_wdt_freq ; 

__attribute__((used)) static void
ar933x_chip_detect_sys_frequency(void)
{
	uint32_t clock_ctrl;
	uint32_t cpu_config;
	uint32_t freq;
	uint32_t t;

	t = ATH_READ_REG(AR933X_RESET_REG_BOOTSTRAP);
	if (t & AR933X_BOOTSTRAP_REF_CLK_40)
		u_ar71xx_refclk = (40 * 1000 * 1000);
	else
		u_ar71xx_refclk = (25 * 1000 * 1000);

	clock_ctrl = ATH_READ_REG(AR933X_PLL_CLOCK_CTRL_REG);
	if (clock_ctrl & AR933X_PLL_CLOCK_CTRL_BYPASS) {
		u_ar71xx_cpu_freq = u_ar71xx_refclk;
		u_ar71xx_ahb_freq = u_ar71xx_refclk;
		u_ar71xx_ddr_freq = u_ar71xx_refclk;
	} else {
		cpu_config = ATH_READ_REG(AR933X_PLL_CPU_CONFIG_REG);

		t = (cpu_config >> AR933X_PLL_CPU_CONFIG_REFDIV_SHIFT) &
		    AR933X_PLL_CPU_CONFIG_REFDIV_MASK;
		freq = u_ar71xx_refclk / t;

		t = (cpu_config >> AR933X_PLL_CPU_CONFIG_NINT_SHIFT) &
		    AR933X_PLL_CPU_CONFIG_NINT_MASK;
		freq *= t;

		t = (cpu_config >> AR933X_PLL_CPU_CONFIG_OUTDIV_SHIFT) &
		    AR933X_PLL_CPU_CONFIG_OUTDIV_MASK;
		if (t == 0)
			t = 1;

		freq >>= t;

		t = ((clock_ctrl >> AR933X_PLL_CLOCK_CTRL_CPU_DIV_SHIFT) &
		     AR933X_PLL_CLOCK_CTRL_CPU_DIV_MASK) + 1;
		u_ar71xx_cpu_freq = freq / t;

		t = ((clock_ctrl >> AR933X_PLL_CLOCK_CTRL_DDR_DIV_SHIFT) &
		      AR933X_PLL_CLOCK_CTRL_DDR_DIV_MASK) + 1;
		u_ar71xx_ddr_freq = freq / t;

		t = ((clock_ctrl >> AR933X_PLL_CLOCK_CTRL_AHB_DIV_SHIFT) &
		     AR933X_PLL_CLOCK_CTRL_AHB_DIV_MASK) + 1;
		u_ar71xx_ahb_freq = freq / t;
	}

	/*
	 * On the AR933x, the UART frequency is the reference clock,
	 * not the AHB bus clock.
	 */
	u_ar71xx_uart_freq = u_ar71xx_refclk;

	/*
	 * XXX TODO: check whether the mdio frequency is always the
	 * refclock frequency, or whether it's variable like on the
	 * AR934x.
	 */
	u_ar71xx_mdio_freq = u_ar71xx_refclk;

	/*
	 * XXX check what the watchdog frequency should be?
	 */
	u_ar71xx_wdt_freq = u_ar71xx_ahb_freq;
}
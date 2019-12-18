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
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int QCA953X_BOOTSTRAP_REF_CLK_40 ; 
 int QCA953X_PLL_CLK_CTRL_AHBCLK_FROM_DDRPLL ; 
 int QCA953X_PLL_CLK_CTRL_AHB_PLL_BYPASS ; 
 int QCA953X_PLL_CLK_CTRL_AHB_POST_DIV_MASK ; 
 int QCA953X_PLL_CLK_CTRL_AHB_POST_DIV_SHIFT ; 
 int QCA953X_PLL_CLK_CTRL_CPUCLK_FROM_CPUPLL ; 
 int QCA953X_PLL_CLK_CTRL_CPU_PLL_BYPASS ; 
 int QCA953X_PLL_CLK_CTRL_CPU_POST_DIV_MASK ; 
 int QCA953X_PLL_CLK_CTRL_CPU_POST_DIV_SHIFT ; 
 int QCA953X_PLL_CLK_CTRL_DDRCLK_FROM_DDRPLL ; 
 int QCA953X_PLL_CLK_CTRL_DDR_PLL_BYPASS ; 
 int QCA953X_PLL_CLK_CTRL_DDR_POST_DIV_MASK ; 
 int QCA953X_PLL_CLK_CTRL_DDR_POST_DIV_SHIFT ; 
 int /*<<< orphan*/  QCA953X_PLL_CLK_CTRL_REG ; 
 int QCA953X_PLL_CPU_CONFIG_NFRAC_MASK ; 
 int QCA953X_PLL_CPU_CONFIG_NFRAC_SHIFT ; 
 int QCA953X_PLL_CPU_CONFIG_NINT_MASK ; 
 int QCA953X_PLL_CPU_CONFIG_NINT_SHIFT ; 
 int QCA953X_PLL_CPU_CONFIG_OUTDIV_MASK ; 
 int QCA953X_PLL_CPU_CONFIG_OUTDIV_SHIFT ; 
 int QCA953X_PLL_CPU_CONFIG_REFDIV_MASK ; 
 int QCA953X_PLL_CPU_CONFIG_REFDIV_SHIFT ; 
 int /*<<< orphan*/  QCA953X_PLL_CPU_CONFIG_REG ; 
 int QCA953X_PLL_DDR_CONFIG_NFRAC_MASK ; 
 int QCA953X_PLL_DDR_CONFIG_NFRAC_SHIFT ; 
 int QCA953X_PLL_DDR_CONFIG_NINT_MASK ; 
 int QCA953X_PLL_DDR_CONFIG_NINT_SHIFT ; 
 int QCA953X_PLL_DDR_CONFIG_OUTDIV_MASK ; 
 int QCA953X_PLL_DDR_CONFIG_OUTDIV_SHIFT ; 
 int QCA953X_PLL_DDR_CONFIG_REFDIV_MASK ; 
 int QCA953X_PLL_DDR_CONFIG_REFDIV_SHIFT ; 
 int /*<<< orphan*/  QCA953X_PLL_DDR_CONFIG_REG ; 
 int /*<<< orphan*/  QCA953X_RESET_REG_BOOTSTRAP ; 
 unsigned long u_ar71xx_ahb_freq ; 
 unsigned long u_ar71xx_cpu_freq ; 
 unsigned long u_ar71xx_ddr_freq ; 
 unsigned long u_ar71xx_mdio_freq ; 
 unsigned long u_ar71xx_refclk ; 
 unsigned long u_ar71xx_uart_freq ; 
 unsigned long u_ar71xx_wdt_freq ; 

__attribute__((used)) static void
qca953x_chip_detect_sys_frequency(void)
{
	unsigned long ref_rate;
	unsigned long cpu_rate;
	unsigned long ddr_rate;
	unsigned long ahb_rate;
	uint32_t pll, out_div, ref_div, nint, frac, clk_ctrl, postdiv;
	uint32_t cpu_pll, ddr_pll;
	uint32_t bootstrap;

	bootstrap = ATH_READ_REG(QCA953X_RESET_REG_BOOTSTRAP);
	if (bootstrap &	QCA953X_BOOTSTRAP_REF_CLK_40)
		ref_rate = 40 * 1000 * 1000;
	else
		ref_rate = 25 * 1000 * 1000;

	pll = ATH_READ_REG(QCA953X_PLL_CPU_CONFIG_REG);
	out_div = (pll >> QCA953X_PLL_CPU_CONFIG_OUTDIV_SHIFT) &
		  QCA953X_PLL_CPU_CONFIG_OUTDIV_MASK;
	ref_div = (pll >> QCA953X_PLL_CPU_CONFIG_REFDIV_SHIFT) &
		  QCA953X_PLL_CPU_CONFIG_REFDIV_MASK;
	nint = (pll >> QCA953X_PLL_CPU_CONFIG_NINT_SHIFT) &
	       QCA953X_PLL_CPU_CONFIG_NINT_MASK;
	frac = (pll >> QCA953X_PLL_CPU_CONFIG_NFRAC_SHIFT) &
	       QCA953X_PLL_CPU_CONFIG_NFRAC_MASK;

	cpu_pll = nint * ref_rate / ref_div;
	cpu_pll += frac * (ref_rate >> 6) / ref_div;
	cpu_pll /= (1 << out_div);

	pll = ATH_READ_REG(QCA953X_PLL_DDR_CONFIG_REG);
	out_div = (pll >> QCA953X_PLL_DDR_CONFIG_OUTDIV_SHIFT) &
		  QCA953X_PLL_DDR_CONFIG_OUTDIV_MASK;
	ref_div = (pll >> QCA953X_PLL_DDR_CONFIG_REFDIV_SHIFT) &
		  QCA953X_PLL_DDR_CONFIG_REFDIV_MASK;
	nint = (pll >> QCA953X_PLL_DDR_CONFIG_NINT_SHIFT) &
	       QCA953X_PLL_DDR_CONFIG_NINT_MASK;
	frac = (pll >> QCA953X_PLL_DDR_CONFIG_NFRAC_SHIFT) &
	       QCA953X_PLL_DDR_CONFIG_NFRAC_MASK;

	ddr_pll = nint * ref_rate / ref_div;
	ddr_pll += frac * (ref_rate >> 6) / (ref_div << 4);
	ddr_pll /= (1 << out_div);

	clk_ctrl = ATH_READ_REG(QCA953X_PLL_CLK_CTRL_REG);

	postdiv = (clk_ctrl >> QCA953X_PLL_CLK_CTRL_CPU_POST_DIV_SHIFT) &
		  QCA953X_PLL_CLK_CTRL_CPU_POST_DIV_MASK;

	if (clk_ctrl & QCA953X_PLL_CLK_CTRL_CPU_PLL_BYPASS)
		cpu_rate = ref_rate;
	else if (clk_ctrl & QCA953X_PLL_CLK_CTRL_CPUCLK_FROM_CPUPLL)
		cpu_rate = cpu_pll / (postdiv + 1);
	else
		cpu_rate = ddr_pll / (postdiv + 1);

	postdiv = (clk_ctrl >> QCA953X_PLL_CLK_CTRL_DDR_POST_DIV_SHIFT) &
		  QCA953X_PLL_CLK_CTRL_DDR_POST_DIV_MASK;

	if (clk_ctrl & QCA953X_PLL_CLK_CTRL_DDR_PLL_BYPASS)
		ddr_rate = ref_rate;
	else if (clk_ctrl & QCA953X_PLL_CLK_CTRL_DDRCLK_FROM_DDRPLL)
		ddr_rate = ddr_pll / (postdiv + 1);
	else
		ddr_rate = cpu_pll / (postdiv + 1);

	postdiv = (clk_ctrl >> QCA953X_PLL_CLK_CTRL_AHB_POST_DIV_SHIFT) &
		  QCA953X_PLL_CLK_CTRL_AHB_POST_DIV_MASK;

	if (clk_ctrl & QCA953X_PLL_CLK_CTRL_AHB_PLL_BYPASS)
		ahb_rate = ref_rate;
	else if (clk_ctrl & QCA953X_PLL_CLK_CTRL_AHBCLK_FROM_DDRPLL)
		ahb_rate = ddr_pll / (postdiv + 1);
	else
		ahb_rate = cpu_pll / (postdiv + 1);

	u_ar71xx_ddr_freq = ddr_rate;
	u_ar71xx_cpu_freq = cpu_rate;
	u_ar71xx_ahb_freq = ahb_rate;

	u_ar71xx_wdt_freq = ref_rate;
	u_ar71xx_uart_freq = ref_rate;
	u_ar71xx_mdio_freq = ref_rate;
	u_ar71xx_refclk = ref_rate;
}
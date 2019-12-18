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
typedef  int /*<<< orphan*/  u16 ;
struct clk_syscon {int clk_val; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
#define  U300_SYSCON_CCR_CLKING_PERFORMANCE_HIGH 142 
#define  U300_SYSCON_CCR_CLKING_PERFORMANCE_INTERMEDIATE 141 
#define  U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW 140 
#define  U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER 139 
#define  U300_SYSCON_SBCER_CPU_CLK_EN 138 
#define  U300_SYSCON_SBCER_DMAC_CLK_EN 137 
#define  U300_SYSCON_SBCER_EMIF_CLK_EN 136 
#define  U300_SYSCON_SBCER_FAST_BRIDGE_CLK_EN 135 
#define  U300_SYSCON_SBCER_I2C0_CLK_EN 134 
#define  U300_SYSCON_SBCER_I2C1_CLK_EN 133 
#define  U300_SYSCON_SBCER_MMC_CLK_EN 132 
#define  U300_SYSCON_SBCER_NANDIF_CLK_EN 131 
#define  U300_SYSCON_SBCER_SEMI_CLK_EN 130 
#define  U300_SYSCON_SBCER_SPI_CLK_EN 129 
#define  U300_SYSCON_SBCER_XGAM_CLK_EN 128 
 int /*<<< orphan*/  syscon_get_perf () ; 
 struct clk_syscon* to_syscon (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
syscon_clk_recalc_rate(struct clk_hw *hw,
		       unsigned long parent_rate)
{
	struct clk_syscon *sclk = to_syscon(hw);
	u16 perf = syscon_get_perf();

	switch (sclk->clk_val) {
	case U300_SYSCON_SBCER_FAST_BRIDGE_CLK_EN:
	case U300_SYSCON_SBCER_I2C0_CLK_EN:
	case U300_SYSCON_SBCER_I2C1_CLK_EN:
	case U300_SYSCON_SBCER_MMC_CLK_EN:
	case U300_SYSCON_SBCER_SPI_CLK_EN:
		/* The FAST clocks have one progression */
		switch (perf) {
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER:
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW:
			return 13000000;
		default:
			return parent_rate; /* 26 MHz */
		}
	case U300_SYSCON_SBCER_DMAC_CLK_EN:
	case U300_SYSCON_SBCER_NANDIF_CLK_EN:
	case U300_SYSCON_SBCER_XGAM_CLK_EN:
		/* AMBA interconnect peripherals */
		switch (perf) {
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER:
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW:
			return 6500000;
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_INTERMEDIATE:
			return 26000000;
		default:
			return parent_rate; /* 52 MHz */
		}
	case U300_SYSCON_SBCER_SEMI_CLK_EN:
	case U300_SYSCON_SBCER_EMIF_CLK_EN:
		/* EMIF speeds */
		switch (perf) {
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER:
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW:
			return 13000000;
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_INTERMEDIATE:
			return 52000000;
		default:
			return 104000000;
		}
	case U300_SYSCON_SBCER_CPU_CLK_EN:
		/* And the fast CPU clock */
		switch (perf) {
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW_POWER:
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_LOW:
			return 13000000;
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_INTERMEDIATE:
			return 52000000;
		case U300_SYSCON_CCR_CLKING_PERFORMANCE_HIGH:
			return 104000000;
		default:
			return parent_rate; /* 208 MHz */
		}
	default:
		/*
		 * The SLOW clocks and default just inherit the rate of
		 * their parent (typically PLL13 13 MHz).
		 */
		return parent_rate;
	}
}
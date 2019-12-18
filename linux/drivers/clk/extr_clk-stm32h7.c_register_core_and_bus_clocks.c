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

/* Variables and functions */
 int /*<<< orphan*/  CLK_IGNORE_UNUSED ; 
 size_t CPU_SYSTICK ; 
 size_t HCLK ; 
 size_t PCLK1 ; 
 size_t PCLK2 ; 
 size_t PCLK3 ; 
 size_t PCLK4 ; 
 scalar_t__ RCC_D1CFGR ; 
 scalar_t__ RCC_D2CFGR ; 
 scalar_t__ RCC_D3CFGR ; 
 size_t SYS_D1CPRE ; 
 scalar_t__ base ; 
 int /*<<< orphan*/  clk_hw_register_divider_table (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_hw_register_fixed_factor (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  clk_register_stm32_timer_ker (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d1cpre_div_table ; 
 int /*<<< orphan*/ * hws ; 
 int /*<<< orphan*/  ppre_div_table ; 
 int /*<<< orphan*/  stm32rcc_lock ; 

__attribute__((used)) static void register_core_and_bus_clocks(void)
{
	/* CORE AND BUS */
	hws[SYS_D1CPRE] = clk_hw_register_divider_table(NULL, "d1cpre",
			"sys_ck", CLK_IGNORE_UNUSED, base + RCC_D1CFGR, 8, 4, 0,
			d1cpre_div_table, &stm32rcc_lock);

	hws[HCLK] = clk_hw_register_divider_table(NULL, "hclk", "d1cpre",
			CLK_IGNORE_UNUSED, base + RCC_D1CFGR, 0, 4, 0,
			d1cpre_div_table, &stm32rcc_lock);

	/* D1 DOMAIN */
	/* * CPU Systick */
	hws[CPU_SYSTICK] = clk_hw_register_fixed_factor(NULL, "systick",
			"d1cpre", 0, 1, 8);

	/* * APB3 peripheral */
	hws[PCLK3] = clk_hw_register_divider_table(NULL, "pclk3", "hclk", 0,
			base + RCC_D1CFGR, 4, 3, 0,
			ppre_div_table, &stm32rcc_lock);

	/* D2 DOMAIN */
	/* * APB1 peripheral */
	hws[PCLK1] = clk_hw_register_divider_table(NULL, "pclk1", "hclk", 0,
			base + RCC_D2CFGR, 4, 3, 0,
			ppre_div_table, &stm32rcc_lock);

	/* Timers prescaler clocks */
	clk_register_stm32_timer_ker(NULL, "tim1_ker", "pclk1", 0,
			4, &stm32rcc_lock);

	/* * APB2 peripheral */
	hws[PCLK2] = clk_hw_register_divider_table(NULL, "pclk2", "hclk", 0,
			base + RCC_D2CFGR, 8, 3, 0, ppre_div_table,
			&stm32rcc_lock);

	clk_register_stm32_timer_ker(NULL, "tim2_ker", "pclk2", 0, 8,
			&stm32rcc_lock);

	/* D3 DOMAIN */
	/* * APB4 peripheral */
	hws[PCLK4] = clk_hw_register_divider_table(NULL, "pclk4", "hclk", 0,
			base + RCC_D3CFGR, 4, 3, 0,
			ppre_div_table, &stm32rcc_lock);
}
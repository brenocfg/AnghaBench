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
 int ARRAY_SIZE (int*) ; 
 scalar_t__ RK3288_CLKGATE_CON (int) ; 
 scalar_t__ RK3288_MODE_CON ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 scalar_t__ rk3288_cru_base ; 
 int* rk3288_saved_cru_reg_ids ; 
 int /*<<< orphan*/ * rk3288_saved_cru_regs ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static int rk3288_clk_suspend(void)
{
	int i, reg_id;

	for (i = 0; i < ARRAY_SIZE(rk3288_saved_cru_reg_ids); i++) {
		reg_id = rk3288_saved_cru_reg_ids[i];

		rk3288_saved_cru_regs[i] =
				readl_relaxed(rk3288_cru_base + reg_id);
	}

	/*
	 * Going into deep sleep (specifically setting PMU_CLR_DMA in
	 * RK3288_PMU_PWRMODE_CON1) appears to fail unless
	 * "aclk_dmac1" is on.
	 */
	writel_relaxed(1 << (12 + 16),
		       rk3288_cru_base + RK3288_CLKGATE_CON(10));

	/*
	 * Switch PLLs other than DPLL (for SDRAM) to slow mode to
	 * avoid crashes on resume. The Mask ROM on the system will
	 * put APLL, CPLL, and GPLL into slow mode at resume time
	 * anyway (which is why we restore them), but we might not
	 * even make it to the Mask ROM if this isn't done at suspend
	 * time.
	 *
	 * NOTE: only APLL truly matters here, but we'll do them all.
	 */

	writel_relaxed(0xf3030000, rk3288_cru_base + RK3288_MODE_CON);

	return 0;
}
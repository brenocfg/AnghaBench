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
struct samsung_clk_provider {int /*<<< orphan*/  reg_base; } ;
struct exynos5_subcmu_info {int /*<<< orphan*/  nr_suspend_regs; int /*<<< orphan*/  suspend_regs; int /*<<< orphan*/  nr_gate_clks; int /*<<< orphan*/  gate_clks; } ;

/* Variables and functions */
 struct exynos5_subcmu_info const** cmu ; 
 struct samsung_clk_provider* ctx ; 
 int /*<<< orphan*/  exynos5_subcmu_clk_save (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos5_subcmu_defer_gate (struct samsung_clk_provider*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int nr_cmus ; 

void exynos5_subcmus_init(struct samsung_clk_provider *_ctx, int _nr_cmus,
			  const struct exynos5_subcmu_info **_cmu)
{
	ctx = _ctx;
	cmu = _cmu;
	nr_cmus = _nr_cmus;

	for (; _nr_cmus--; _cmu++) {
		exynos5_subcmu_defer_gate(ctx, (*_cmu)->gate_clks,
					  (*_cmu)->nr_gate_clks);
		exynos5_subcmu_clk_save(ctx->reg_base, (*_cmu)->suspend_regs,
					(*_cmu)->nr_suspend_regs);
	}
}
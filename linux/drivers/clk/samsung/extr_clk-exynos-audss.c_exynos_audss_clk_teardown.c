#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num; int /*<<< orphan*/ * hws; } ;

/* Variables and functions */
 int EXYNOS_DOUT_SRP ; 
 int EXYNOS_MOUT_AUDSS ; 
 int EXYNOS_SRP_CLK ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 TYPE_1__* clk_data ; 
 int /*<<< orphan*/  clk_hw_unregister_divider (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_unregister_gate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_hw_unregister_mux (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exynos_audss_clk_teardown(void)
{
	int i;

	for (i = EXYNOS_MOUT_AUDSS; i < EXYNOS_DOUT_SRP; i++) {
		if (!IS_ERR(clk_data->hws[i]))
			clk_hw_unregister_mux(clk_data->hws[i]);
	}

	for (; i < EXYNOS_SRP_CLK; i++) {
		if (!IS_ERR(clk_data->hws[i]))
			clk_hw_unregister_divider(clk_data->hws[i]);
	}

	for (; i < clk_data->num; i++) {
		if (!IS_ERR(clk_data->hws[i]))
			clk_hw_unregister_gate(clk_data->hws[i]);
	}
}
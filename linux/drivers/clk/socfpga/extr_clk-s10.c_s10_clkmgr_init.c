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
struct stratix10_clock_data {int dummy; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct stratix10_clock_data*) ; 
 int PTR_ERR (struct stratix10_clock_data*) ; 
 int /*<<< orphan*/  STRATIX10_NUM_CLKS ; 
 struct stratix10_clock_data* __socfpga_s10_clk_init (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s10_clk_register_c_perip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stratix10_clock_data*) ; 
 int /*<<< orphan*/  s10_clk_register_cnt_perip (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stratix10_clock_data*) ; 
 int /*<<< orphan*/  s10_clk_register_gate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stratix10_clock_data*) ; 
 int /*<<< orphan*/  s10_clk_register_pll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stratix10_clock_data*) ; 
 int /*<<< orphan*/  s10_gate_clks ; 
 int /*<<< orphan*/  s10_main_perip_c_clks ; 
 int /*<<< orphan*/  s10_main_perip_cnt_clks ; 
 int /*<<< orphan*/  s10_pll_clks ; 

__attribute__((used)) static int s10_clkmgr_init(struct platform_device *pdev)
{
	struct stratix10_clock_data *clk_data;

	clk_data = __socfpga_s10_clk_init(pdev, STRATIX10_NUM_CLKS);
	if (IS_ERR(clk_data))
		return PTR_ERR(clk_data);

	s10_clk_register_pll(s10_pll_clks, ARRAY_SIZE(s10_pll_clks), clk_data);

	s10_clk_register_c_perip(s10_main_perip_c_clks,
				 ARRAY_SIZE(s10_main_perip_c_clks), clk_data);

	s10_clk_register_cnt_perip(s10_main_perip_cnt_clks,
				   ARRAY_SIZE(s10_main_perip_cnt_clks),
				   clk_data);

	s10_clk_register_gate(s10_gate_clks, ARRAY_SIZE(s10_gate_clks),
			      clk_data);
	return 0;
}
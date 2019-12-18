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
struct clk_scu {int /*<<< orphan*/  clk_type; int /*<<< orphan*/  rsrc_id; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ccm_ipc_handle ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int sc_pm_clock_enable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct clk_scu* to_clk_scu (struct clk_hw*) ; 

__attribute__((used)) static void clk_scu_unprepare(struct clk_hw *hw)
{
	struct clk_scu *clk = to_clk_scu(hw);
	int ret;

	ret = sc_pm_clock_enable(ccm_ipc_handle, clk->rsrc_id,
				 clk->clk_type, false, false);
	if (ret)
		pr_warn("%s: clk unprepare failed %d\n", clk_hw_get_name(hw),
			ret);
}
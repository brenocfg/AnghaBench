#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
struct sd_clock {size_t cur_div_idx; TYPE_2__* div_table; TYPE_1__ csn; } ;
struct clk_hw {int dummy; } ;
struct TYPE_4__ {int val; } ;

/* Variables and functions */
 int CPG_SD_STP_MASK ; 
 int /*<<< orphan*/  cpg_reg_modify (int /*<<< orphan*/ ,int,int) ; 
 struct sd_clock* to_sd_clock (struct clk_hw*) ; 

__attribute__((used)) static int cpg_sd_clock_enable(struct clk_hw *hw)
{
	struct sd_clock *clock = to_sd_clock(hw);

	cpg_reg_modify(clock->csn.reg, CPG_SD_STP_MASK,
		       clock->div_table[clock->cur_div_idx].val &
		       CPG_SD_STP_MASK);

	return 0;
}
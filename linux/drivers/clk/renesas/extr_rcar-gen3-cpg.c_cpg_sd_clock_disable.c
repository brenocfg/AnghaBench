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
struct TYPE_2__ {int /*<<< orphan*/  reg; } ;
struct sd_clock {TYPE_1__ csn; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPG_SD_STP_MASK ; 
 int /*<<< orphan*/  cpg_reg_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sd_clock* to_sd_clock (struct clk_hw*) ; 

__attribute__((used)) static void cpg_sd_clock_disable(struct clk_hw *hw)
{
	struct sd_clock *clock = to_sd_clock(hw);

	cpg_reg_modify(clock->csn.reg, 0, CPG_SD_STP_MASK);
}
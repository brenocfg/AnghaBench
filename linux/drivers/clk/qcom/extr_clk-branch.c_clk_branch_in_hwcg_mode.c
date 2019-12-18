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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_branch {int /*<<< orphan*/  hwcg_bit; int /*<<< orphan*/  hwcg_reg; TYPE_1__ clkr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool clk_branch_in_hwcg_mode(const struct clk_branch *br)
{
	u32 val;

	if (!br->hwcg_reg)
		return false;

	regmap_read(br->clkr.regmap, br->hwcg_reg, &val);

	return !!(val & BIT(br->hwcg_bit));
}
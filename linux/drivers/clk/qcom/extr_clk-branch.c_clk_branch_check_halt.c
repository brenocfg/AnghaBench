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
struct clk_branch {scalar_t__ halt_check; int /*<<< orphan*/  halt_bit; int /*<<< orphan*/  halt_reg; TYPE_1__ clkr; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ BRANCH_HALT_ENABLE ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool clk_branch_check_halt(const struct clk_branch *br, bool enabling)
{
	bool invert = (br->halt_check == BRANCH_HALT_ENABLE);
	u32 val;

	regmap_read(br->clkr.regmap, br->halt_reg, &val);

	val &= BIT(br->halt_bit);
	if (invert)
		val = !val;

	return !!val == !enabling;
}
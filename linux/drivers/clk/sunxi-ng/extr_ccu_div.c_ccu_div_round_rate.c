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
struct clk_hw {int dummy; } ;
struct ccu_mux_internal {int dummy; } ;
struct TYPE_4__ {int features; int /*<<< orphan*/  hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  width; int /*<<< orphan*/  table; } ;
struct ccu_div {unsigned long fixed_post_div; TYPE_2__ common; TYPE_1__ div; } ;

/* Variables and functions */
 int CCU_FEATURE_FIXED_POSTDIV ; 
 unsigned long divider_round_rate_parent (int /*<<< orphan*/ *,struct clk_hw*,unsigned long,unsigned long*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long ccu_div_round_rate(struct ccu_mux_internal *mux,
					struct clk_hw *parent,
					unsigned long *parent_rate,
					unsigned long rate,
					void *data)
{
	struct ccu_div *cd = data;

	if (cd->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate *= cd->fixed_post_div;

	rate = divider_round_rate_parent(&cd->common.hw, parent,
					 rate, parent_rate,
					 cd->div.table, cd->div.width,
					 cd->div.flags);

	if (cd->common.features & CCU_FEATURE_FIXED_POSTDIV)
		rate /= cd->fixed_post_div;

	return rate;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_5__ {unsigned long shift; int width; unsigned long offset; } ;
struct TYPE_6__ {scalar_t__ reg; scalar_t__ base; } ;
struct ccu_mult {TYPE_1__ mult; int /*<<< orphan*/  mux; TYPE_2__ common; int /*<<< orphan*/  frac; } ;

/* Variables and functions */
 scalar_t__ ccu_frac_helper_is_enabled (TYPE_2__*,int /*<<< orphan*/ *) ; 
 unsigned long ccu_frac_helper_read_rate (TYPE_2__*,int /*<<< orphan*/ *) ; 
 unsigned long ccu_mux_helper_apply_prediv (TYPE_2__*,int /*<<< orphan*/ *,int,unsigned long) ; 
 struct ccu_mult* hw_to_ccu_mult (struct clk_hw*) ; 
 unsigned long readl (scalar_t__) ; 

__attribute__((used)) static unsigned long ccu_mult_recalc_rate(struct clk_hw *hw,
					unsigned long parent_rate)
{
	struct ccu_mult *cm = hw_to_ccu_mult(hw);
	unsigned long val;
	u32 reg;

	if (ccu_frac_helper_is_enabled(&cm->common, &cm->frac))
		return ccu_frac_helper_read_rate(&cm->common, &cm->frac);

	reg = readl(cm->common.base + cm->common.reg);
	val = reg >> cm->mult.shift;
	val &= (1 << cm->mult.width) - 1;

	parent_rate = ccu_mux_helper_apply_prediv(&cm->common, &cm->mux, -1,
						  parent_rate);

	return parent_rate * (val + cm->mult.offset);
}
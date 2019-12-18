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
typedef  scalar_t__ u32 ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {unsigned long max; } ;
struct clk_generated {scalar_t__ gckdiv; TYPE_1__ range; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 int EINVAL ; 
 scalar_t__ GENERATED_MAX_DIV ; 
 struct clk_generated* to_clk_generated (struct clk_hw*) ; 

__attribute__((used)) static int clk_generated_set_rate(struct clk_hw *hw,
				  unsigned long rate,
				  unsigned long parent_rate)
{
	struct clk_generated *gck = to_clk_generated(hw);
	u32 div;

	if (!rate)
		return -EINVAL;

	if (gck->range.max && rate > gck->range.max)
		return -EINVAL;

	div = DIV_ROUND_CLOSEST(parent_rate, rate);
	if (div > GENERATED_MAX_DIV + 1 || !div)
		return -EINVAL;

	gck->gckdiv = div - 1;
	return 0;
}
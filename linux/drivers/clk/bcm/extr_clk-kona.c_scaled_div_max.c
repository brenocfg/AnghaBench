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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_3__ {int width; } ;
struct TYPE_4__ {TYPE_1__ s; int /*<<< orphan*/  fixed; } ;
struct bcm_clk_div {TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ divider_is_fixed (struct bcm_clk_div*) ; 
 int /*<<< orphan*/  scaled_div_value (struct bcm_clk_div*,int) ; 

u64 scaled_div_max(struct bcm_clk_div *div)
{
	u32 reg_div;

	if (divider_is_fixed(div))
		return (u64)div->u.fixed;

	reg_div = ((u32)1 << div->u.s.width) - 1;

	return scaled_div_value(div, reg_div);
}
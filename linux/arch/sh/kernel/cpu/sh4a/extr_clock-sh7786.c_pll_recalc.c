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
struct clk {TYPE_1__* parent; } ;
struct TYPE_4__ {int (* mv_mode_pins ) () ;} ;
struct TYPE_3__ {int rate; } ;

/* Variables and functions */
 TYPE_2__ sh_mv ; 
 int stub1 () ; 

__attribute__((used)) static unsigned long pll_recalc(struct clk *clk)
{
	int multiplier;

	/*
	 * Clock modes 0, 1, and 2 use an x64 multiplier against PLL1,
	 * while modes 3, 4, and 5 use an x32.
	 */
	multiplier = (sh_mv.mv_mode_pins() & 0xf) < 3 ? 64 : 32;

	return clk->parent->rate * multiplier;
}
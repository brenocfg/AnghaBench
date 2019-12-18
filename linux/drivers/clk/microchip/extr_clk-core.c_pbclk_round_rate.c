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
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PB_DIV_MAX ; 
 int /*<<< orphan*/  PB_DIV_MIN ; 
 long calc_best_divided_rate (unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long pbclk_round_rate(struct clk_hw *hw, unsigned long rate,
			     unsigned long *parent_rate)
{
	return calc_best_divided_rate(rate, *parent_rate,
				      PB_DIV_MAX, PB_DIV_MIN);
}
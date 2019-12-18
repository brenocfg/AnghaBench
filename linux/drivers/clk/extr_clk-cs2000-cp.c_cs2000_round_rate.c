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
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cs2000_rate_to_ratio (unsigned long,unsigned long) ; 
 long cs2000_ratio_to_rate (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static long cs2000_round_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long *parent_rate)
{
	u32 ratio;

	ratio = cs2000_rate_to_ratio(*parent_rate, rate);

	return cs2000_ratio_to_rate(ratio, *parent_rate);
}
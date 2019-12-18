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
typedef  unsigned long u64 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long DTO_RESL_DOUBLE ; 
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 

__attribute__((used)) static long dto_clk_round_rate(struct clk_hw *hw, unsigned long rate,
	unsigned long *parent_rate)
{
	u64 dividend = rate * DTO_RESL_DOUBLE;

	do_div(dividend, *parent_rate);
	dividend *= *parent_rate;
	do_div(dividend, DTO_RESL_DOUBLE);

	return dividend;
}
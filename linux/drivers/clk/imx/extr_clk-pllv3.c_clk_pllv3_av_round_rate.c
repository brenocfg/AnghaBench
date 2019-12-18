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
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 

__attribute__((used)) static long clk_pllv3_av_round_rate(struct clk_hw *hw, unsigned long rate,
				    unsigned long *prate)
{
	unsigned long parent_rate = *prate;
	unsigned long min_rate = parent_rate * 27;
	unsigned long max_rate = parent_rate * 54;
	u32 div;
	u32 mfn, mfd = 1000000;
	u32 max_mfd = 0x3FFFFFFF;
	u64 temp64;

	if (rate > max_rate)
		rate = max_rate;
	else if (rate < min_rate)
		rate = min_rate;

	if (parent_rate <= max_mfd)
		mfd = parent_rate;

	div = rate / parent_rate;
	temp64 = (u64) (rate - div * parent_rate);
	temp64 *= mfd;
	do_div(temp64, parent_rate);
	mfn = temp64;

	temp64 = (u64)parent_rate;
	temp64 *= mfn;
	do_div(temp64, mfd);

	return parent_rate * div + (unsigned long)temp64;
}
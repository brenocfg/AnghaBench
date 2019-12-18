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
typedef  long u64 ;
typedef  long u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long ARRAY_SIZE (unsigned long*) ; 
 long DEFAULT_MFD ; 
 unsigned long MAX_MFD ; 
 int /*<<< orphan*/  clk_hw_get_name (struct clk_hw*) ; 
 int /*<<< orphan*/  do_div (long,long) ; 
 unsigned long* pllv4_mult_table ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,unsigned long,unsigned long) ; 

__attribute__((used)) static long clk_pllv4_round_rate(struct clk_hw *hw, unsigned long rate,
				 unsigned long *prate)
{
	unsigned long parent_rate = *prate;
	unsigned long round_rate, i;
	u32 mfn, mfd = DEFAULT_MFD;
	bool found = false;
	u64 temp64;

	for (i = 0; i < ARRAY_SIZE(pllv4_mult_table); i++) {
		round_rate = parent_rate * pllv4_mult_table[i];
		if (rate >= round_rate) {
			found = true;
			break;
		}
	}

	if (!found) {
		pr_warn("%s: unable to round rate %lu, parent rate %lu\n",
			clk_hw_get_name(hw), rate, parent_rate);
		return 0;
	}

	if (parent_rate <= MAX_MFD)
		mfd = parent_rate;

	temp64 = (u64)(rate - round_rate);
	temp64 *= mfd;
	do_div(temp64, parent_rate);
	mfn = temp64;

	/*
	 * NOTE: The value of numerator must always be configured to be
	 * less than the value of the denominator. If we can't get a proper
	 * pair of mfn/mfd, we simply return the round_rate without using
	 * the frac part.
	 */
	if (mfn >= mfd)
		return round_rate;

	temp64 = (u64)parent_rate;
	temp64 *= mfn;
	do_div(temp64, mfd);

	return round_rate + (u32)temp64;
}
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
struct clk_pllv3_vf610_mf {int mfi; int mfd; int mfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  do_div (unsigned long,unsigned long) ; 

__attribute__((used)) static struct clk_pllv3_vf610_mf clk_pllv3_vf610_rate_to_mf(
		unsigned long parent_rate, unsigned long rate)
{
	struct clk_pllv3_vf610_mf mf;
	u64 temp64;

	mf.mfi = (rate >= 22 * parent_rate) ? 22 : 20;
	mf.mfd = 0x3fffffff;	/* use max supported value for best accuracy */

	if (rate <= parent_rate * mf.mfi)
		mf.mfn = 0;
	else if (rate >= parent_rate * (mf.mfi + 1))
		mf.mfn = mf.mfd - 1;
	else {
		/* rate = parent_rate * (mfi + mfn/mfd) */
		temp64 = rate - parent_rate * mf.mfi;
		temp64 *= mf.mfd;
		do_div(temp64, parent_rate);
		mf.mfn = temp64;
	}

	return mf;
}
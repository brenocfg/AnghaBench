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
typedef  unsigned long u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long DIV_ROUND_CLOSEST (unsigned long,unsigned long) ; 
 unsigned long PLL_FBDIV_MAX ; 
 unsigned long PLL_FBDIV_MIN ; 

__attribute__((used)) static long zynq_pll_round_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long *prate)
{
	u32 fbdiv;

	fbdiv = DIV_ROUND_CLOSEST(rate, *prate);
	if (fbdiv < PLL_FBDIV_MIN)
		fbdiv = PLL_FBDIV_MIN;
	else if (fbdiv > PLL_FBDIV_MAX)
		fbdiv = PLL_FBDIV_MAX;

	return *prate * fbdiv;
}
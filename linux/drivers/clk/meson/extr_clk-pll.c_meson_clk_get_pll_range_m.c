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
typedef  unsigned int u64 ;
struct meson_clk_pll_data {int dummy; } ;

/* Variables and functions */
 unsigned int DIV_ROUND_CLOSEST_ULL (unsigned int,unsigned long) ; 
 scalar_t__ __pll_round_closest_mult (struct meson_clk_pll_data*) ; 
 unsigned int div_u64 (unsigned int,unsigned long) ; 

__attribute__((used)) static unsigned int meson_clk_get_pll_range_m(unsigned long rate,
					      unsigned long parent_rate,
					      unsigned int n,
					      struct meson_clk_pll_data *pll)
{
	u64 val = (u64)rate * n;

	if (__pll_round_closest_mult(pll))
		return DIV_ROUND_CLOSEST_ULL(val, parent_rate);

	return div_u64(val,  parent_rate);
}
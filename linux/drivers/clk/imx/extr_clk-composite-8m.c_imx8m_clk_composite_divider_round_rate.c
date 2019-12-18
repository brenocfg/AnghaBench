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
 long DIV_ROUND_UP (unsigned long,int) ; 
 int /*<<< orphan*/  imx8m_clk_composite_compute_dividers (unsigned long,unsigned long,int*,int*) ; 

__attribute__((used)) static long imx8m_clk_composite_divider_round_rate(struct clk_hw *hw,
						unsigned long rate,
						unsigned long *prate)
{
	int prediv_value;
	int div_value;

	imx8m_clk_composite_compute_dividers(rate, *prate,
						&prediv_value, &div_value);
	rate = DIV_ROUND_UP(*prate, prediv_value);

	return DIV_ROUND_UP(rate, div_value);

}
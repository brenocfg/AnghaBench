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
typedef  int u32 ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_pll_calc (unsigned long,unsigned long,int*,int*) ; 

__attribute__((used)) static long clk_pll_round_rate(struct clk_hw *hwclk, unsigned long rate,
			       unsigned long *parent_rate)
{
	u32 divq, divf;
	unsigned long ref_freq = *parent_rate;

	clk_pll_calc(rate, ref_freq, &divq, &divf);

	return (ref_freq * (divf + 1)) / (1 << divq);
}
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
 int /*<<< orphan*/  CCSR ; 
 unsigned long CCSR_L_MASK ; 
 unsigned long CCSR_N2_MASK ; 
 unsigned long CCSR_N2_SHIFT ; 
 unsigned long readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long clk_pxa27x_cpll_get_rate(struct clk_hw *hw,
	unsigned long parent_rate)
{
	unsigned long clkcfg;
	unsigned int t, ht;
	unsigned int l, L, n2, N;
	unsigned long ccsr = readl(CCSR);

	asm("mrc\tp14, 0, %0, c6, c0, 0" : "=r" (clkcfg));
	t  = clkcfg & (1 << 0);
	ht = clkcfg & (1 << 2);

	l  = ccsr & CCSR_L_MASK;
	n2 = (ccsr & CCSR_N2_MASK) >> CCSR_N2_SHIFT;
	L  = l * parent_rate;
	N  = (L * n2) / 2;

	return N;
}
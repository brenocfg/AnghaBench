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
 unsigned long ACCR_XL_MASK ; 
 unsigned long ACCR_XN_MASK ; 
 unsigned long ACSR ; 
 int /*<<< orphan*/  pr_info (char*,unsigned long,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned long clk_pxa3xx_cpll_get_rate(struct clk_hw *hw,
	unsigned long parent_rate)
{
	unsigned long acsr = ACSR;
	unsigned int xn = (acsr & ACCR_XN_MASK) >> 8;
	unsigned int xl = acsr & ACCR_XL_MASK;
	unsigned int t, xclkcfg;

	/* Read XCLKCFG register turbo bit */
	__asm__ __volatile__("mrc\tp14, 0, %0, c6, c0, 0" : "=r"(xclkcfg));
	t = xclkcfg & 0x1;

	pr_info("RJK: parent_rate=%lu, xl=%u, xn=%u\n", parent_rate, xl, xn);
	return t ? parent_rate * xl * xn : parent_rate * xl;
}
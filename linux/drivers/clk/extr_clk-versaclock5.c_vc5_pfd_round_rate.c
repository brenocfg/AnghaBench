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
 unsigned long DIV_ROUND_UP (unsigned long,unsigned long) ; 
 long EINVAL ; 

__attribute__((used)) static long vc5_pfd_round_rate(struct clk_hw *hw, unsigned long rate,
			       unsigned long *parent_rate)
{
	unsigned long idiv;

	/* PLL cannot operate with input clock above 50 MHz. */
	if (rate > 50000000)
		return -EINVAL;

	/* CLKIN within range of PLL input, feed directly to PLL. */
	if (*parent_rate <= 50000000)
		return *parent_rate;

	idiv = DIV_ROUND_UP(*parent_rate, rate);
	if (idiv > 127)
		return -EINVAL;

	return *parent_rate / idiv;
}
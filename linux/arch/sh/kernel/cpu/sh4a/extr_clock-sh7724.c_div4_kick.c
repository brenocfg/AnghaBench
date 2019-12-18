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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FRQCRA ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void div4_kick(struct clk *clk)
{
	unsigned long value;

	/* set KICK bit in FRQCRA to update hardware setting */
	value = __raw_readl(FRQCRA);
	value |= (1 << 31);
	__raw_writel(value, FRQCRA);
}
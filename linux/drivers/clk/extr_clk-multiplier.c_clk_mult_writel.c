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
typedef  int /*<<< orphan*/  u32 ;
struct clk_multiplier {int flags; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int CLK_MULTIPLIER_BIG_ENDIAN ; 
 int /*<<< orphan*/  iowrite32be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void clk_mult_writel(struct clk_multiplier *mult, u32 val)
{
	if (mult->flags & CLK_MULTIPLIER_BIG_ENDIAN)
		iowrite32be(val, mult->reg);
	else
		writel(val, mult->reg);
}
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
 int CLK_SET_RATE_PARENT ; 
 struct clk* clk_register_fixed_factor (int /*<<< orphan*/ *,char const*,char const*,int,int,int) ; 

__attribute__((used)) static inline struct clk *mpc512x_clk_factor(
	const char *name, const char *parent_name,
	int mul, int div)
{
	int clkflags;

	clkflags = CLK_SET_RATE_PARENT;
	return clk_register_fixed_factor(NULL, name, parent_name, clkflags,
					 mul, div);
}
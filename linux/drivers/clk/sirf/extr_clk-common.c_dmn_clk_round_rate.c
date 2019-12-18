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
 unsigned int BIT (unsigned int) ; 
 char* clk_hw_get_name (struct clk_hw*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static long dmn_clk_round_rate(struct clk_hw *hw, unsigned long rate,
	unsigned long *parent_rate)
{
	unsigned long fin;
	unsigned ratio, wait, hold;
	const char *name = clk_hw_get_name(hw);
	unsigned bits = (strcmp(name, "mem") == 0) ? 3 : 4;

	fin = *parent_rate;
	ratio = fin / rate;

	if (ratio < 2)
		ratio = 2;
	if (ratio > BIT(bits + 1))
		ratio = BIT(bits + 1);

	wait = (ratio >> 1) - 1;
	hold = ratio - wait - 2;

	return fin / (wait + hold + 2);
}
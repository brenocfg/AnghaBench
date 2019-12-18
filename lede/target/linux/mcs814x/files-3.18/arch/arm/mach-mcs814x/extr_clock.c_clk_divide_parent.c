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
struct clk {unsigned long divider; scalar_t__ parent; } ;

/* Variables and functions */
 unsigned long clk_get_rate (scalar_t__) ; 

__attribute__((used)) static unsigned long clk_divide_parent(struct clk *clk)
{
	if (clk->parent && clk->divider)
		return clk_get_rate(clk->parent) / clk->divider;
	else
		return 0;
}
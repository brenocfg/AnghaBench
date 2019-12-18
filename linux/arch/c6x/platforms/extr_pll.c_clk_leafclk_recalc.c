#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clk {unsigned long rate; TYPE_1__* parent; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int rate; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned long clk_leafclk_recalc(struct clk *clk)
{
	if (WARN_ON(!clk->parent))
		return clk->rate;

	pr_debug("%s: (parent %s) rate = %lu KHz\n",
		 clk->name, clk->parent->name,	clk->parent->rate / 1000);

	return clk->parent->rate;
}
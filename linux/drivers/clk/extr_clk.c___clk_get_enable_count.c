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
struct clk {TYPE_1__* core; } ;
struct TYPE_2__ {unsigned int enable_count; } ;

/* Variables and functions */

unsigned int __clk_get_enable_count(struct clk *clk)
{
	return !clk ? 0 : clk->core->enable_count;
}
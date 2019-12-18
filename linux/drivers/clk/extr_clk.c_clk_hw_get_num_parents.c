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
struct clk_hw {TYPE_1__* core; } ;
struct TYPE_2__ {unsigned int num_parents; } ;

/* Variables and functions */

unsigned int clk_hw_get_num_parents(const struct clk_hw *hw)
{
	return hw->core->num_parents;
}
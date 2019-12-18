#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/  min_counter_down; } ;
typedef  TYPE_1__ ftree_sw_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t find_lowest_loaded_group_on_sw(ftree_sw_t * p_sw)
{
	return p_sw->min_counter_down;
}
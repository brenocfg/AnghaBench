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
struct linux_prom_ranges {scalar_t__ ot_parent_space; scalar_t__ ot_child_space; scalar_t__ ot_parent_base; scalar_t__ ot_child_base; unsigned int or_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  prom_printf (char*) ; 

__attribute__((used)) static void prom_adjust_ranges(struct linux_prom_ranges *ranges1, int nranges1,
			       struct linux_prom_ranges *ranges2, int nranges2)
{
	int rng1c, rng2c;

	for (rng1c = 0; rng1c < nranges1; rng1c++) {
		for (rng2c = 0; rng2c < nranges2; rng2c++)
			if (ranges1[rng1c].ot_parent_space == ranges2[rng2c].ot_child_space &&
			   ranges1[rng1c].ot_parent_base >= ranges2[rng2c].ot_child_base &&
			   ranges2[rng2c].ot_child_base + ranges2[rng2c].or_size - ranges1[rng1c].ot_parent_base > 0U)
			break;
		if (rng2c == nranges2) /* oops */
			prom_printf("adjust_ranges: Could not find matching bus type...\n");
		else if (ranges1[rng1c].ot_parent_base + ranges1[rng1c].or_size > ranges2[rng2c].ot_child_base + ranges2[rng2c].or_size)
			ranges1[rng1c].or_size = ranges2[rng2c].ot_child_base + ranges2[rng2c].or_size - ranges1[rng1c].ot_parent_base;
		ranges1[rng1c].ot_parent_space = ranges2[rng2c].ot_parent_space;
		ranges1[rng1c].ot_parent_base += ranges2[rng2c].ot_parent_base;
	}
}
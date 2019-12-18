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
struct omap_hwmod {int rst_lines_cnt; TYPE_1__* rst_lines; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ _read_hardreset (struct omap_hwmod*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool _are_all_hardreset_lines_asserted(struct omap_hwmod *oh)
{
	int i, rst_cnt = 0;

	if (oh->rst_lines_cnt == 0)
		return false;

	for (i = 0; i < oh->rst_lines_cnt; i++)
		if (_read_hardreset(oh, oh->rst_lines[i].name) > 0)
			rst_cnt++;

	if (oh->rst_lines_cnt == rst_cnt)
		return true;

	return false;
}
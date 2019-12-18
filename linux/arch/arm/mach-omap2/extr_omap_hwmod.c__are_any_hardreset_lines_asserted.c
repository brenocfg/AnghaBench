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

__attribute__((used)) static bool _are_any_hardreset_lines_asserted(struct omap_hwmod *oh)
{
	int rst_cnt = 0;
	int i;

	for (i = 0; i < oh->rst_lines_cnt && rst_cnt == 0; i++)
		if (_read_hardreset(oh, oh->rst_lines[i].name) > 0)
			rst_cnt++;

	return (rst_cnt) ? true : false;
}
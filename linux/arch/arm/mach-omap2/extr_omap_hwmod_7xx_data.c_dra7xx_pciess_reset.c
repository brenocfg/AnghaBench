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
 int /*<<< orphan*/  omap_hwmod_assert_hardreset (struct omap_hwmod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_hwmod_deassert_hardreset (struct omap_hwmod*,int /*<<< orphan*/ ) ; 

int dra7xx_pciess_reset(struct omap_hwmod *oh)
{
	int i;

	for (i = 0; i < oh->rst_lines_cnt; i++) {
		omap_hwmod_assert_hardreset(oh, oh->rst_lines[i].name);
		omap_hwmod_deassert_hardreset(oh, oh->rst_lines[i].name);
	}

	return 0;
}
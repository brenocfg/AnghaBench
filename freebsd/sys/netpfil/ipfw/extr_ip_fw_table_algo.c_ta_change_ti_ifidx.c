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
struct table_info {int dummy; } ;
struct iftable_cfg {struct table_info* ti; } ;

/* Variables and functions */

__attribute__((used)) static void
ta_change_ti_ifidx(void *ta_state, struct table_info *ti)
{
	struct iftable_cfg *icfg;

	icfg = (struct iftable_cfg *)ta_state;
	icfg->ti = ti;
}
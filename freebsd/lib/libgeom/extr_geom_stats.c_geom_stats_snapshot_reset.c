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
struct snapshot {scalar_t__ v; scalar_t__ u; } ;

/* Variables and functions */

void
geom_stats_snapshot_reset(void *arg)
{
	struct snapshot *sp;

	sp = arg;
	sp->u = sp->v = 0;
}
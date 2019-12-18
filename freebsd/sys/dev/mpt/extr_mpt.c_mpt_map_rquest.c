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
struct mpt_map_info {int error; int /*<<< orphan*/  phys; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */

void
mpt_map_rquest(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct mpt_map_info *map_info;

	map_info = (struct mpt_map_info *)arg;
	map_info->error = error;
	map_info->phys = segs->ds_addr;
}
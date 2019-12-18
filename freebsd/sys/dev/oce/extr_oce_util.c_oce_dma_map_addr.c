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
struct TYPE_3__ {scalar_t__ ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */

void
oce_dma_map_addr(void *arg, bus_dma_segment_t * segs, int nseg, int error)
{
	bus_addr_t *paddr = arg;

	if (error)
		*paddr = 0;
	else
		*paddr = segs->ds_addr;
}
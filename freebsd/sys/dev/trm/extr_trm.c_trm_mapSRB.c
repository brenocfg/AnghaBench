#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;
struct TYPE_5__ {int /*<<< orphan*/  srb_physbase; } ;
typedef  TYPE_2__* PACB ;

/* Variables and functions */

__attribute__((used)) static void
trm_mapSRB(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	PACB pACB;

	pACB = (PACB)arg;
	pACB->srb_physbase = segs->ds_addr;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct proto_callback_bundle {TYPE_3__* ioc; } ;
struct TYPE_9__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_4__ bus_dma_segment_t ;
struct TYPE_6__ {int bus_nsegs; int /*<<< orphan*/  bus_addr; } ;
struct TYPE_7__ {TYPE_1__ md; } ;
struct TYPE_8__ {TYPE_2__ u; } ;

/* Variables and functions */

__attribute__((used)) static void
proto_busdma_mem_alloc_callback(void *arg, bus_dma_segment_t *segs, int	nseg,
    int error)
{
	struct proto_callback_bundle *pcb = arg;

	pcb->ioc->u.md.bus_nsegs = nseg;
	pcb->ioc->u.md.bus_addr = segs[0].ds_addr;
}
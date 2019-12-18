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
struct sec_dma_mem {int /*<<< orphan*/  dma_paddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 

__attribute__((used)) static void
sec_alloc_dma_mem_cb(void *arg, bus_dma_segment_t *segs, int nseg, int error)
{
	struct sec_dma_mem *dma_mem = arg;

	if (error)
		return;

	KASSERT(nseg == 1, ("Wrong number of segments, should be 1"));
	dma_mem->dma_paddr = segs->ds_addr;
}
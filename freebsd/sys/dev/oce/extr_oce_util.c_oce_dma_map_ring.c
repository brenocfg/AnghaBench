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
struct _oce_dmamap_paddr_table {int max_entries; int num_entries; TYPE_1__* paddrs; } ;
struct TYPE_5__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_4__ {int /*<<< orphan*/  hi; int /*<<< orphan*/  lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADDR_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ADDR_LO (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
oce_dma_map_ring(void *arg, bus_dma_segment_t * segs, int nseg, int error)
{
	int i;
	struct _oce_dmamap_paddr_table *dpt =
	    (struct _oce_dmamap_paddr_table *)arg;

	if (error == 0) {
		if (nseg <= dpt->max_entries) {
			for (i = 0; i < nseg; i++) {
				dpt->paddrs[i].lo = ADDR_LO(segs[i].ds_addr);
				dpt->paddrs[i].hi = ADDR_HI(segs[i].ds_addr);
			}
			dpt->num_entries = nseg;
		}
	}
}
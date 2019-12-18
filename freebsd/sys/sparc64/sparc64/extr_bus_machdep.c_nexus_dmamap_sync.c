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
typedef  int bus_dmasync_op_t ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;
typedef  int /*<<< orphan*/  bus_dma_tag_t ;

/* Variables and functions */
 int BUS_DMASYNC_POSTWRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  Sync ; 
 int /*<<< orphan*/  membar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nexus_dmamap_sync(bus_dma_tag_t dmat, bus_dmamap_t map, bus_dmasync_op_t op)
{

	/*
	 * We sync out our caches, but the bus must do the same.
	 *
	 * Actually a #Sync is expensive.  We should optimize.
	 */
	if ((op & BUS_DMASYNC_PREREAD) || (op & BUS_DMASYNC_PREWRITE)) {
		/*
		 * Don't really need to do anything, but flush any pending
		 * writes anyway.
		 */
		membar(Sync);
	}
	if (op & BUS_DMASYNC_POSTWRITE) {
		/* Nothing to do.  Handled by the bus controller. */
	}
}
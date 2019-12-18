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
struct cesa_dma_mem {int /*<<< orphan*/  cdm_map; int /*<<< orphan*/  cdm_tag; int /*<<< orphan*/ * cdm_vaddr; } ;
typedef  int /*<<< orphan*/  bus_dmasync_op_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cesa_sync_dma_mem(struct cesa_dma_mem *cdm, bus_dmasync_op_t op)
{

	/* Sync only if dma memory is valid */
        if (cdm->cdm_vaddr != NULL)
		bus_dmamap_sync(cdm->cdm_tag, cdm->cdm_map, op);
}
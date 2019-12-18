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
struct cesa_dma_mem {int /*<<< orphan*/ * cdm_vaddr; int /*<<< orphan*/  cdm_tag; int /*<<< orphan*/  cdm_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cesa_free_dma_mem(struct cesa_dma_mem *cdm)
{

	bus_dmamap_unload(cdm->cdm_tag, cdm->cdm_map);
	bus_dmamem_free(cdm->cdm_tag, cdm->cdm_vaddr, cdm->cdm_map);
	bus_dma_tag_destroy(cdm->cdm_tag);
	cdm->cdm_vaddr = NULL;
}
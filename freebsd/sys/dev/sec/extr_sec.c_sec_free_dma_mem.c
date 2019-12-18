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
struct sec_dma_mem {int /*<<< orphan*/ * dma_vaddr; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  dma_map; scalar_t__ dma_is_map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sec_free_dma_mem(struct sec_dma_mem *dma_mem)
{

	/* Check for double free */
	if (dma_mem->dma_vaddr == NULL)
		return;

	bus_dmamap_unload(dma_mem->dma_tag, dma_mem->dma_map);

	if (dma_mem->dma_is_map)
		bus_dmamap_destroy(dma_mem->dma_tag, dma_mem->dma_map);
	else
		bus_dmamem_free(dma_mem->dma_tag, dma_mem->dma_vaddr,
		    dma_mem->dma_map);

	bus_dma_tag_destroy(dma_mem->dma_tag);
	dma_mem->dma_vaddr = NULL;
}
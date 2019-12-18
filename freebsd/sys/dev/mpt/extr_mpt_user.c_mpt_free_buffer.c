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
struct mpt_page_memory {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  tag; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mpt_free_buffer(struct mpt_page_memory *page_mem)
{

	if (page_mem->vaddr == NULL)
		return;
	bus_dmamap_unload(page_mem->tag, page_mem->map);
	bus_dmamem_free(page_mem->tag, page_mem->vaddr, page_mem->map);
	bus_dma_tag_destroy(page_mem->tag);
	page_mem->vaddr = NULL;
}
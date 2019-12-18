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
struct vmci_softc {int dummy; } ;
struct vmci_dma_alloc {scalar_t__ dma_paddr; int /*<<< orphan*/ * dma_tag; int /*<<< orphan*/  dma_map; int /*<<< orphan*/ * dma_vaddr; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct vmci_dma_alloc*,int) ; 

__attribute__((used)) static void
vmci_dma_free_int(struct vmci_softc *sc, struct vmci_dma_alloc *dma)
{

	if (dma->dma_tag != NULL) {
		if (dma->dma_paddr != 0) {
			bus_dmamap_sync(dma->dma_tag, dma->dma_map,
			    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(dma->dma_tag, dma->dma_map);
		}

		if (dma->dma_vaddr != NULL)
			bus_dmamem_free(dma->dma_tag, dma->dma_vaddr,
			    dma->dma_map);

		bus_dma_tag_destroy(dma->dma_tag);
	}
	bzero(dma, sizeof(struct vmci_dma_alloc));
}
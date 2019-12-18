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
struct pvscsi_softc {int dummy; } ;
struct pvscsi_dma {scalar_t__ paddr; int /*<<< orphan*/ * tag; int /*<<< orphan*/  map; int /*<<< orphan*/ * vaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (struct pvscsi_dma*,int) ; 

__attribute__((used)) static void
pvscsi_dma_free(struct pvscsi_softc *sc, struct pvscsi_dma *dma)
{

	if (dma->tag != NULL) {
		if (dma->paddr != 0) {
			bus_dmamap_unload(dma->tag, dma->map);
		}

		if (dma->vaddr != NULL) {
			bus_dmamem_free(dma->tag, dma->vaddr, dma->map);
		}

		bus_dma_tag_destroy(dma->tag);
	}

	bzero(dma, sizeof(*dma));
}
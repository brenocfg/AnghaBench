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
struct bxe_softc {int dummy; } ;
struct bxe_dma {scalar_t__ size; int /*<<< orphan*/ * tag; int /*<<< orphan*/  map; int /*<<< orphan*/  vaddr; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  DBASSERT (struct bxe_softc*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct bxe_dma*,int /*<<< orphan*/ ,int) ; 

void
bxe_dma_free(struct bxe_softc *sc,
             struct bxe_dma   *dma)
{
    if (dma->size > 0) {
        DBASSERT(sc, (dma->tag != NULL), ("dma tag is NULL"));

        bus_dmamap_sync(dma->tag, dma->map,
                        (BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE));
        bus_dmamap_unload(dma->tag, dma->map);
        bus_dmamem_free(dma->tag, dma->vaddr, dma->map);
        bus_dma_tag_destroy(dma->tag);
    }

    memset(dma, 0, sizeof(*dma));
}
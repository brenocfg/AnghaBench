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
struct mrsas_softc {int /*<<< orphan*/ * ctlr_info_tag; int /*<<< orphan*/  ctlr_info_dmamap; int /*<<< orphan*/ * ctlr_info_mem; scalar_t__ ctlr_info_phys_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mrsas_free_ctlr_info_cmd(struct mrsas_softc *sc)
{
	if (sc->ctlr_info_phys_addr)
		bus_dmamap_unload(sc->ctlr_info_tag, sc->ctlr_info_dmamap);
	if (sc->ctlr_info_mem != NULL)
		bus_dmamem_free(sc->ctlr_info_tag, sc->ctlr_info_mem, sc->ctlr_info_dmamap);
	if (sc->ctlr_info_tag != NULL)
		bus_dma_tag_destroy(sc->ctlr_info_tag);
}
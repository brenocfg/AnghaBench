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
struct mrsas_softc {int /*<<< orphan*/ * ioc_init_tag; int /*<<< orphan*/  ioc_init_dmamap; int /*<<< orphan*/ * ioc_init_mem; scalar_t__ ioc_init_phys_mem; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
mrsas_free_ioc_cmd(struct mrsas_softc *sc)
{
	if (sc->ioc_init_phys_mem)
		bus_dmamap_unload(sc->ioc_init_tag, sc->ioc_init_dmamap);
	if (sc->ioc_init_mem != NULL)
		bus_dmamem_free(sc->ioc_init_tag, sc->ioc_init_mem, sc->ioc_init_dmamap);
	if (sc->ioc_init_tag != NULL)
		bus_dma_tag_destroy(sc->ioc_init_tag);
}
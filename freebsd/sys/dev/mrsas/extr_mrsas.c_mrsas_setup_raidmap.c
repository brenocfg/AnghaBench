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
struct mrsas_softc {int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/ * raidmap_mem; int /*<<< orphan*/ * raidmap_phys_addr; int /*<<< orphan*/  max_map_sz; int /*<<< orphan*/ * raidmap_dmamap; int /*<<< orphan*/ * raidmap_tag; int /*<<< orphan*/  mrsas_parent_tag; void** ld_drv_map; int /*<<< orphan*/  drv_map_sz; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  M_MRSAS ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrsas_addr_cb ; 
 int /*<<< orphan*/  mrsas_get_map_info (struct mrsas_softc*) ; 
 int /*<<< orphan*/  mrsas_sync_map_info (struct mrsas_softc*) ; 

__attribute__((used)) static int
mrsas_setup_raidmap(struct mrsas_softc *sc)
{
	int i;

	for (i = 0; i < 2; i++) {
		sc->ld_drv_map[i] =
		    (void *)malloc(sc->drv_map_sz, M_MRSAS, M_NOWAIT);
		/* Do Error handling */
		if (!sc->ld_drv_map[i]) {
			device_printf(sc->mrsas_dev, "Could not allocate memory for local map");

			if (i == 1)
				free(sc->ld_drv_map[0], M_MRSAS);
			/* ABORT driver initialization */
			goto ABORT;
		}
	}

	for (int i = 0; i < 2; i++) {
		if (bus_dma_tag_create(sc->mrsas_parent_tag,
		    4, 0,
		    BUS_SPACE_MAXADDR_32BIT,
		    BUS_SPACE_MAXADDR,
		    NULL, NULL,
		    sc->max_map_sz,
		    1,
		    sc->max_map_sz,
		    BUS_DMA_ALLOCNOW,
		    NULL, NULL,
		    &sc->raidmap_tag[i])) {
			device_printf(sc->mrsas_dev,
			    "Cannot allocate raid map tag.\n");
			return (ENOMEM);
		}
		if (bus_dmamem_alloc(sc->raidmap_tag[i],
		    (void **)&sc->raidmap_mem[i],
		    BUS_DMA_NOWAIT, &sc->raidmap_dmamap[i])) {
			device_printf(sc->mrsas_dev,
			    "Cannot allocate raidmap memory.\n");
			return (ENOMEM);
		}
		bzero(sc->raidmap_mem[i], sc->max_map_sz);

		if (bus_dmamap_load(sc->raidmap_tag[i], sc->raidmap_dmamap[i],
		    sc->raidmap_mem[i], sc->max_map_sz,
		    mrsas_addr_cb, &sc->raidmap_phys_addr[i],
		    BUS_DMA_NOWAIT)) {
			device_printf(sc->mrsas_dev, "Cannot load raidmap memory.\n");
			return (ENOMEM);
		}
		if (!sc->raidmap_mem[i]) {
			device_printf(sc->mrsas_dev,
			    "Cannot allocate memory for raid map.\n");
			return (ENOMEM);
		}
	}

	if (!mrsas_get_map_info(sc))
		mrsas_sync_map_info(sc);

	return (0);

ABORT:
	return (1);
}
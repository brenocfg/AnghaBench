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
struct mrsas_tmp_dcmd {int /*<<< orphan*/  tmp_dcmd_mem; int /*<<< orphan*/  tmp_dcmd_phys_addr; int /*<<< orphan*/  tmp_dcmd_dmamap; int /*<<< orphan*/  tmp_dcmd_tag; } ;
struct mrsas_softc {int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/  mrsas_parent_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_ALLOCNOW ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENOMEM ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mrsas_addr_cb ; 

int
mrsas_alloc_tmp_dcmd(struct mrsas_softc *sc,
    struct mrsas_tmp_dcmd *tcmd, int size)
{
	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    1, 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    size,
	    1,
	    size,
	    BUS_DMA_ALLOCNOW,
	    NULL, NULL,
	    &tcmd->tmp_dcmd_tag)) {
		device_printf(sc->mrsas_dev, "Cannot allocate tmp dcmd tag\n");
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(tcmd->tmp_dcmd_tag, (void **)&tcmd->tmp_dcmd_mem,
	    BUS_DMA_NOWAIT, &tcmd->tmp_dcmd_dmamap)) {
		device_printf(sc->mrsas_dev, "Cannot allocate tmp dcmd mem\n");
		return (ENOMEM);
	}
	if (bus_dmamap_load(tcmd->tmp_dcmd_tag, tcmd->tmp_dcmd_dmamap,
	    tcmd->tmp_dcmd_mem, size, mrsas_addr_cb,
	    &tcmd->tmp_dcmd_phys_addr, BUS_DMA_NOWAIT)) {
		device_printf(sc->mrsas_dev, "Cannot load tmp dcmd mem\n");
		return (ENOMEM);
	}
	memset(tcmd->tmp_dcmd_mem, 0, size);
	return (0);
}
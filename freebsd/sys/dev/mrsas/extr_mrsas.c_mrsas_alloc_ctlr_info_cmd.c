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
struct mrsas_softc {int /*<<< orphan*/  ctlr_info_mem; int /*<<< orphan*/  mrsas_dev; int /*<<< orphan*/  ctlr_info_phys_addr; int /*<<< orphan*/  ctlr_info_dmamap; int /*<<< orphan*/  ctlr_info_tag; int /*<<< orphan*/  mrsas_parent_tag; } ;
struct mrsas_ctrl_info {int dummy; } ;

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
mrsas_alloc_ctlr_info_cmd(struct mrsas_softc *sc)
{
	int ctlr_info_size;

	/* Allocate get controller info command */
	ctlr_info_size = sizeof(struct mrsas_ctrl_info);
	if (bus_dma_tag_create(sc->mrsas_parent_tag,
	    1, 0,
	    BUS_SPACE_MAXADDR_32BIT,
	    BUS_SPACE_MAXADDR,
	    NULL, NULL,
	    ctlr_info_size,
	    1,
	    ctlr_info_size,
	    BUS_DMA_ALLOCNOW,
	    NULL, NULL,
	    &sc->ctlr_info_tag)) {
		device_printf(sc->mrsas_dev, "Cannot allocate ctlr info tag\n");
		return (ENOMEM);
	}
	if (bus_dmamem_alloc(sc->ctlr_info_tag, (void **)&sc->ctlr_info_mem,
	    BUS_DMA_NOWAIT, &sc->ctlr_info_dmamap)) {
		device_printf(sc->mrsas_dev, "Cannot allocate ctlr info cmd mem\n");
		return (ENOMEM);
	}
	if (bus_dmamap_load(sc->ctlr_info_tag, sc->ctlr_info_dmamap,
	    sc->ctlr_info_mem, ctlr_info_size, mrsas_addr_cb,
	    &sc->ctlr_info_phys_addr, BUS_DMA_NOWAIT)) {
		device_printf(sc->mrsas_dev, "Cannot load ctlr info cmd mem\n");
		return (ENOMEM);
	}
	memset(sc->ctlr_info_mem, 0, ctlr_info_size);
	return (0);
}
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
struct sc_info {int bufsize; int /*<<< orphan*/  rbuf; int /*<<< orphan*/  pbuf; int /*<<< orphan*/  dev; int /*<<< orphan*/  rmap; int /*<<< orphan*/  dmat; int /*<<< orphan*/  pmap; int /*<<< orphan*/  ih; void* irq; scalar_t__ irqid; void* cs; int /*<<< orphan*/  csh; int /*<<< orphan*/  cst; scalar_t__ csid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR ; 
 int /*<<< orphan*/  BUS_SPACE_MAXADDR_32BIT ; 
 int ENXIO ; 
 int /*<<< orphan*/  Giant ; 
 int HDSPE_DMASEGSIZE ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_AV ; 
 scalar_t__ PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ bus_dma_tag_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sc_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  busdma_lock_mutex ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hdspe_dmapsetmap ; 
 int /*<<< orphan*/  hdspe_intr ; 
 int /*<<< orphan*/  rman_get_bushandle (void*) ; 
 int /*<<< orphan*/  rman_get_bustag (void*) ; 

__attribute__((used)) static int
hdspe_alloc_resources(struct sc_info *sc)
{

	/* Allocate resource. */
	sc->csid = PCIR_BAR(0);
	sc->cs = bus_alloc_resource_any(sc->dev, SYS_RES_MEMORY,
	    &sc->csid, RF_ACTIVE);

	if (!sc->cs) {
		device_printf(sc->dev, "Unable to map SYS_RES_MEMORY.\n");
		return (ENXIO);
	}

	sc->cst = rman_get_bustag(sc->cs);
	sc->csh = rman_get_bushandle(sc->cs);

	/* Allocate interrupt resource. */
	sc->irqid = 0;
	sc->irq = bus_alloc_resource_any(sc->dev, SYS_RES_IRQ, &sc->irqid,
	    RF_ACTIVE | RF_SHAREABLE);

	if (!sc->irq ||
	    bus_setup_intr(sc->dev, sc->irq, INTR_MPSAFE | INTR_TYPE_AV,
		NULL, hdspe_intr, sc, &sc->ih)) {
		device_printf(sc->dev, "Unable to alloc interrupt resource.\n");
		return (ENXIO);
	}

	/* Allocate DMA resources. */
	if (bus_dma_tag_create(/*parent*/bus_get_dma_tag(sc->dev),
		/*alignment*/4,
		/*boundary*/0,
		/*lowaddr*/BUS_SPACE_MAXADDR_32BIT,
		/*highaddr*/BUS_SPACE_MAXADDR,
		/*filter*/NULL,
		/*filterarg*/NULL,
		/*maxsize*/2 * HDSPE_DMASEGSIZE,
		/*nsegments*/2,
		/*maxsegsz*/HDSPE_DMASEGSIZE,
		/*flags*/0,
		/*lockfunc*/busdma_lock_mutex,
		/*lockarg*/&Giant,
		/*dmatag*/&sc->dmat) != 0) {
		device_printf(sc->dev, "Unable to create dma tag.\n");
		return (ENXIO);
	}

	sc->bufsize = HDSPE_DMASEGSIZE;

	/* pbuf (play buffer). */
	if (bus_dmamem_alloc(sc->dmat, (void **)&sc->pbuf,
		BUS_DMA_NOWAIT, &sc->pmap)) {
		device_printf(sc->dev, "Can't alloc pbuf.\n");
		return (ENXIO);
	}

	if (bus_dmamap_load(sc->dmat, sc->pmap, sc->pbuf, sc->bufsize,
		hdspe_dmapsetmap, sc, 0)) {
		device_printf(sc->dev, "Can't load pbuf.\n");
		return (ENXIO);
	}

	/* rbuf (rec buffer). */
	if (bus_dmamem_alloc(sc->dmat, (void **)&sc->rbuf,
		BUS_DMA_NOWAIT, &sc->rmap)) {
		device_printf(sc->dev, "Can't alloc rbuf.\n");
		return (ENXIO);
	}

	if (bus_dmamap_load(sc->dmat, sc->rmap, sc->rbuf, sc->bufsize,
		hdspe_dmapsetmap, sc, 0)) {
		device_printf(sc->dev, "Can't load rbuf.\n");
		return (ENXIO);
	}

	bzero(sc->pbuf, sc->bufsize);
	bzero(sc->rbuf, sc->bufsize);

	return (0);
}
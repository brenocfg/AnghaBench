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
typedef  int uint32_t ;
struct zy7_devcfg_softc {int /*<<< orphan*/  dma_map; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/  sc_mtx; } ;
struct uio {scalar_t__ uio_offset; int uio_resid; } ;
struct cdev {struct zy7_devcfg_softc* si_drv1; } ;
typedef  scalar_t__ bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int /*<<< orphan*/  DEVCFG_SC_LOCK (struct zy7_devcfg_softc*) ; 
 int /*<<< orphan*/  DEVCFG_SC_UNLOCK (struct zy7_devcfg_softc*) ; 
 int EIO ; 
 int MIN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  PCATCH ; 
 int RD4 (struct zy7_devcfg_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct zy7_devcfg_softc*,int /*<<< orphan*/ ,int) ; 
 int ZY7_DEVCFG_DMA_ADDR_ILLEGAL ; 
 int ZY7_DEVCFG_DMA_ADDR_WAIT_PCAP ; 
 int /*<<< orphan*/  ZY7_DEVCFG_DMA_DST_ADDR ; 
 int /*<<< orphan*/  ZY7_DEVCFG_DMA_DST_LEN ; 
 int /*<<< orphan*/  ZY7_DEVCFG_DMA_SRC_ADDR ; 
 int /*<<< orphan*/  ZY7_DEVCFG_DMA_SRC_LEN ; 
 int ZY7_DEVCFG_INT_ALL ; 
 int ZY7_DEVCFG_INT_DMA_DONE ; 
 int /*<<< orphan*/  ZY7_DEVCFG_INT_MASK ; 
 int ZY7_DEVCFG_INT_PCFG_DONE ; 
 int /*<<< orphan*/  ZY7_DEVCFG_INT_STATUS ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_dmamem_alloc (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hz ; 
 int mtx_sleep (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int uiomove (void*,int,struct uio*) ; 
 int /*<<< orphan*/  zy7_devcfg_init_hw (struct zy7_devcfg_softc*) ; 
 int zy7_devcfg_reset_pl (struct zy7_devcfg_softc*) ; 
 int /*<<< orphan*/  zy7_dma_cb2 ; 
 int /*<<< orphan*/  zy7_en_level_shifters ; 
 int /*<<< orphan*/  zy7_slcr_postload_pl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zy7_slcr_preload_pl () ; 

__attribute__((used)) static int
zy7_devcfg_write(struct cdev *dev, struct uio *uio, int ioflag)
{
	struct zy7_devcfg_softc *sc = dev->si_drv1;
	void *dma_mem;
	bus_addr_t dma_physaddr;
	int segsz, err;

	DEVCFG_SC_LOCK(sc);

	/* First write?  Reset PL. */
	if (uio->uio_offset == 0 && uio->uio_resid > 0)	{
		zy7_devcfg_init_hw(sc);
		zy7_slcr_preload_pl();
		err = zy7_devcfg_reset_pl(sc);
		if (err != 0) {
			DEVCFG_SC_UNLOCK(sc);
			return (err);
		}
	}

	/* Allocate dma memory and load. */
	err = bus_dmamem_alloc(sc->dma_tag, &dma_mem, BUS_DMA_NOWAIT,
			       &sc->dma_map);
	if (err != 0) {
		DEVCFG_SC_UNLOCK(sc);
		return (err);
	}
	err = bus_dmamap_load(sc->dma_tag, sc->dma_map, dma_mem, PAGE_SIZE,
			      zy7_dma_cb2, &dma_physaddr, 0);
	if (err != 0) {
		bus_dmamem_free(sc->dma_tag, dma_mem, sc->dma_map);
		DEVCFG_SC_UNLOCK(sc);
		return (err);
	}

	while (uio->uio_resid > 0) {
		/* If DONE signal has been set, we shouldn't write anymore. */
		if ((RD4(sc, ZY7_DEVCFG_INT_STATUS) &
		     ZY7_DEVCFG_INT_PCFG_DONE) != 0) {
			err = EIO;
			break;
		}

		/* uiomove the data from user buffer to our dma map. */
		segsz = MIN(PAGE_SIZE, uio->uio_resid);
		DEVCFG_SC_UNLOCK(sc);
		err = uiomove(dma_mem, segsz, uio);
		DEVCFG_SC_LOCK(sc);
		if (err != 0)
			break;

		/* Flush the cache to memory. */
		bus_dmamap_sync(sc->dma_tag, sc->dma_map,
				BUS_DMASYNC_PREWRITE);

		/* Program devcfg's DMA engine.  The ordering of these
		 * register writes is critical.
		 */
		if (uio->uio_resid > segsz)
			WR4(sc, ZY7_DEVCFG_DMA_SRC_ADDR,
			    (uint32_t) dma_physaddr);
		else
			WR4(sc, ZY7_DEVCFG_DMA_SRC_ADDR,
			    (uint32_t) dma_physaddr |
			    ZY7_DEVCFG_DMA_ADDR_WAIT_PCAP);
		WR4(sc, ZY7_DEVCFG_DMA_DST_ADDR, ZY7_DEVCFG_DMA_ADDR_ILLEGAL);
		WR4(sc, ZY7_DEVCFG_DMA_SRC_LEN, (segsz+3)/4);
		WR4(sc, ZY7_DEVCFG_DMA_DST_LEN, 0);

		/* Now clear done bit and set up DMA done interrupt. */
		WR4(sc, ZY7_DEVCFG_INT_STATUS, ZY7_DEVCFG_INT_ALL);
		WR4(sc, ZY7_DEVCFG_INT_MASK, ~ZY7_DEVCFG_INT_DMA_DONE);

		/* Wait for DMA done interrupt. */
		err = mtx_sleep(sc->dma_map, &sc->sc_mtx, PCATCH,
				"zy7dma", hz);
		if (err != 0)
			break;

		bus_dmamap_sync(sc->dma_tag, sc->dma_map,
				BUS_DMASYNC_POSTWRITE);

		/* Check DONE signal. */
		if ((RD4(sc, ZY7_DEVCFG_INT_STATUS) &
		     ZY7_DEVCFG_INT_PCFG_DONE) != 0)
			zy7_slcr_postload_pl(zy7_en_level_shifters);
	}

	bus_dmamap_unload(sc->dma_tag, sc->dma_map);
	bus_dmamem_free(sc->dma_tag, dma_mem, sc->dma_map);
	DEVCFG_SC_UNLOCK(sc);
	return (err);
}
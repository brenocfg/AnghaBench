#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cesa_softc {scalar_t__ sc_soc_id; int /*<<< orphan*/  sc_sc_lock; int /*<<< orphan*/  sc_tdesc_lock; int /*<<< orphan*/  sc_sdesc_lock; int /*<<< orphan*/  sc_requests_lock; int /*<<< orphan*/  sc_sessions_lock; int /*<<< orphan*/  sc_sram_size; int /*<<< orphan*/  sc_sram_base_va; int /*<<< orphan*/ * sc_res; int /*<<< orphan*/  sc_icookie; int /*<<< orphan*/  sc_data_dtag; int /*<<< orphan*/  sc_tdesc_cdm; int /*<<< orphan*/  sc_sdesc_cdm; int /*<<< orphan*/  sc_requests_cdm; TYPE_1__* sc_requests; int /*<<< orphan*/  sc_cid; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  cr_dmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CESA_ICM ; 
 int /*<<< orphan*/  CESA_REG_WRITE (struct cesa_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int CESA_REQUESTS ; 
 int /*<<< orphan*/  CESA_TDMA_EMR ; 
 int /*<<< orphan*/  CESA_TDMA_WRITE (struct cesa_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MV_DEV_88F6810 ; 
 scalar_t__ MV_DEV_88F6820 ; 
 scalar_t__ MV_DEV_88F6828 ; 
 size_t RES_CESA_IRQ ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cesa_free_dma_mem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cesa_res_spec ; 
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 struct cesa_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_unmapdev (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
cesa_detach(device_t dev)
{
	struct cesa_softc *sc;
	int i;
 
	sc = device_get_softc(dev);

	/* TODO: Wait for queued requests completion before shutdown. */

	/* Mask interrupts */
	CESA_REG_WRITE(sc, CESA_ICM, 0);
	CESA_TDMA_WRITE(sc, CESA_TDMA_EMR, 0);

	/* Unregister from OCF */
	crypto_unregister_all(sc->sc_cid);

	/* Free DMA Maps */
	for (i = 0; i < CESA_REQUESTS; i++)
		bus_dmamap_destroy(sc->sc_data_dtag,
		    sc->sc_requests[i].cr_dmap);

	/* Free DMA Memory */
	cesa_free_dma_mem(&sc->sc_requests_cdm);
	cesa_free_dma_mem(&sc->sc_sdesc_cdm);
	cesa_free_dma_mem(&sc->sc_tdesc_cdm);

	/* Free DMA Tag */
	bus_dma_tag_destroy(sc->sc_data_dtag);

	/* Stop interrupt */
	bus_teardown_intr(dev, sc->sc_res[RES_CESA_IRQ], sc->sc_icookie);

	/* Relase I/O and IRQ resources */
	bus_release_resources(dev, cesa_res_spec, sc->sc_res);

	/* Unmap SRAM memory */
	if (sc->sc_soc_id == MV_DEV_88F6828 ||
	    sc->sc_soc_id == MV_DEV_88F6820 ||
	    sc->sc_soc_id == MV_DEV_88F6810)
		pmap_unmapdev(sc->sc_sram_base_va, sc->sc_sram_size);

	/* Destroy mutexes */
	mtx_destroy(&sc->sc_sessions_lock);
	mtx_destroy(&sc->sc_requests_lock);
	mtx_destroy(&sc->sc_sdesc_lock);
	mtx_destroy(&sc->sc_tdesc_lock);
	mtx_destroy(&sc->sc_sc_lock);

	return (0);
}
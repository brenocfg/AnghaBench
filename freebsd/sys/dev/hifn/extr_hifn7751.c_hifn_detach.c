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
struct hifn_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_bar0res; int /*<<< orphan*/  sc_bar1res; int /*<<< orphan*/  sc_dmat; int /*<<< orphan*/  sc_dmamap; int /*<<< orphan*/  sc_dma; int /*<<< orphan*/  sc_irq; int /*<<< orphan*/  sc_intrhand; int /*<<< orphan*/  sc_cid; scalar_t__ sc_rndtest; int /*<<< orphan*/  sc_rngto; int /*<<< orphan*/  sc_tickto; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  HIFN_1_DMA_CNFG ; 
 int /*<<< orphan*/  HIFN_1_DMA_IER ; 
 int /*<<< orphan*/  HIFN_BAR0 ; 
 int /*<<< orphan*/  HIFN_BAR1 ; 
 int HIFN_DMACNFG_DMARESET ; 
 int HIFN_DMACNFG_MODE ; 
 int HIFN_DMACNFG_MSTRESET ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WRITE_REG_1 (struct hifn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 struct hifn_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rndtest_detach (scalar_t__) ; 

__attribute__((used)) static int 
hifn_detach(device_t dev)
{
	struct hifn_softc *sc = device_get_softc(dev);

	KASSERT(sc != NULL, ("hifn_detach: null software carrier!"));

	/* disable interrupts */
	WRITE_REG_1(sc, HIFN_1_DMA_IER, 0);

	/*XXX other resources */
	callout_stop(&sc->sc_tickto);
	callout_stop(&sc->sc_rngto);
#ifdef HIFN_RNDTEST
	if (sc->sc_rndtest)
		rndtest_detach(sc->sc_rndtest);
#endif

	/* Turn off DMA polling */
	WRITE_REG_1(sc, HIFN_1_DMA_CNFG, HIFN_DMACNFG_MSTRESET |
	    HIFN_DMACNFG_DMARESET | HIFN_DMACNFG_MODE);

	crypto_unregister_all(sc->sc_cid);

	bus_generic_detach(dev);	/*XXX should be no children, right? */

	bus_teardown_intr(dev, sc->sc_irq, sc->sc_intrhand);
	/* XXX don't store rid */
	bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq);

	bus_dmamap_unload(sc->sc_dmat, sc->sc_dmamap);
	bus_dmamem_free(sc->sc_dmat, sc->sc_dma, sc->sc_dmamap);
	bus_dma_tag_destroy(sc->sc_dmat);

	bus_release_resource(dev, SYS_RES_MEMORY, HIFN_BAR1, sc->sc_bar1res);
	bus_release_resource(dev, SYS_RES_MEMORY, HIFN_BAR0, sc->sc_bar0res);

	mtx_destroy(&sc->sc_mtx);

	return (0);
}
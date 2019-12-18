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
struct safe_softc {int /*<<< orphan*/  sc_sr; int /*<<< orphan*/  sc_dstdmat; int /*<<< orphan*/  sc_srcdmat; int /*<<< orphan*/  sc_irq; int /*<<< orphan*/  sc_ih; int /*<<< orphan*/  sc_ringalloc; int /*<<< orphan*/  sc_ringmtx; int /*<<< orphan*/  sc_spalloc; int /*<<< orphan*/  sc_dpalloc; scalar_t__ sc_rndtest; int /*<<< orphan*/  sc_cid; int /*<<< orphan*/  sc_rngto; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BS_BAR ; 
 int /*<<< orphan*/  SAFE_HI_MASK ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  WRITE_REG (struct safe_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  crypto_unregister_all (int /*<<< orphan*/ ) ; 
 struct safe_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rndtest_detach (scalar_t__) ; 
 int /*<<< orphan*/  safe_cleanchip (struct safe_softc*) ; 
 int /*<<< orphan*/  safe_dma_free (struct safe_softc*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
safe_detach(device_t dev)
{
	struct safe_softc *sc = device_get_softc(dev);

	/* XXX wait/abort active ops */

	WRITE_REG(sc, SAFE_HI_MASK, 0);		/* disable interrupts */

	callout_stop(&sc->sc_rngto);

	crypto_unregister_all(sc->sc_cid);

#ifdef SAFE_RNDTEST
	if (sc->sc_rndtest)
		rndtest_detach(sc->sc_rndtest);
#endif

	safe_cleanchip(sc);
	safe_dma_free(sc, &sc->sc_dpalloc);
	safe_dma_free(sc, &sc->sc_spalloc);
	mtx_destroy(&sc->sc_ringmtx);
	safe_dma_free(sc, &sc->sc_ringalloc);

	bus_generic_detach(dev);
	bus_teardown_intr(dev, sc->sc_irq, sc->sc_ih);
	bus_release_resource(dev, SYS_RES_IRQ, 0, sc->sc_irq);

	bus_dma_tag_destroy(sc->sc_srcdmat);
	bus_dma_tag_destroy(sc->sc_dstdmat);
	bus_release_resource(dev, SYS_RES_MEMORY, BS_BAR, sc->sc_sr);

	return (0);
}
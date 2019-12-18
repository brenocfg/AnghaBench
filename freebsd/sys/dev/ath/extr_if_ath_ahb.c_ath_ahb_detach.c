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
struct ath_softc {int sc_invalid; scalar_t__ sc_eepromdata; int /*<<< orphan*/  sc_dmat; } ;
struct ath_ahb_softc {int /*<<< orphan*/  sc_sr; int /*<<< orphan*/  sc_irq; int /*<<< orphan*/  sc_ih; struct ath_softc sc_sc; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_LOCK_DESTROY (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_PCU_LOCK_DESTROY (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_RX_LOCK_DESTROY (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_TXSTATUS_LOCK_DESTROY (struct ath_softc*) ; 
 int /*<<< orphan*/  ATH_TX_LOCK_DESTROY (struct ath_softc*) ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  ath_detach (struct ath_softc*) ; 
 int /*<<< orphan*/  bus_child_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ath_ahb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath_ahb_detach(device_t dev)
{
	struct ath_ahb_softc *psc = device_get_softc(dev);
	struct ath_softc *sc = &psc->sc_sc;

	/* check if device was removed */
	sc->sc_invalid = !bus_child_present(dev);

	ath_detach(sc);

	bus_generic_detach(dev);
	bus_teardown_intr(dev, psc->sc_irq, psc->sc_ih);
	bus_release_resource(dev, SYS_RES_IRQ, 0, psc->sc_irq);

	bus_dma_tag_destroy(sc->sc_dmat);
	bus_release_resource(dev, SYS_RES_MEMORY, 0, psc->sc_sr);
	/* XXX?! */
	if (sc->sc_eepromdata)
		free(sc->sc_eepromdata, M_TEMP);

	ATH_TXSTATUS_LOCK_DESTROY(sc);
	ATH_RX_LOCK_DESTROY(sc);
	ATH_TX_LOCK_DESTROY(sc);
	ATH_PCU_LOCK_DESTROY(sc);
	ATH_LOCK_DESTROY(sc);

	return (0);
}
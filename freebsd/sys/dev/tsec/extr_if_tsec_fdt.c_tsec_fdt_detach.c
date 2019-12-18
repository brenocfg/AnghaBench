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
struct tsec_softc {int /*<<< orphan*/  ic_lock; int /*<<< orphan*/  transmit_lock; int /*<<< orphan*/  receive_lock; scalar_t__ sc_rres; int /*<<< orphan*/  sc_rrid; int /*<<< orphan*/  sc_error_irid; int /*<<< orphan*/  sc_error_ihand; int /*<<< orphan*/  sc_error_ires; int /*<<< orphan*/  sc_receive_irid; int /*<<< orphan*/  sc_receive_ihand; int /*<<< orphan*/  sc_receive_ires; int /*<<< orphan*/  sc_transmit_irid; int /*<<< orphan*/  sc_transmit_ihand; int /*<<< orphan*/  sc_transmit_ires; int /*<<< orphan*/  tsec_callout; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct tsec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsec_detach (struct tsec_softc*) ; 
 int /*<<< orphan*/  tsec_release_intr (struct tsec_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
tsec_fdt_detach(device_t dev)
{
	struct tsec_softc *sc;
	int error;

	sc = device_get_softc(dev);

	/* Wait for stopping watchdog */
	callout_drain(&sc->tsec_callout);

	/* Stop and release all interrupts */
	tsec_release_intr(sc, sc->sc_transmit_ires, sc->sc_transmit_ihand,
	    sc->sc_transmit_irid, "TX");
	tsec_release_intr(sc, sc->sc_receive_ires, sc->sc_receive_ihand,
	    sc->sc_receive_irid, "RX");
	tsec_release_intr(sc, sc->sc_error_ires, sc->sc_error_ihand,
	    sc->sc_error_irid, "ERR");

	/* TSEC detach */
	tsec_detach(sc);

	/* Free IO memory handler */
	if (sc->sc_rres) {
		error = bus_release_resource(dev, SYS_RES_MEMORY, sc->sc_rrid,
		    sc->sc_rres);
		if (error)
			device_printf(dev, "bus_release_resource() failed for"
			    " IO memory, error %d\n", error);
	}

	/* Destroy locks */
	mtx_destroy(&sc->receive_lock);
	mtx_destroy(&sc->transmit_lock);
	mtx_destroy(&sc->ic_lock);
	return (0);
}
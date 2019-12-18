#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct uart_softc {int sc_leaving; TYPE_2__* sc_class; int /*<<< orphan*/  sc_hwmtx_s; int /*<<< orphan*/ * sc_rres; int /*<<< orphan*/  sc_rrid; int /*<<< orphan*/  sc_rtype; int /*<<< orphan*/ * sc_ires; int /*<<< orphan*/  sc_irid; int /*<<< orphan*/  sc_icookie; struct uart_softc* sc_rxbuf; struct uart_softc* sc_txbuf; TYPE_1__* sc_sysdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {scalar_t__ size; } ;
struct TYPE_5__ {scalar_t__ size; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* detach ) (struct uart_softc*) ;int /*<<< orphan*/ * hwmtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_UART ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  UART_DETACH (struct uart_softc*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* device_get_driver (int /*<<< orphan*/ ) ; 
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct uart_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_tty_detach (struct uart_softc*) ; 

int
uart_bus_detach(device_t dev)
{
	struct uart_softc *sc;

	sc = device_get_softc(dev);

	sc->sc_leaving = 1;

	if (sc->sc_sysdev != NULL)
		sc->sc_sysdev->hwmtx = NULL;

	UART_DETACH(sc);

	if (sc->sc_sysdev != NULL && sc->sc_sysdev->detach != NULL)
		(*sc->sc_sysdev->detach)(sc);
	else
		uart_tty_detach(sc);

	free(sc->sc_txbuf, M_UART);
	free(sc->sc_rxbuf, M_UART);

	if (sc->sc_ires != NULL) {
		bus_teardown_intr(dev, sc->sc_ires, sc->sc_icookie);
		bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irid,
		    sc->sc_ires);
	}
	bus_release_resource(dev, sc->sc_rtype, sc->sc_rrid, sc->sc_rres);

	mtx_destroy(&sc->sc_hwmtx_s);

	if (sc->sc_class->size > device_get_driver(dev)->size) {
		device_set_softc(dev, NULL);
		free(sc, M_UART);
	}

	return (0);
}
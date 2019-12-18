#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  regshft; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; } ;
struct uart_softc {TYPE_1__ sc_bas; int /*<<< orphan*/ * sc_class; TYPE_2__* sc_sysdev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int /*<<< orphan*/  bas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CVMX_MIO_UARTX_RBR (int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 TYPE_2__* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ bus_space_map (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int uart_bus_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_bus_space_mem ; 
 int /*<<< orphan*/  uart_getrange (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_oct16550_class ; 
 int /*<<< orphan*/  uart_sysdevs ; 

__attribute__((used)) static int
uart_octeon_probe(device_t dev)
{
	struct uart_softc *sc;
	int unit;

	unit = device_get_unit(dev);
	sc = device_get_softc(dev);
	sc->sc_class = &uart_oct16550_class;

	/*
	 * We inherit the settings from the systme console.  Note, the bst
	 * bad bus_space_map are bogus here, but obio doesn't yet support
	 * them, it seems.
	 */
	sc->sc_sysdev = SLIST_FIRST(&uart_sysdevs);
	bcopy(&sc->sc_sysdev->bas, &sc->sc_bas, sizeof(sc->sc_bas));
	sc->sc_bas.bst = uart_bus_space_mem;
	/*
	 * XXX
	 * RBR isn't really a great base address.
	 */
	if (bus_space_map(sc->sc_bas.bst, CVMX_MIO_UARTX_RBR(0),
	    uart_getrange(sc->sc_class), 0, &sc->sc_bas.bsh) != 0)
		return (ENXIO);
	return (uart_bus_probe(dev, sc->sc_bas.regshft, 0, 0, 0, unit, 0));
}
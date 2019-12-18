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
struct uart_opal_softc {scalar_t__ vtermid; int polltime; int /*<<< orphan*/  tp; int /*<<< orphan*/  callout; int /*<<< orphan*/  sc_icookie; int /*<<< orphan*/ * irqres; scalar_t__ irqrid; int /*<<< orphan*/  dev; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  node; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  cn_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  CALLOUT_MPSAFE ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 int MTX_NOWITNESS ; 
 int MTX_QUIET ; 
 int MTX_SPIN ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct uart_opal_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct uart_opal_softc*) ; 
 struct uart_opal_softc* console_sc ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct uart_opal_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ ,struct uart_opal_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tty_alloc (int /*<<< orphan*/ *,struct uart_opal_softc*) ; 
 int /*<<< orphan*/  tty_init_console (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__ uart_opal_consdev ; 
 int /*<<< orphan*/  uart_opal_intr ; 
 int /*<<< orphan*/  uart_opal_probe_node (struct uart_opal_softc*) ; 
 int /*<<< orphan*/  uart_opal_tty_class ; 

__attribute__((used)) static int
uart_opal_attach(device_t dev)
{
	struct uart_opal_softc *sc;
	int unit;

	sc = device_get_softc(dev);
	sc->node = ofw_bus_get_node(dev);
	uart_opal_probe_node(sc);

	unit = device_get_unit(dev);
	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL,
	    MTX_SPIN | MTX_QUIET | MTX_NOWITNESS);

	if (console_sc != NULL && console_sc->vtermid == sc->vtermid) {
		device_printf(dev, "console\n");
		device_set_softc(dev, console_sc);
		sc = console_sc;
		sprintf(uart_opal_consdev.cn_name, "ttyu%r", unit);
	}
	sc->tp = tty_alloc(&uart_opal_tty_class, sc);

	if (console_sc == sc)
		tty_init_console(sc->tp, 0);

	sc->dev = dev;
	sc->irqrid = 0;
	sc->irqres = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqrid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->irqres != NULL) {
		bus_setup_intr(dev, sc->irqres, INTR_TYPE_TTY | INTR_MPSAFE,
		    NULL, uart_opal_intr, sc, &sc->sc_icookie);
	} else {
		callout_init(&sc->callout, CALLOUT_MPSAFE);
		sc->polltime = hz / 20;
		if (sc->polltime < 1)
			sc->polltime = 1;
		callout_reset(&sc->callout, sc->polltime, uart_opal_intr, sc);
	}

	tty_makedev(sc->tp, NULL, "u%r", unit);

	return (0);
}
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
struct uart_phyp_softc {scalar_t__ vtermid; int polltime; int /*<<< orphan*/  tp; int /*<<< orphan*/  callout; int /*<<< orphan*/  sc_icookie; int /*<<< orphan*/ * irqres; scalar_t__ irqrid; int /*<<< orphan*/  outseqno; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  node; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  cn_name; } ;

/* Variables and functions */
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 int MTX_NOWITNESS ; 
 int MTX_QUIET ; 
 int MTX_SPIN ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct uart_phyp_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct uart_phyp_softc*) ; 
 struct uart_phyp_softc* console_sc ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct uart_phyp_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  tty_alloc (int /*<<< orphan*/ *,struct uart_phyp_softc*) ; 
 int /*<<< orphan*/  tty_init_console (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_makedev (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 TYPE_1__ uart_phyp_consdev ; 
 int /*<<< orphan*/  uart_phyp_intr ; 
 int /*<<< orphan*/  uart_phyp_probe_node (struct uart_phyp_softc*) ; 
 int /*<<< orphan*/  uart_phyp_tty_class ; 

__attribute__((used)) static int
uart_phyp_attach(device_t dev)
{
	struct uart_phyp_softc *sc;
	int unit;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->node = ofw_bus_get_node(dev);
	uart_phyp_probe_node(sc);

	unit = device_get_unit(dev);
	sc->tp = tty_alloc(&uart_phyp_tty_class, sc);
	mtx_init(&sc->sc_mtx, device_get_nameunit(dev), NULL,
	    MTX_SPIN | MTX_QUIET | MTX_NOWITNESS);

	if (console_sc != NULL && console_sc->vtermid == sc->vtermid) {
		sc->outseqno = console_sc->outseqno;
		console_sc = sc;
		sprintf(uart_phyp_consdev.cn_name, "ttyu%r", unit);
		tty_init_console(sc->tp, 0);
	}

	sc->irqrid = 0;
	sc->irqres = bus_alloc_resource_any(dev, SYS_RES_IRQ, &sc->irqrid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->irqres != NULL) {
		bus_setup_intr(dev, sc->irqres, INTR_TYPE_TTY | INTR_MPSAFE,
		    NULL, uart_phyp_intr, sc, &sc->sc_icookie);
	} else {
		callout_init(&sc->callout, 1);
		sc->polltime = hz / 20;
		if (sc->polltime < 1)
			sc->polltime = 1;
		callout_reset(&sc->callout, sc->polltime, uart_phyp_intr, sc);
	}

	tty_makedev(sc->tp, NULL, "u%r", unit);

	return (0);
}
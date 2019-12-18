#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timeout_t ;
struct TYPE_6__ {int /*<<< orphan*/  bst; int /*<<< orphan*/  bsh; } ;
struct uart_softc {int sc_leaving; int sc_rxbufsz; int sc_rxfifosz; int sc_txfifosz; int sc_testintr; int sc_fastintr; int sc_polled; int /*<<< orphan*/  sc_hwmtx_s; int /*<<< orphan*/ * sc_rres; int /*<<< orphan*/  sc_rrid; int /*<<< orphan*/  sc_rtype; int /*<<< orphan*/ * sc_ires; int /*<<< orphan*/  sc_irid; int /*<<< orphan*/  sc_icookie; void* sc_rxbuf; void* sc_txbuf; int /*<<< orphan*/ * sc_hwmtx; TYPE_3__* sc_sysdev; int /*<<< orphan*/  sc_timer; scalar_t__ sc_hwoflow; scalar_t__ sc_hwiflow; TYPE_2__ sc_bas; TYPE_1__* sc_class; } ;
typedef  int /*<<< orphan*/  driver_intr_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_8__ {scalar_t__ size; } ;
struct TYPE_7__ {int baudrate; int type; size_t parity; int databits; int stopbits; int (* attach ) (struct uart_softc*) ;int /*<<< orphan*/ * hwmtx; struct uart_softc* sc; } ;
struct TYPE_5__ {scalar_t__ size; } ;

/* Variables and functions */
 int ENXIO ; 
 int FILTER_SCHEDULE_THREAD ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  MTX_SPIN ; 
 int /*<<< orphan*/  M_UART ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int UART_ATTACH (struct uart_softc*) ; 
#define  UART_DEV_CONSOLE 130 
#define  UART_DEV_DBGPORT 129 
#define  UART_DEV_KEYBOARD 128 
 scalar_t__ UART_IOCTL (struct uart_softc*,int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  UART_IOCTL_BAUD ; 
 int /*<<< orphan*/  bcopy (struct uart_softc*,struct uart_softc*,int) ; 
 scalar_t__ bootverbose ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int (*) (struct uart_softc*),int /*<<< orphan*/ *,struct uart_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,struct uart_softc*) ; 
 TYPE_4__* device_get_driver (int /*<<< orphan*/ ) ; 
 struct uart_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_print_prettyname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_softc (int /*<<< orphan*/ ,struct uart_softc*) ; 
 int /*<<< orphan*/  free (void*,int /*<<< orphan*/ ) ; 
 int hz ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 
 int stub1 (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_force_poll ; 
 int uart_intr (struct uart_softc*) ; 
 int uart_poll_freq ; 
 int /*<<< orphan*/  uart_pps_init (struct uart_softc*) ; 
 int uart_tty_attach (struct uart_softc*) ; 

int
uart_bus_attach(device_t dev)
{
	struct uart_softc *sc, *sc0;
	const char *sep;
	int error, filt;

	/*
	 * The sc_class field defines the type of UART we're going to work
	 * with and thus the size of the softc. Replace the generic softc
	 * with one that matches the UART now that we're certain we handle
	 * the device.
	 */
	sc0 = device_get_softc(dev);
	if (sc0->sc_class->size > device_get_driver(dev)->size) {
		sc = malloc(sc0->sc_class->size, M_UART, M_WAITOK|M_ZERO);
		bcopy(sc0, sc, sizeof(*sc));
		device_set_softc(dev, sc);
	} else
		sc = sc0;

	/*
	 * Now that we know the softc for this device, connect the back
	 * pointer from the sysdev for this device, if any
	 */
	if (sc->sc_sysdev != NULL)
		sc->sc_sysdev->sc = sc;

	/*
	 * Protect ourselves against interrupts while we're not completely
	 * finished attaching and initializing. We don't expect interrupts
	 * until after UART_ATTACH(), though.
	 */
	sc->sc_leaving = 1;

	mtx_init(&sc->sc_hwmtx_s, "uart_hwmtx", NULL, MTX_SPIN);
	if (sc->sc_hwmtx == NULL)
		sc->sc_hwmtx = &sc->sc_hwmtx_s;

	/*
	 * Re-allocate. We expect that the softc contains the information
	 * collected by uart_bus_probe() intact.
	 */
	sc->sc_rres = bus_alloc_resource_any(dev, sc->sc_rtype, &sc->sc_rrid,
	    RF_ACTIVE);
	if (sc->sc_rres == NULL) {
		mtx_destroy(&sc->sc_hwmtx_s);
		return (ENXIO);
	}
	sc->sc_bas.bsh = rman_get_bushandle(sc->sc_rres);
	sc->sc_bas.bst = rman_get_bustag(sc->sc_rres);

	/*
	 * Ensure there is room for at least three full FIFOs of data in the
	 * receive buffer (handles the case of low-level drivers with huge
	 * FIFOs), and also ensure that there is no less than the historical
	 * size of 384 bytes (handles the typical small-FIFO case).
	 */
	sc->sc_rxbufsz = MAX(384, sc->sc_rxfifosz * 3);
	sc->sc_rxbuf = malloc(sc->sc_rxbufsz * sizeof(*sc->sc_rxbuf),
	    M_UART, M_WAITOK);
	sc->sc_txbuf = malloc(sc->sc_txfifosz * sizeof(*sc->sc_txbuf),
	    M_UART, M_WAITOK);

	error = UART_ATTACH(sc);
	if (error)
		goto fail;

	if (sc->sc_hwiflow || sc->sc_hwoflow) {
		sep = "";
		device_print_prettyname(dev);
		if (sc->sc_hwiflow) {
			printf("%sRTS iflow", sep);
			sep = ", ";
		}
		if (sc->sc_hwoflow) {
			printf("%sCTS oflow", sep);
			sep = ", ";
		}
		printf("\n");
	}

	if (sc->sc_sysdev != NULL) {
		if (sc->sc_sysdev->baudrate == 0) {
			if (UART_IOCTL(sc, UART_IOCTL_BAUD,
			    (intptr_t)&sc->sc_sysdev->baudrate) != 0)
				sc->sc_sysdev->baudrate = -1;
		}
		switch (sc->sc_sysdev->type) {
		case UART_DEV_CONSOLE:
			device_printf(dev, "console");
			break;
		case UART_DEV_DBGPORT:
			device_printf(dev, "debug port");
			break;
		case UART_DEV_KEYBOARD:
			device_printf(dev, "keyboard");
			break;
		default:
			device_printf(dev, "unknown system device");
			break;
		}
		printf(" (%d,%c,%d,%d)\n", sc->sc_sysdev->baudrate,
		    "noems"[sc->sc_sysdev->parity], sc->sc_sysdev->databits,
		    sc->sc_sysdev->stopbits);
	}

	sc->sc_leaving = 0;
	sc->sc_testintr = 1;
	filt = uart_intr(sc);
	sc->sc_testintr = 0;

	/*
	 * Don't use interrupts if we couldn't clear any pending interrupt
	 * conditions. We may have broken H/W and polling is probably the
	 * safest thing to do.
	 */
	if (filt != FILTER_SCHEDULE_THREAD && !uart_force_poll) {
		sc->sc_ires = bus_alloc_resource_any(dev, SYS_RES_IRQ,
		    &sc->sc_irid, RF_ACTIVE | RF_SHAREABLE);
	}
	if (sc->sc_ires != NULL) {
		error = bus_setup_intr(dev, sc->sc_ires, INTR_TYPE_TTY,
		    uart_intr, NULL, sc, &sc->sc_icookie);
		sc->sc_fastintr = (error == 0) ? 1 : 0;

		if (!sc->sc_fastintr)
			error = bus_setup_intr(dev, sc->sc_ires,
			    INTR_TYPE_TTY | INTR_MPSAFE, NULL,
			    (driver_intr_t *)uart_intr, sc, &sc->sc_icookie);

		if (error) {
			device_printf(dev, "could not activate interrupt\n");
			bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irid,
			    sc->sc_ires);
			sc->sc_ires = NULL;
		}
	}
	if (sc->sc_ires == NULL) {
		/* No interrupt resource. Force polled mode. */
		sc->sc_polled = 1;
		callout_init(&sc->sc_timer, 1);
		callout_reset(&sc->sc_timer, hz / uart_poll_freq,
		    (timeout_t *)uart_intr, sc);
	}

	if (bootverbose && (sc->sc_fastintr || sc->sc_polled)) {
		sep = "";
		device_print_prettyname(dev);
		if (sc->sc_fastintr) {
			printf("%sfast interrupt", sep);
			sep = ", ";
		}
		if (sc->sc_polled) {
			printf("%spolled mode (%dHz)", sep, uart_poll_freq);
			sep = ", ";
		}
		printf("\n");
	}

	if (sc->sc_sysdev != NULL && sc->sc_sysdev->attach != NULL) {
		if ((error = sc->sc_sysdev->attach(sc)) != 0)
			goto fail;
	} else {
		if ((error = uart_tty_attach(sc)) != 0)
			goto fail;
		uart_pps_init(sc);
	}

	if (sc->sc_sysdev != NULL)
		sc->sc_sysdev->hwmtx = sc->sc_hwmtx;

	return (0);

 fail:
	free(sc->sc_txbuf, M_UART);
	free(sc->sc_rxbuf, M_UART);

	if (sc->sc_ires != NULL) {
		bus_teardown_intr(dev, sc->sc_ires, sc->sc_icookie);
		bus_release_resource(dev, SYS_RES_IRQ, sc->sc_irid,
		    sc->sc_ires);
	}
	bus_release_resource(dev, sc->sc_rtype, sc->sc_rrid, sc->sc_rres);

	mtx_destroy(&sc->sc_hwmtx_s);

	return (error);
}
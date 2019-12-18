#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_softc {int sc_opened; int /*<<< orphan*/  sc_softih; int /*<<< orphan*/ * sc_sysdev; int /*<<< orphan*/  sc_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  sc_kbd; struct uart_softc* sc_uart; int /*<<< orphan*/ * sc_sysdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_TYPE_TTY ; 
 int /*<<< orphan*/  KBD_INIT_DONE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SWI_TTY ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kbd_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunkbd_enable (int /*<<< orphan*/ *) ; 
 TYPE_1__ sunkbd_softc ; 
 int /*<<< orphan*/  sunkbd_uart_intr ; 
 int /*<<< orphan*/  swi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_intr_event ; 
 int /*<<< orphan*/  uart_driver_name ; 

__attribute__((used)) static int
sunkbd_attach(struct uart_softc *sc)
{

	/*
	 * Don't attach if we didn't probe the keyboard. Note that
	 * the UART is still marked as a system device in that case.
	 */
	if (sunkbd_softc.sc_sysdev == NULL) {
		device_printf(sc->sc_dev, "keyboard not present\n");
		return (0);
	}

	if (sc->sc_sysdev != NULL) {
		sunkbd_softc.sc_uart = sc;

#ifdef KBD_INSTALL_CDEV
		kbd_attach(&sunkbd_softc.sc_kbd);
#endif
		sunkbd_enable(&sunkbd_softc.sc_kbd);

		swi_add(&tty_intr_event, uart_driver_name, sunkbd_uart_intr,
		    &sunkbd_softc, SWI_TTY, INTR_TYPE_TTY, &sc->sc_softih);

		sc->sc_opened = 1;
		KBD_INIT_DONE(&sunkbd_softc.sc_kbd);
	}

	return (0);
}
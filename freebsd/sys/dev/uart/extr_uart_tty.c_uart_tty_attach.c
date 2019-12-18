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
struct TYPE_4__ {struct tty* tp; } ;
struct TYPE_5__ {TYPE_1__ u_tty; } ;
struct uart_softc {int /*<<< orphan*/  sc_softih; TYPE_3__* sc_sysdev; int /*<<< orphan*/  sc_dev; TYPE_2__ sc_u; } ;
struct tty {int dummy; } ;
struct consdev {int /*<<< orphan*/  cn_name; } ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  baudrate; scalar_t__ cookie; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTR_TYPE_TTY ; 
 int /*<<< orphan*/  SWI_TTY ; 
 scalar_t__ UART_DEV_CONSOLE ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  swi_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct uart_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct tty* tty_alloc (int /*<<< orphan*/ *,struct uart_softc*) ; 
 int /*<<< orphan*/  tty_init_console (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_intr_event ; 
 int /*<<< orphan*/  tty_makedev (struct tty*,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  uart_driver_name ; 
 int /*<<< orphan*/  uart_tty_class ; 
 int /*<<< orphan*/  uart_tty_intr ; 

int
uart_tty_attach(struct uart_softc *sc)
{
	struct tty *tp;
	int unit;

	sc->sc_u.u_tty.tp = tp = tty_alloc(&uart_tty_class, sc);

	unit = device_get_unit(sc->sc_dev);

	if (sc->sc_sysdev != NULL && sc->sc_sysdev->type == UART_DEV_CONSOLE) {
		sprintf(((struct consdev *)sc->sc_sysdev->cookie)->cn_name,
		    "ttyu%r", unit);
		tty_init_console(tp, sc->sc_sysdev->baudrate);
	}

	swi_add(&tty_intr_event, uart_driver_name, uart_tty_intr, sc, SWI_TTY,
	    INTR_TYPE_TTY, &sc->sc_softih);

	tty_makedev(tp, NULL, "u%r", unit);

	return (0);
}
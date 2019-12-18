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
struct tty {int dummy; } ;
struct altera_jtag_uart_softc {int ajus_flags; int /*<<< orphan*/  ajus_ac_callout; int /*<<< orphan*/  ajus_io_callout; int /*<<< orphan*/  ajus_irq_cookie; int /*<<< orphan*/ * ajus_irq_res; int /*<<< orphan*/  ajus_dev; struct tty* ajus_ttyp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AJU_LOCK (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_LOCK_DESTROY (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_UNLOCK (struct altera_jtag_uart_softc*) ; 
 int ALTERA_JTAG_UART_FLAG_CONSOLE ; 
 int /*<<< orphan*/ * aju_cons_sc ; 
 int /*<<< orphan*/  aju_intr_disable (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_rel_gone (struct tty*) ; 

void
altera_jtag_uart_detach(struct altera_jtag_uart_softc *sc)
{
	struct tty *tp = sc->ajus_ttyp;

	/*
	 * If we're using interrupts, disable and release the interrupt
	 * handler now.  Otherwise drain the polling timeout.
	 */
	if (sc->ajus_irq_res != NULL) {
		AJU_LOCK(sc);
		aju_intr_disable(sc);
		AJU_UNLOCK(sc);
		bus_teardown_intr(sc->ajus_dev, sc->ajus_irq_res,
		    sc->ajus_irq_cookie);
	} else
		callout_drain(&sc->ajus_io_callout);
	callout_drain(&sc->ajus_ac_callout);
	if (sc->ajus_flags & ALTERA_JTAG_UART_FLAG_CONSOLE)
		aju_cons_sc = NULL;
	tty_lock(tp);
	tty_rel_gone(tp);
	AJU_LOCK_DESTROY(sc);
}
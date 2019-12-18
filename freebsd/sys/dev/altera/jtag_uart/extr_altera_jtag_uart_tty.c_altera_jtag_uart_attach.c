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
struct altera_jtag_uart_softc {int ajus_flags; int /*<<< orphan*/  ajus_ac_callout; int /*<<< orphan*/  ajus_io_callout; int /*<<< orphan*/ * ajus_irq_res; int /*<<< orphan*/  ajus_unit; struct tty* ajus_ttyp; int /*<<< orphan*/  ajus_dev; int /*<<< orphan*/  ajus_irq_cookie; int /*<<< orphan*/  ajus_jtag_missed; int /*<<< orphan*/ * ajus_jtag_missedp; int /*<<< orphan*/  ajus_jtag_present; int /*<<< orphan*/ * ajus_jtag_presentp; int /*<<< orphan*/  ajus_buffer_data; int /*<<< orphan*/ * ajus_buffer_datap; int /*<<< orphan*/  ajus_buffer_valid; int /*<<< orphan*/ * ajus_buffer_validp; int /*<<< orphan*/  ajus_lock; int /*<<< orphan*/ * ajus_lockp; int /*<<< orphan*/  ajus_mem_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  AJU_AC_POLLINTERVAL ; 
 int /*<<< orphan*/  AJU_IO_POLLINTERVAL ; 
 int /*<<< orphan*/  AJU_LOCK (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_LOCK_DESTROY (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_LOCK_INIT (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_TTYNAME ; 
 int /*<<< orphan*/  AJU_UNLOCK (struct altera_jtag_uart_softc*) ; 
 int ALTERA_JTAG_UART_FLAG_CONSOLE ; 
 scalar_t__ BERI_UART_BASE ; 
 int INTR_ENTROPY ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_TTY ; 
 int /*<<< orphan*/  aju_ac_callout ; 
 int /*<<< orphan*/  aju_cons_buffer_data ; 
 int /*<<< orphan*/  aju_cons_buffer_valid ; 
 int /*<<< orphan*/  aju_cons_jtag_missed ; 
 int /*<<< orphan*/  aju_cons_jtag_present ; 
 int /*<<< orphan*/  aju_cons_lock ; 
 struct altera_jtag_uart_softc* aju_cons_sc ; 
 int /*<<< orphan*/  aju_intr ; 
 int /*<<< orphan*/  aju_intr_disable (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  aju_intr_readable_enable (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  aju_io_callout ; 
 int /*<<< orphan*/  aju_ttydevsw ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct altera_jtag_uart_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rman_get_start (int /*<<< orphan*/ ) ; 
 struct tty* tty_alloc (int /*<<< orphan*/ *,struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  tty_init_console (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_makedev (struct tty*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
altera_jtag_uart_attach(struct altera_jtag_uart_softc *sc)
{
	struct tty *tp;
	int error;

	AJU_LOCK_INIT(sc);

	/*
	 * XXXRW: Currently, we detect the console solely based on it using a
	 * reserved address, and borrow console-level locks and buffer if so.
	 * Is there a better way?
	 */
	if (rman_get_start(sc->ajus_mem_res) == BERI_UART_BASE) {
		sc->ajus_lockp = &aju_cons_lock;
		sc->ajus_buffer_validp = &aju_cons_buffer_valid;
		sc->ajus_buffer_datap = &aju_cons_buffer_data;
		sc->ajus_jtag_presentp = &aju_cons_jtag_present;
		sc->ajus_jtag_missedp = &aju_cons_jtag_missed;
		sc->ajus_flags |= ALTERA_JTAG_UART_FLAG_CONSOLE;
	} else {
		sc->ajus_lockp = &sc->ajus_lock;
		sc->ajus_buffer_validp = &sc->ajus_buffer_valid;
		sc->ajus_buffer_datap = &sc->ajus_buffer_data;
		sc->ajus_jtag_presentp = &sc->ajus_jtag_present;
		sc->ajus_jtag_missedp = &sc->ajus_jtag_missed;
	}

	/*
	 * Disable interrupts regardless of whether or not we plan to use
	 * them.  We will register an interrupt handler now if they will be
	 * used, but not re-enable intil later once the remainder of the tty
	 * layer is properly initialised, as we're not ready for input yet.
	 */
	AJU_LOCK(sc);
	aju_intr_disable(sc);
	AJU_UNLOCK(sc);
	if (sc->ajus_irq_res != NULL) {
		error = bus_setup_intr(sc->ajus_dev, sc->ajus_irq_res,
		    INTR_ENTROPY | INTR_TYPE_TTY | INTR_MPSAFE, NULL,
		    aju_intr, sc, &sc->ajus_irq_cookie);
		if (error) {
			device_printf(sc->ajus_dev,
			    "could not activate interrupt\n");
			AJU_LOCK_DESTROY(sc);
			return (error);
		}
	}
	tp = sc->ajus_ttyp = tty_alloc(&aju_ttydevsw, sc);
	if (sc->ajus_flags & ALTERA_JTAG_UART_FLAG_CONSOLE) {
		aju_cons_sc = sc;
		tty_init_console(tp, 0);
	}
	tty_makedev(tp, NULL, "%s%d", AJU_TTYNAME, sc->ajus_unit);

	/*
	 * If we will be using interrupts, enable them now; otherwise, start
	 * polling.  From this point onwards, input can arrive.
	 */
	if (sc->ajus_irq_res != NULL) {
		AJU_LOCK(sc);
		aju_intr_readable_enable(sc);
		AJU_UNLOCK(sc);
	} else {
		callout_init(&sc->ajus_io_callout, 1);
		callout_reset(&sc->ajus_io_callout, AJU_IO_POLLINTERVAL,
		    aju_io_callout, sc);
	}
	callout_init(&sc->ajus_ac_callout, 1);
	callout_reset(&sc->ajus_ac_callout, AJU_AC_POLLINTERVAL,
	    aju_ac_callout, sc);
	return (0);
}
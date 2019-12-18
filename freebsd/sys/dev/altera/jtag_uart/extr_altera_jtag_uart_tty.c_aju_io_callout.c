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
struct altera_jtag_uart_softc {int /*<<< orphan*/  ajus_io_callout; struct tty* ajus_ttyp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AJU_IO_POLLINTERVAL ; 
 int /*<<< orphan*/  AJU_LOCK (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_UNLOCK (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  aju_handle_input (struct altera_jtag_uart_softc*,struct tty*) ; 
 int /*<<< orphan*/  aju_handle_output (struct altera_jtag_uart_softc*,struct tty*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static void
aju_io_callout(void *arg)
{
	struct altera_jtag_uart_softc *sc = arg;
	struct tty *tp = sc->ajus_ttyp;

	tty_lock(tp);
	AJU_LOCK(sc);

	/*
	 * It would be convenient if we could share code with aju_intr() here
	 * by testing the control register for ALTERA_JTAG_UART_CONTROL_RI and
	 * ALTERA_JTAG_UART_CONTROL_WI.  Unfortunately, it's not clear that
	 * this is supported, so do all the work to poll for both input and
	 * output.
	 */
	aju_handle_input(sc, tp);
	aju_handle_output(sc, tp);

	/*
	 * Reschedule next poll attempt.  There's some argument that we should
	 * do adaptive polling based on the expectation of I/O: is something
	 * pending in the output buffer, or have we recently had input, but we
	 * don't.
	 */
	callout_reset(&sc->ajus_io_callout, AJU_IO_POLLINTERVAL,
	    aju_io_callout, sc);
	AJU_UNLOCK(sc);
	tty_unlock(tp);
}
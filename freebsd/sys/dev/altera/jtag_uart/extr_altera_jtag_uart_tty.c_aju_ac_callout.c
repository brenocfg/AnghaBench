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
typedef  int uint32_t ;
struct tty {int dummy; } ;
struct altera_jtag_uart_softc {int* ajus_jtag_presentp; scalar_t__* ajus_jtag_missedp; int /*<<< orphan*/  ajus_ac_callout; struct tty* ajus_ttyp; } ;

/* Variables and functions */
 int /*<<< orphan*/  AJU_AC_POLLINTERVAL ; 
 scalar_t__ AJU_JTAG_MAXMISS ; 
 int /*<<< orphan*/  AJU_LOCK (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_UNLOCK (struct altera_jtag_uart_softc*) ; 
 int ALTERA_JTAG_UART_CONTROL_AC ; 
 int aju_control_read (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  aju_control_write (struct altera_jtag_uart_softc*,int) ; 
 int /*<<< orphan*/  aju_handle_output (struct altera_jtag_uart_softc*,struct tty*) ; 
 int /*<<< orphan*/  aju_jtag_appeared ; 
 int /*<<< orphan*/  aju_jtag_vanished ; 
 int /*<<< orphan*/  atomic_add_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 

__attribute__((used)) static void
aju_ac_callout(void *arg)
{
	struct altera_jtag_uart_softc *sc = arg;
	struct tty *tp = sc->ajus_ttyp;
	uint32_t v;

	tty_lock(tp);
	AJU_LOCK(sc);
	v = aju_control_read(sc);
	if (v & ALTERA_JTAG_UART_CONTROL_AC) {
		v &= ~ALTERA_JTAG_UART_CONTROL_AC;
		aju_control_write(sc, v);
		if (*sc->ajus_jtag_presentp == 0) {
			*sc->ajus_jtag_presentp = 1;
			atomic_add_int(&aju_jtag_appeared, 1);
			aju_handle_output(sc, tp);
		}

		/* Any hit eliminates all recent misses. */
		*sc->ajus_jtag_missedp = 0;
	} else if (*sc->ajus_jtag_presentp != 0) {
		/*
		 * If we've exceeded our tolerance for misses, mark JTAG as
		 * disconnected and drain output.  Otherwise, bump the miss
		 * counter.
		 */
		if (*sc->ajus_jtag_missedp > AJU_JTAG_MAXMISS) {
			*sc->ajus_jtag_presentp = 0;
			atomic_add_int(&aju_jtag_vanished, 1);
			aju_handle_output(sc, tp);
		} else
			(*sc->ajus_jtag_missedp)++;
	}
	callout_reset(&sc->ajus_ac_callout, AJU_AC_POLLINTERVAL,
	    aju_ac_callout, sc);
	AJU_UNLOCK(sc);
	tty_unlock(tp);
}
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
struct altera_jtag_uart_softc {int ajus_flags; int /*<<< orphan*/  ajus_alt_break_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AJU_LOCK (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_LOCK_ASSERT (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  AJU_UNLOCK (struct altera_jtag_uart_softc*) ; 
 int ALTERA_JTAG_UART_FLAG_CONSOLE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int aju_read (struct altera_jtag_uart_softc*) ; 
 scalar_t__ aju_readable (struct altera_jtag_uart_softc*) ; 
 int /*<<< orphan*/  kdb_alt_break (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock_assert (struct tty*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 

__attribute__((used)) static void
aju_handle_input(struct altera_jtag_uart_softc *sc, struct tty *tp)
{
	int c;

	tty_lock_assert(tp, MA_OWNED);
	AJU_LOCK_ASSERT(sc);

	while (aju_readable(sc)) {
		c = aju_read(sc);
		AJU_UNLOCK(sc);
#ifdef KDB
		if (sc->ajus_flags & ALTERA_JTAG_UART_FLAG_CONSOLE)
			kdb_alt_break(c, &sc->ajus_alt_break_state);
#endif
		ttydisc_rint(tp, c, 0);
		AJU_LOCK(sc);
	}
	AJU_UNLOCK(sc);
	ttydisc_rint_done(tp);
	AJU_LOCK(sc);
}
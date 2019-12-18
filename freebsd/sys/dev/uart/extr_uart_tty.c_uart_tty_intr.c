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
struct uart_softc {int sc_isquelch; int /*<<< orphan*/  sc_hwiflow; TYPE_2__ sc_u; int /*<<< orphan*/  sc_ttypend; scalar_t__ sc_leaving; } ;
struct TYPE_6__ {int c_cflag; } ;
struct tty {TYPE_3__ t_termios; } ;

/* Variables and functions */
 int CRTS_IFLOW ; 
 int SER_DCD ; 
 int SER_DCTS ; 
 int SER_DDCD ; 
 int /*<<< orphan*/  SER_DRTS ; 
 int SER_INT_BREAK ; 
 int SER_INT_MASK ; 
 int SER_INT_RXREADY ; 
 int SER_INT_SIGCHG ; 
 int SER_INT_SIGMASK ; 
 int SER_INT_TXIDLE ; 
 int TRE_BREAK ; 
 int TRE_FRAMING ; 
 int TRE_OVERRUN ; 
 int TRE_PARITY ; 
 int /*<<< orphan*/  UART_SETSIG (struct uart_softc*,int /*<<< orphan*/ ) ; 
 int UART_STAT_FRAMERR ; 
 int UART_STAT_OVERRUN ; 
 int UART_STAT_PARERR ; 
 int atomic_readandclear_32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_modem (struct tty*,int) ; 
 scalar_t__ ttydisc_rint (struct tty*,int,int) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int /*<<< orphan*/  uart_rx_empty (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_rx_next (struct uart_softc*) ; 
 int uart_rx_peek (struct uart_softc*) ; 
 int /*<<< orphan*/  uart_tty_outwakeup (struct tty*) ; 

void
uart_tty_intr(void *arg)
{
	struct uart_softc *sc = arg;
	struct tty *tp;
	int c, err = 0, pend, sig, xc;

	if (sc->sc_leaving)
		return;

	pend = atomic_readandclear_32(&sc->sc_ttypend);
	if (!(pend & SER_INT_MASK))
		return;

	tp = sc->sc_u.u_tty.tp;
	tty_lock(tp);

	if (pend & SER_INT_RXREADY) {
		while (!uart_rx_empty(sc) && !sc->sc_isquelch) {
			xc = uart_rx_peek(sc);
			c = xc & 0xff;
			if (xc & UART_STAT_FRAMERR)
				err |= TRE_FRAMING;
			if (xc & UART_STAT_OVERRUN)
				err |= TRE_OVERRUN;
			if (xc & UART_STAT_PARERR)
				err |= TRE_PARITY;
			if (ttydisc_rint(tp, c, err) != 0) {
				sc->sc_isquelch = 1;
				if ((tp->t_termios.c_cflag & CRTS_IFLOW) &&
				    !sc->sc_hwiflow)
					UART_SETSIG(sc, SER_DRTS);
			} else
				uart_rx_next(sc);
		}
	}

	if (pend & SER_INT_BREAK)
		ttydisc_rint(tp, 0, TRE_BREAK);

	if (pend & SER_INT_SIGCHG) {
		sig = pend & SER_INT_SIGMASK;
		if (sig & SER_DDCD)
			ttydisc_modem(tp, sig & SER_DCD);
		if (sig & SER_DCTS)
			uart_tty_outwakeup(tp);
	}

	if (pend & SER_INT_TXIDLE)
		uart_tty_outwakeup(tp);
	ttydisc_rint_done(tp);
	tty_unlock(tp);
}
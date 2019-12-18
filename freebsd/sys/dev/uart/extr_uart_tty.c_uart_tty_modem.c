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
struct uart_softc {int sc_hwsig; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int SER_DELTA (int) ; 
 int /*<<< orphan*/  UART_SETSIG (struct uart_softc*,int) ; 
 struct uart_softc* tty_softc (struct tty*) ; 

__attribute__((used)) static int
uart_tty_modem(struct tty *tp, int biton, int bitoff)
{
	struct uart_softc *sc;

	sc = tty_softc(tp);
	if (biton != 0 || bitoff != 0)
		UART_SETSIG(sc, SER_DELTA(bitoff | biton) | biton);
	return (sc->sc_hwsig);
}
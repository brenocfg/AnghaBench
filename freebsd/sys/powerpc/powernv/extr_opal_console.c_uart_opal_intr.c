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
struct uart_opal_softc {int /*<<< orphan*/  polltime; int /*<<< orphan*/  callout; int /*<<< orphan*/ * irqres; struct tty* tp; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPAL_POLL_EVENTS ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct uart_opal_softc*) ; 
 int /*<<< orphan*/  opal_call (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int uart_opal_getc (struct uart_opal_softc*) ; 

__attribute__((used)) static void
uart_opal_intr(void *v)
{
	struct uart_opal_softc *sc = v;
	struct tty *tp = sc->tp;
	int c;

	tty_lock(tp);
	while ((c = uart_opal_getc(sc)) > 0)
		ttydisc_rint(tp, c, 0);
	ttydisc_rint_done(tp);
	tty_unlock(tp);

	opal_call(OPAL_POLL_EVENTS, NULL);

	if (sc->irqres == NULL)
		callout_reset(&sc->callout, sc->polltime, uart_opal_intr, sc);
}
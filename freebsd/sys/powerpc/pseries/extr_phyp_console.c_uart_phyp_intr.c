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
struct uart_phyp_softc {int /*<<< orphan*/  polltime; int /*<<< orphan*/  callout; int /*<<< orphan*/ * irqres; struct tty* tp; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct uart_phyp_softc*) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_unlock (struct tty*) ; 
 int /*<<< orphan*/  ttydisc_rint (struct tty*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ttydisc_rint_done (struct tty*) ; 
 int uart_phyp_get (struct uart_phyp_softc*,unsigned char*,int) ; 

__attribute__((used)) static void
uart_phyp_intr(void *v)
{
	struct uart_phyp_softc *sc = v;
	struct tty *tp = sc->tp;
	unsigned char c;
	int len;

	tty_lock(tp);
	while ((len = uart_phyp_get(sc, &c, 1)) > 0)
		ttydisc_rint(tp, c, 0);
	ttydisc_rint_done(tp);
	tty_unlock(tp);

	if (sc->irqres == NULL)
		callout_reset(&sc->callout, sc->polltime, uart_phyp_intr, sc);
}
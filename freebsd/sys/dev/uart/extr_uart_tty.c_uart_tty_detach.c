#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct tty* tp; } ;
struct TYPE_4__ {TYPE_1__ u_tty; } ;
struct uart_softc {int /*<<< orphan*/  sc_softih; TYPE_2__ sc_u; } ;
struct tty {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  swi_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_lock (struct tty*) ; 
 int /*<<< orphan*/  tty_rel_gone (struct tty*) ; 

int
uart_tty_detach(struct uart_softc *sc)
{
	struct tty *tp;

	tp = sc->sc_u.u_tty.tp;

	tty_lock(tp);
	swi_remove(sc->sc_softih);
	tty_rel_gone(tp);

	return (0);
}
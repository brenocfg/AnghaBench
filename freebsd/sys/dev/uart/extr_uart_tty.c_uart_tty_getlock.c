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
struct TYPE_3__ {int /*<<< orphan*/ * tp; } ;
struct TYPE_4__ {TYPE_1__ u_tty; } ;
struct uart_softc {TYPE_2__ sc_u; } ;
struct mtx {int dummy; } ;

/* Variables and functions */
 struct mtx* tty_getlock (int /*<<< orphan*/ *) ; 

struct mtx *
uart_tty_getlock(struct uart_softc *sc)
{

	if (sc->sc_u.u_tty.tp != NULL)
		return (tty_getlock(sc->sc_u.u_tty.tp));
	else
		return (NULL);
}
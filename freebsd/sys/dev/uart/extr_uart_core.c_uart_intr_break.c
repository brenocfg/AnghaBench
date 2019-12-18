#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uart_softc {scalar_t__ sc_opened; TYPE_1__* sc_sysdev; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SER_INT_BREAK ; 
 scalar_t__ UART_DEV_CONSOLE ; 
 scalar_t__ kdb_break () ; 
 int /*<<< orphan*/  uart_sched_softih (struct uart_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
uart_intr_break(void *arg)
{
	struct uart_softc *sc = arg;

#if defined(KDB)
	if (sc->sc_sysdev != NULL && sc->sc_sysdev->type == UART_DEV_CONSOLE) {
		if (kdb_break())
			return (0);
	}
#endif
	if (sc->sc_opened)
		uart_sched_softih(sc, SER_INT_BREAK);
	return (0);
}
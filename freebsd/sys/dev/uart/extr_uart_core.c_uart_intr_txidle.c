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
struct uart_softc {scalar_t__ sc_txbusy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SER_INT_TXIDLE ; 
 int /*<<< orphan*/  uart_sched_softih (struct uart_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline int
uart_intr_txidle(void *arg)
{
	struct uart_softc *sc = arg;

	if (sc->sc_txbusy) {
		sc->sc_txbusy = 0;
		uart_sched_softih(sc, SER_INT_TXIDLE);
	}
	return (0);
}
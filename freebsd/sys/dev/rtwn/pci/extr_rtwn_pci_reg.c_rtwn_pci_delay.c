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
struct rtwn_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  msecs_to_ticks (int) ; 
 int /*<<< orphan*/  mtx_sleep (struct rtwn_softc*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
rtwn_pci_delay(struct rtwn_softc *sc, int usec)
{
	if (usec < 1000)
		DELAY(usec);
	else {
		(void) mtx_sleep(sc, &sc->sc_mtx, 0, "rtwn_pci",
		    msecs_to_ticks(usec / 1000));
	}
}
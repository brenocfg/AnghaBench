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
typedef  int uint32_t ;
struct intelspi_softc {int sc_flags; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int INTELSPI_BUSY ; 
 int /*<<< orphan*/  INTELSPI_LOCK (struct intelspi_softc*) ; 
 int INTELSPI_READ (struct intelspi_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTELSPI_SSPREG_SSCR1 ; 
 int /*<<< orphan*/  INTELSPI_SSPREG_SSSR ; 
 int /*<<< orphan*/  INTELSPI_UNLOCK (struct intelspi_softc*) ; 
 int /*<<< orphan*/  INTELSPI_WRITE (struct intelspi_softc*,int /*<<< orphan*/ ,int) ; 
 int SSCR1_RIE ; 
 int SSCR1_TIE ; 
 int SSCR1_TINTE ; 
 scalar_t__ intelspi_transact (struct intelspi_softc*) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
intelspi_intr(void *arg)
{
	struct intelspi_softc *sc;
	uint32_t reg;

	sc = (struct intelspi_softc *)arg;

	INTELSPI_LOCK(sc);
	if ((sc->sc_flags & INTELSPI_BUSY) == 0) {
		INTELSPI_UNLOCK(sc);
		return;
	}

	/* Check if SSP if off */
	reg = INTELSPI_READ(sc, INTELSPI_SSPREG_SSSR);
	if (reg == 0xffffffffU) {
		INTELSPI_UNLOCK(sc);
		return;
	}

	/* Check for end of transfer. */
	if (intelspi_transact(sc)) {
		/* Disable interrupts */
		reg = INTELSPI_READ(sc, INTELSPI_SSPREG_SSCR1);
		reg &= ~(SSCR1_TIE | SSCR1_RIE | SSCR1_TINTE);
		INTELSPI_WRITE(sc, INTELSPI_SSPREG_SSCR1, reg);
		wakeup(sc->sc_dev);
	}

	INTELSPI_UNLOCK(sc);
}
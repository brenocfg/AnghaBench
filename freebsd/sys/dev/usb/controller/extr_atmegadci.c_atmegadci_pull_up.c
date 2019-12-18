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
struct TYPE_2__ {int d_pulled_up; scalar_t__ port_powered; } ;
struct atmegadci_softc {TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATMEGA_UDCON ; 
 int /*<<< orphan*/  ATMEGA_WRITE_1 (struct atmegadci_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
atmegadci_pull_up(struct atmegadci_softc *sc)
{
	/* pullup D+, if possible */

	if (!sc->sc_flags.d_pulled_up &&
	    sc->sc_flags.port_powered) {
		sc->sc_flags.d_pulled_up = 1;
		ATMEGA_WRITE_1(sc, ATMEGA_UDCON, 0);
	}
}
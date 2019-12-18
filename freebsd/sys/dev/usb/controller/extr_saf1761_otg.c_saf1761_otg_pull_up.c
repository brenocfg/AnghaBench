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
struct saf1761_otg_softc {TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 

__attribute__((used)) static void
saf1761_otg_pull_up(struct saf1761_otg_softc *sc)
{
	/* activate pullup on D+, if possible */

	if (!sc->sc_flags.d_pulled_up && sc->sc_flags.port_powered) {
		DPRINTF("\n");

		sc->sc_flags.d_pulled_up = 1;
	}
}
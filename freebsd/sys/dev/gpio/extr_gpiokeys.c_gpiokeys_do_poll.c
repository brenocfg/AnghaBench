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
typedef  scalar_t__ uint8_t ;
struct gpiokeys_softc {int sc_flags; scalar_t__ sc_inputs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOKEYS_ASSERT_LOCKED (struct gpiokeys_softc*) ; 
 int GPIOKEYS_GLOBAL_FLAG_POLLING ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  PRI_UNCHANGED ; 
 int /*<<< orphan*/  SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/  kdb_active ; 
 int /*<<< orphan*/  kern_yield (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static void
gpiokeys_do_poll(struct gpiokeys_softc *sc, uint8_t wait)
{

	KASSERT((sc->sc_flags & GPIOKEYS_GLOBAL_FLAG_POLLING) != 0,
	    ("gpiokeys_do_poll called when not polling\n"));

	GPIOKEYS_ASSERT_LOCKED(sc);

	if (!kdb_active && !SCHEDULER_STOPPED()) {
		while (sc->sc_inputs == 0) {
			kern_yield(PRI_UNCHANGED);
			if (!wait)
				break;
		}
		return;
	}

	while ((sc->sc_inputs == 0) && wait) {
		printf("POLL!\n");
	}
}
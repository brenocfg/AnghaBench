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
struct ukbd_softc {scalar_t__ sc_inputs; scalar_t__ sc_delay; int /*<<< orphan*/  sc_time_ms; } ;

/* Variables and functions */
 int /*<<< orphan*/  UKBD_LOCK_ASSERT () ; 
 scalar_t__ ukbd_any_key_pressed (struct ukbd_softc*) ; 
 int /*<<< orphan*/  ukbd_event_keyinput (struct ukbd_softc*) ; 
 int /*<<< orphan*/  ukbd_interrupt (struct ukbd_softc*) ; 
 int /*<<< orphan*/  ukbd_start_timer (struct ukbd_softc*) ; 

__attribute__((used)) static void
ukbd_timeout(void *arg)
{
	struct ukbd_softc *sc = arg;

	UKBD_LOCK_ASSERT();

	sc->sc_time_ms += sc->sc_delay;
	sc->sc_delay = 0;

	ukbd_interrupt(sc);

	/* Make sure any leftover key events gets read out */
	ukbd_event_keyinput(sc);

	if (ukbd_any_key_pressed(sc) || (sc->sc_inputs != 0)) {
		ukbd_start_timer(sc);
	}
}
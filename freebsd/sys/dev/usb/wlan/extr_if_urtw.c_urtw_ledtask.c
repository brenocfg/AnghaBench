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
struct urtw_softc {scalar_t__ sc_strategy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (struct urtw_softc*,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  URTW_DEBUG_STATE ; 
 int /*<<< orphan*/  URTW_LOCK (struct urtw_softc*) ; 
 scalar_t__ URTW_SW_LED_MODE0 ; 
 int /*<<< orphan*/  URTW_UNLOCK (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_led_blink (struct urtw_softc*) ; 

__attribute__((used)) static void
urtw_ledtask(void *arg, int pending)
{
	struct urtw_softc *sc = arg;

	if (sc->sc_strategy != URTW_SW_LED_MODE0) {
		DPRINTF(sc, URTW_DEBUG_STATE,
		    "could not process a LED strategy 0x%x",
		    sc->sc_strategy);
		return;
	}

	URTW_LOCK(sc);
	urtw_led_blink(sc);
	URTW_UNLOCK(sc);
}
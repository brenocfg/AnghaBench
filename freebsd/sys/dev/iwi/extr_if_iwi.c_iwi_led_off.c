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
typedef  int /*<<< orphan*/  uint32_t ;
struct iwi_softc {int /*<<< orphan*/  sc_ledoff; int /*<<< orphan*/  sc_ledtimer; int /*<<< orphan*/  sc_ledpin; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_led_done ; 
 int /*<<< orphan*/  iwi_read_event (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_toggle_event (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iwi_write_event (struct iwi_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iwi_led_off(void *arg)
{
	struct iwi_softc *sc = arg;
	uint32_t v;

	v = iwi_read_event(sc);
	v &= ~sc->sc_ledpin;
	iwi_write_event(sc, iwi_toggle_event(v));
	callout_reset(&sc->sc_ledtimer, sc->sc_ledoff, iwi_led_done, sc);
}
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
struct iwm_softc {int /*<<< orphan*/  sc_led_blink_to; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iwm_mvm_led_disable (struct iwm_softc*) ; 

void
iwm_led_blink_stop(struct iwm_softc *sc)
{
	callout_stop(&sc->sc_led_blink_to);
	iwm_mvm_led_disable(sc);
}
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
struct iwm_softc {scalar_t__ sc_attached; int /*<<< orphan*/  sc_led_blink_to; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,void (*) (void*),struct iwm_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  iwm_mvm_led_disable (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_mvm_led_enable (struct iwm_softc*) ; 
 scalar_t__ iwm_mvm_led_is_enabled (struct iwm_softc*) ; 

__attribute__((used)) static void
iwm_led_blink_timeout(void *arg)
{
	struct iwm_softc *sc = arg;

	if (sc->sc_attached == 0)
		return;

	if (iwm_mvm_led_is_enabled(sc))
		iwm_mvm_led_disable(sc);
	else
		iwm_mvm_led_enable(sc);

	callout_reset(&sc->sc_led_blink_to, (200 * hz) / 1000,
	    iwm_led_blink_timeout, sc);
}
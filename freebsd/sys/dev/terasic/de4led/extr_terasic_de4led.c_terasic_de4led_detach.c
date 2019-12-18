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
struct terasic_de4led_softc {int /*<<< orphan*/ ** tdl_leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERASIC_DE4LED_CLEARBAR (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  TERASIC_DE4LED_LOCK (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  TERASIC_DE4LED_LOCK_DESTROY (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  TERASIC_DE4LED_UNLOCK (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  led_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  terasic_de4led_update (struct terasic_de4led_softc*) ; 

void
terasic_de4led_detach(struct terasic_de4led_softc *sc)
{
	int i;

	for (i = 0; i < 8; i++) {
		led_destroy(sc->tdl_leds[i]);
		sc->tdl_leds[i] = NULL;
	}
	TERASIC_DE4LED_LOCK(sc);
	TERASIC_DE4LED_CLEARBAR(sc);
	terasic_de4led_update(sc);
	TERASIC_DE4LED_UNLOCK(sc);
	TERASIC_DE4LED_LOCK_DESTROY(sc);
}
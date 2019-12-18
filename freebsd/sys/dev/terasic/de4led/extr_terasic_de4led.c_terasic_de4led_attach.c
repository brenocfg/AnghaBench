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
struct terasic_de4led_softc {int /*<<< orphan*/  tdl_unit; int /*<<< orphan*/  tdl_dev; void** tdl_leds; } ;

/* Variables and functions */
 int /*<<< orphan*/  TERASIC_DE4LED_CLEARBAR (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  TERASIC_DE4LED_LOCK (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  TERASIC_DE4LED_LOCK_INIT (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  TERASIC_DE4LED_UNLOCK (struct terasic_de4led_softc*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_0 ; 
 int /*<<< orphan*/  led_1 ; 
 int /*<<< orphan*/  led_2 ; 
 int /*<<< orphan*/  led_3 ; 
 int /*<<< orphan*/  led_4 ; 
 int /*<<< orphan*/  led_5 ; 
 int /*<<< orphan*/  led_6 ; 
 int /*<<< orphan*/  led_7 ; 
 void* led_create (int /*<<< orphan*/ ,struct terasic_de4led_softc*,char*) ; 
 int /*<<< orphan*/  led_set (char*,char const*) ; 
 scalar_t__ resource_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  terasic_de4led_update (struct terasic_de4led_softc*) ; 

void
terasic_de4led_attach(struct terasic_de4led_softc *sc)
{
	const char *cmd;

	TERASIC_DE4LED_LOCK_INIT(sc);

	/*
	 * Clear the LED array before we start.
	 */
	TERASIC_DE4LED_LOCK(sc);
	TERASIC_DE4LED_CLEARBAR(sc);
	terasic_de4led_update(sc);
	TERASIC_DE4LED_UNLOCK(sc);

	/*
	 * Register the LED array with led(4).
	 */
	sc->tdl_leds[0] = led_create(led_0, sc, "de4led_0");
	sc->tdl_leds[1] = led_create(led_1, sc, "de4led_1");
	sc->tdl_leds[2] = led_create(led_2, sc, "de4led_2");
	sc->tdl_leds[3] = led_create(led_3, sc, "de4led_3");
	sc->tdl_leds[4] = led_create(led_4, sc, "de4led_4");
	sc->tdl_leds[5] = led_create(led_5, sc, "de4led_5");
	sc->tdl_leds[6] = led_create(led_6, sc, "de4led_6");
	sc->tdl_leds[7] = led_create(led_7, sc, "de4led_7");

	if (resource_string_value(device_get_name(sc->tdl_dev),
	    sc->tdl_unit, "de4led_0_cmd", &cmd) == 0)
		led_set("de4led_0", cmd);
	if (resource_string_value(device_get_name(sc->tdl_dev),
	    sc->tdl_unit, "de4led_1_cmd", &cmd) == 0)
		led_set("de4led_1", cmd);
	if (resource_string_value(device_get_name(sc->tdl_dev),
	    sc->tdl_unit, "de4led_2_cmd", &cmd) == 0)
		led_set("de4led_2", cmd);
	if (resource_string_value(device_get_name(sc->tdl_dev),
	    sc->tdl_unit, "de4led_3_cmd", &cmd) == 0)
		led_set("de4led_3", cmd);
	if (resource_string_value(device_get_name(sc->tdl_dev),
	    sc->tdl_unit, "de4led_4_cmd", &cmd) == 0)
		led_set("de4led_4", cmd);
	if (resource_string_value(device_get_name(sc->tdl_dev),
	    sc->tdl_unit, "de4led_5_cmd", &cmd) == 0)
		led_set("de4led_5", cmd);
	if (resource_string_value(device_get_name(sc->tdl_dev),
	    sc->tdl_unit, "de4led_6_cmd", &cmd) == 0)
		led_set("de4led_6", cmd);
	if (resource_string_value(device_get_name(sc->tdl_dev),
	    sc->tdl_unit, "de4led_7_cmd", &cmd) == 0)
		led_set("de4led_7", cmd);
}
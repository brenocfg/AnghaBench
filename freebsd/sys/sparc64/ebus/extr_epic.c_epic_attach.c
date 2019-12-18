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
struct epic_softc {void* sc_led_dev_power; void* sc_led_dev_alert; int /*<<< orphan*/  sc_res; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  EPIC_FW_LED_READ (struct epic_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPIC_FW_VERSION ; 
 int /*<<< orphan*/  EPIC_LOCK_INIT (struct epic_softc*) ; 
 scalar_t__ bootverbose ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct epic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  epic_led_alert ; 
 int /*<<< orphan*/  epic_led_power ; 
 int /*<<< orphan*/  epic_res_spec ; 
 void* led_create (int /*<<< orphan*/ ,struct epic_softc*,char*) ; 

__attribute__((used)) static int
epic_attach(device_t dev)
{
	struct epic_softc *sc;

	sc = device_get_softc(dev);
	if (bus_alloc_resources(dev, epic_res_spec, sc->sc_res)) {
		device_printf(dev, "failed to allocate resources\n");
		bus_release_resources(dev, epic_res_spec, sc->sc_res);
		return (ENXIO);
	}

	EPIC_LOCK_INIT(sc);

	if (bootverbose)
		device_printf(dev, "version 0x%x\n",
		    EPIC_FW_LED_READ(sc, EPIC_FW_VERSION));

	sc->sc_led_dev_alert = led_create(epic_led_alert, sc, "alert");
	sc->sc_led_dev_power = led_create(epic_led_power, sc, "power");

	return (0);
}
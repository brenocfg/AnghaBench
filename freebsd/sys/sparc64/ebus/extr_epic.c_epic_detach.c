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
struct epic_softc {int /*<<< orphan*/  sc_res; int /*<<< orphan*/  sc_led_dev_power; int /*<<< orphan*/  sc_led_dev_alert; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  EPIC_LOCK_DESTROY (struct epic_softc*) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct epic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epic_res_spec ; 
 int /*<<< orphan*/  led_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
epic_detach(device_t dev)
{
	struct epic_softc *sc;

	sc = device_get_softc(dev);

	led_destroy(sc->sc_led_dev_alert);
	led_destroy(sc->sc_led_dev_power);

	bus_release_resources(dev, epic_res_spec, sc->sc_res);

	EPIC_LOCK_DESTROY(sc);

	return (0);
}
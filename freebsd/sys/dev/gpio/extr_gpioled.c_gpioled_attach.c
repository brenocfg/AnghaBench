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
struct gpioled_softc {int sc_invert; int /*<<< orphan*/  sc_leddev; int /*<<< orphan*/  sc_busdev; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIOLED_LOCK_INIT (struct gpioled_softc*) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ ) ; 
 char const* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct gpioled_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpioled_control ; 
 int /*<<< orphan*/  led_create_state (int /*<<< orphan*/ ,struct gpioled_softc*,char const*,int) ; 
 int /*<<< orphan*/  resource_int_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 scalar_t__ resource_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 

__attribute__((used)) static int
gpioled_attach(device_t dev)
{
	struct gpioled_softc *sc;
	int state;
	const char *name;

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_busdev = device_get_parent(dev);
	GPIOLED_LOCK_INIT(sc);

	state = 0;

	if (resource_string_value(device_get_name(dev), 
	    device_get_unit(dev), "name", &name))
		name = NULL;
	resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "invert", &sc->sc_invert);
	resource_int_value(device_get_name(dev),
	    device_get_unit(dev), "state", &state);

	sc->sc_leddev = led_create_state(gpioled_control, sc, name ? name :
	    device_get_nameunit(dev), state);

	return (0);
}
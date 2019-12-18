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
struct gpioleds_softc {int /*<<< orphan*/  sc_dev; } ;
struct gpioled {int /*<<< orphan*/  leddev; int /*<<< orphan*/  pin; struct gpioleds_softc* parent_sc; } ;
typedef  int /*<<< orphan*/  phandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_PIN_OUTPUT ; 
 int OF_getprop_alloc (int /*<<< orphan*/ ,char*,void**) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int gpio_pin_get_by_ofw_idx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_pin_setflags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpioled_control ; 
 int /*<<< orphan*/  led_create_state (int /*<<< orphan*/ ,struct gpioled*,char*,int) ; 
 scalar_t__ strcasecmp (char*,char*) ; 

__attribute__((used)) static void
gpioleds_attach_led(struct gpioleds_softc *sc, phandle_t node,
    struct gpioled *led)
{
	char *name;
	int state, err;
	char *default_state;

	led->parent_sc = sc;

	state = 0;
	if (OF_getprop_alloc(node, "default-state",
	    (void **)&default_state) != -1) {
		if (strcasecmp(default_state, "on") == 0)
			state = 1;
		else if (strcasecmp(default_state, "off") == 0)
			state = 0;
		else if (strcasecmp(default_state, "keep") == 0)
			state = -1;
		else {
			state = -1;
			device_printf(sc->sc_dev,
			    "unknown value for default-state in FDT\n");
		}
		OF_prop_free(default_state);
	}

	name = NULL;
	if (OF_getprop_alloc(node, "label", (void **)&name) == -1)
		OF_getprop_alloc(node, "name", (void **)&name);

	if (name == NULL) {
		device_printf(sc->sc_dev,
		    "no name provided for gpio LED, skipping\n");
		return;
	}

	err = gpio_pin_get_by_ofw_idx(sc->sc_dev, node, 0, &led->pin);
	if (err) {
		device_printf(sc->sc_dev, "<%s> failed to map pin\n", name);
		if (name)
			OF_prop_free(name);
		return;
	}
	gpio_pin_setflags(led->pin, GPIO_PIN_OUTPUT);

	led->leddev = led_create_state(gpioled_control, led, name,
	    state);

	if (name != NULL)
		OF_prop_free(name);
}
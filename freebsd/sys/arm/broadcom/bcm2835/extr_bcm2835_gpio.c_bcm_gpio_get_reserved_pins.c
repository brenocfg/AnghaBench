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
struct bcm_gpio_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int ssize_t ;
typedef  scalar_t__ phandle_t ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getprop_alloc (scalar_t__,char*,void**) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 scalar_t__ bcm_gpio_get_ro_pins (struct bcm_gpio_softc*,scalar_t__,char*,char*) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 

__attribute__((used)) static int
bcm_gpio_get_reserved_pins(struct bcm_gpio_softc *sc)
{
	char *name;
	phandle_t gpio, node, reserved;
	ssize_t len;

	/* Get read-only pins if they're provided */
	gpio = ofw_bus_get_node(sc->sc_dev);
	if (bcm_gpio_get_ro_pins(sc, gpio, "broadcom,read-only",
	    "read-only") != 0)
		return (0);
	/* Traverse the GPIO subnodes to find the reserved pins node. */
	reserved = 0;
	node = OF_child(gpio);
	while ((node != 0) && (reserved == 0)) {
		len = OF_getprop_alloc(node, "name", (void **)&name);
		if (len == -1)
			return (-1);
		if (strcmp(name, "reserved") == 0)
			reserved = node;
		OF_prop_free(name);
		node = OF_peer(node);
	}
	if (reserved == 0)
		return (-1);
	/* Get the reserved pins. */
	if (bcm_gpio_get_ro_pins(sc, reserved, "broadcom,pins",
	    "reserved") != 0)
		return (-1);

	return (0);
}
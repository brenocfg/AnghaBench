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
struct gpioleds_softc {size_t sc_total_leds; int /*<<< orphan*/ * sc_leds; int /*<<< orphan*/  sc_busdev; int /*<<< orphan*/  sc_dev; } ;
struct gpioled {int dummy; } ;
typedef  int phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int OF_child (int) ; 
 int /*<<< orphan*/  OF_hasprop (int,char*) ; 
 int OF_peer (int) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct gpioleds_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpioleds_attach_led (struct gpioleds_softc*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int,int /*<<< orphan*/ ,int) ; 
 int ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gpioled_attach(device_t dev)
{
	struct gpioleds_softc *sc;
	phandle_t child, leds;
	int total_leds;

	if ((leds = ofw_bus_get_node(dev)) == -1)
		return (ENXIO);

	sc = device_get_softc(dev);
	sc->sc_dev = dev;
	sc->sc_busdev = device_get_parent(dev);

	/* Traverse the 'gpio-leds' node and count leds */
	total_leds = 0;
	for (child = OF_child(leds); child != 0; child = OF_peer(child)) {
		if (!OF_hasprop(child, "gpios"))
			continue;
		total_leds++;
	}

	if (total_leds) {
		sc->sc_leds =  malloc(sizeof(struct gpioled) * total_leds,
		    M_DEVBUF, M_WAITOK | M_ZERO);

		sc->sc_total_leds = 0;
		/* Traverse the 'gpio-leds' node and count leds */
		for (child = OF_child(leds); child != 0; child = OF_peer(child)) {
			if (!OF_hasprop(child, "gpios"))
				continue;
			gpioleds_attach_led(sc, child, &sc->sc_leds[sc->sc_total_leds]);
			sc->sc_total_leds++;
		}
	}

	return (0);
}
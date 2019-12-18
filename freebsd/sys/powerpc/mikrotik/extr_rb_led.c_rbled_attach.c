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
struct rbled_softc {int /*<<< orphan*/ * sc_led; int /*<<< orphan*/  sc_ledpin; int /*<<< orphan*/ * sc_gpio; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  gp ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  cell_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/ * OF_device_from_xref (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_getprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 struct rbled_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * led_create (int /*<<< orphan*/ ,struct rbled_softc*,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rbled_toggle ; 

__attribute__((used)) static int
rbled_attach(device_t dev)
{
	struct rbled_softc *sc;
	phandle_t node;
	cell_t gp[2];

	sc = device_get_softc(dev);
	node = ofw_bus_get_node(dev);

	if (OF_getprop(node, "user_led", gp, sizeof(gp)) <= 0)
		return (ENXIO);
	
	sc->sc_gpio = OF_device_from_xref(gp[0]);
	if (sc->sc_gpio == NULL) {
		device_printf(dev, "No GPIO resource found!\n");
		return (ENXIO);
	}
	sc->sc_ledpin = gp[1];

	sc->sc_led = led_create(rbled_toggle, sc, "user_led");

	if (sc->sc_led == NULL)
		return (ENXIO);

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  speed ;
typedef  scalar_t__ phandle_t ;
struct TYPE_4__ {int fixed_mask; int fixed25_mask; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ e6000sw_softc_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MV88E6141 ; 
 int /*<<< orphan*/  MV88E6190 ; 
 int /*<<< orphan*/  MV88E6341 ; 
 scalar_t__ MVSWITCH (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ OF_getencprop (scalar_t__,char*,int*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ ofw_bus_find_child (scalar_t__,char*) ; 

__attribute__((used)) static int
e6000sw_parse_fixed_link(e6000sw_softc_t *sc, phandle_t node, uint32_t port)
{
	int speed;
	phandle_t fixed_link;

	fixed_link = ofw_bus_find_child(node, "fixed-link");

	if (fixed_link != 0) {
		sc->fixed_mask |= (1 << port);

		if (OF_getencprop(fixed_link,
		    "speed", &speed, sizeof(speed)) < 0) {
			device_printf(sc->dev,
			    "Port %d has a fixed-link node without a speed "
			    "property\n", port);
			return (ENXIO);
		}
		if (speed == 2500 && (MVSWITCH(sc, MV88E6141) ||
		     MVSWITCH(sc, MV88E6341) || MVSWITCH(sc, MV88E6190)))
			sc->fixed25_mask |= (1 << port);
	}

	return (0);
}
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
struct simplebus_softc {int acells; int scells; scalar_t__ node; int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  OF_getencprop (scalar_t__,char*,int*,int) ; 
 struct simplebus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ ) ; 

void
simplebus_init(device_t dev, phandle_t node)
{
	struct simplebus_softc *sc;

	sc = device_get_softc(dev);
	if (node == 0)
		node = ofw_bus_get_node(dev);
	sc->dev = dev;
	sc->node = node;

	/*
	 * Some important numbers
	 */
	sc->acells = 2;
	OF_getencprop(node, "#address-cells", &sc->acells, sizeof(sc->acells));
	sc->scells = 1;
	OF_getencprop(node, "#size-cells", &sc->scells, sizeof(sc->scells));
}
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
struct simplebus_softc {int /*<<< orphan*/  node; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (int /*<<< orphan*/ ) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 struct simplebus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  simplebus_add_device (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ simplebus_fill_ranges (int /*<<< orphan*/ ,struct simplebus_softc*) ; 
 int /*<<< orphan*/  simplebus_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
simplebus_attach(device_t dev)
{
	struct		simplebus_softc *sc;
	phandle_t	node;

	sc = device_get_softc(dev);
	simplebus_init(dev, 0);
	if (simplebus_fill_ranges(sc->node, sc) < 0) {
		device_printf(dev, "could not get ranges\n");
		return (ENXIO);
	}

	/*
	 * In principle, simplebus could have an interrupt map, but ignore that
	 * for now
	 */

	for (node = OF_child(sc->node); node > 0; node = OF_peer(node))
		simplebus_add_device(dev, node, 0, NULL, -1, NULL);
	return (bus_generic_attach(dev));
}
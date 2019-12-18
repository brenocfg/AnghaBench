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
struct pl330_softc {int /*<<< orphan*/ * ih; int /*<<< orphan*/ ** res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  phandle_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  OF_device_register_xref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OF_xref_from_node (int /*<<< orphan*/ ) ; 
 int PL330_NCHANNELS ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pl330_softc*,int /*<<< orphan*/ ) ; 
 struct pl330_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl330_intr ; 
 int /*<<< orphan*/  pl330_spec ; 

__attribute__((used)) static int
pl330_attach(device_t dev)
{
	struct pl330_softc *sc;
	phandle_t xref, node;
	int err;
	int i;

	sc = device_get_softc(dev);
	sc->dev = dev;

	if (bus_alloc_resources(dev, pl330_spec, sc->res)) {
		device_printf(dev, "could not allocate resources for device\n");
		return (ENXIO);
	}

	/* Setup interrupt handler */
	for (i = 0; i < PL330_NCHANNELS; i++) {
		if (sc->res[i + 1] == NULL)
			break;
		err = bus_setup_intr(dev, sc->res[i + 1], INTR_TYPE_MISC | INTR_MPSAFE,
		    NULL, pl330_intr, sc, sc->ih[i]);
		if (err) {
			device_printf(dev, "Unable to alloc interrupt resource.\n");
			return (ENXIO);
		}
	}

	node = ofw_bus_get_node(dev);
	xref = OF_xref_from_node(node);
	OF_device_register_xref(xref, dev);

	return (0);
}
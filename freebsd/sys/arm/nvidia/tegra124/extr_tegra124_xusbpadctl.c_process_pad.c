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
struct padctl_softc {int /*<<< orphan*/  dev; } ;
struct padctl_pad {int enabled; } ;
typedef  scalar_t__ phandle_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getprop_alloc (scalar_t__,char*,void**) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int /*<<< orphan*/  OF_prop_free (char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ofw_bus_find_child (scalar_t__,char*) ; 
 int /*<<< orphan*/  ofw_bus_node_status_okay (scalar_t__) ; 
 int process_lane (struct padctl_softc*,scalar_t__,struct padctl_pad*) ; 
 struct padctl_pad* search_pad (struct padctl_softc*,char*) ; 

__attribute__((used)) static int
process_pad(struct padctl_softc *sc, phandle_t node)
{
	struct padctl_pad *pad;
	char *name;
	int rv;

	name = NULL;
	rv = OF_getprop_alloc(node, "name", (void **)&name);
	if (rv <= 0) {
		device_printf(sc->dev, "Cannot read pad name.\n");
		return (ENXIO);
	}
	pad = search_pad(sc, name);
	if (pad == NULL) {
		device_printf(sc->dev, "Unknown pad: %s\n", name);
		rv = ENXIO;
		goto end;
	}

	/* Read and process associated lanes. */
	node = ofw_bus_find_child(node, "lanes");
	if (node <= 0) {
		device_printf(sc->dev, "Cannot find regulators subnode\n");
		rv = ENXIO;
		goto end;
	}

	for (node = OF_child(node); node != 0; node = OF_peer(node)) {
		if (!ofw_bus_node_status_okay(node))
			continue;

		rv = process_lane(sc, node, pad);
		if (rv != 0)
			goto end;
	}
	pad->enabled = true;
	rv = 0;
end:
	if (name != NULL)
		OF_prop_free(name);
	return (rv);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ nchannels; int /*<<< orphan*/ * dev; } ;
struct ofw_pwmbus_softc {TYPE_1__ base; } ;
struct TYPE_4__ {scalar_t__ pi_channel; } ;
struct ofw_pwmbus_ivars {TYPE_2__ base; int /*<<< orphan*/  devinfo; } ;
typedef  scalar_t__ phandle_t ;
typedef  scalar_t__ pcell_t ;
typedef  int /*<<< orphan*/ * device_t ;
typedef  int /*<<< orphan*/  chan ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ OF_child (scalar_t__) ; 
 int OF_getencprop (scalar_t__,char*,scalar_t__*,int) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 scalar_t__ PWMBUS_CHANNEL_COUNT (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ofw_pwmbus_ivars* device_get_ivars (int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct ofw_pwmbus_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ ofw_bus_gen_setup_devinfo (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ofw_bus_get_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ofw_pwmbus_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
ofw_pwmbus_attach(device_t dev)
{
	struct ofw_pwmbus_softc *sc;
	struct ofw_pwmbus_ivars *ivars;
	phandle_t node;
	device_t child, parent;
	pcell_t  chan;
	bool any_children;

	sc = device_get_softc(dev);
	sc->base.dev = dev;
	parent = device_get_parent(dev);

	if (PWMBUS_CHANNEL_COUNT(parent, &sc->base.nchannels) != 0 ||
	    sc->base.nchannels == 0) {
		device_printf(dev, "No channels on parent %s\n",
		    device_get_nameunit(parent));
		return (ENXIO);
	}

	/*
	 * Attach the children found in the fdt node of the hardware controller.
	 * Hardware controllers must implement the ofw_bus_get_node method so
	 * that our call to ofw_bus_get_node() gets back the controller's node.
	 */
	any_children = false;
	node = ofw_bus_get_node(dev);
	for (node = OF_child(node); node != 0; node = OF_peer(node)) {
		/*
		 * The child has to have a reg property; its value is the
		 * channel number so range-check it.
		 */
		if (OF_getencprop(node, "reg", &chan, sizeof(chan)) == -1)
			continue;
		if (chan >= sc->base.nchannels)
			continue;

		if ((child = ofw_pwmbus_add_child(dev, 0, NULL, -1)) == NULL)
			continue;

		ivars = device_get_ivars(child);
		ivars->base.pi_channel = chan;

		/* Set up the standard ofw devinfo. */
		if (ofw_bus_gen_setup_devinfo(&ivars->devinfo, node) != 0) {
			device_delete_child(dev, child);
			continue;
		}
		any_children = true;
	}

	/*
	 * If we didn't find any children in the fdt data, add a pwmc(4) child
	 * for each channel, like the base pwmbus does.  The idea is that if
	 * there is any fdt data, then we do exactly what it says and nothing
	 * more, otherwise we just provide generic userland access to all the
	 * pwm channels that exist like the base pwmbus's attach code does.
	 */
	if (!any_children) {
		for (chan = 0; chan < sc->base.nchannels; ++chan) {
			child = ofw_pwmbus_add_child(dev, 0, "pwmc", -1);
			if (child == NULL) {
				device_printf(dev, "failed to add pwmc child "
				    " device for channel %u\n", chan);
				continue;
			}
			ivars = device_get_ivars(child);
			ivars->base.pi_channel = chan;
		}
	}
	bus_enumerate_hinted_children(dev);
	bus_generic_probe(dev);

	return (bus_generic_attach(dev));
}
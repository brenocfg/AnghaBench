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
typedef  scalar_t__ u_int ;
struct pwmbus_softc {scalar_t__ nchannels; int /*<<< orphan*/ * dev; } ;
struct pwmbus_ivars {scalar_t__ pi_channel; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PWMBUS_CHANNEL_COUNT (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ *) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ *) ; 
 struct pwmbus_ivars* device_get_ivars (int /*<<< orphan*/ *) ; 
 scalar_t__ device_get_nameunit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct pwmbus_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/ * pwmbus_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
pwmbus_attach(device_t dev)
{
	struct pwmbus_softc *sc;
	struct pwmbus_ivars *ivars;
	device_t child, parent;
	u_int chan;

	sc = device_get_softc(dev);
	sc->dev = dev;
	parent = device_get_parent(dev);

	if (PWMBUS_CHANNEL_COUNT(parent, &sc->nchannels) != 0 ||
	    sc->nchannels == 0) {
		device_printf(sc->dev, "No channels on parent %s\n",
		    device_get_nameunit(parent));
		return (ENXIO);
	}

	/* Add a pwmc(4) child for each channel. */
	for (chan = 0; chan < sc->nchannels; ++chan) {
		if ((child = pwmbus_add_child(sc->dev, 0, "pwmc", -1)) == NULL) {
			device_printf(dev, "failed to add pwmc child device "
			    "for channel %u\n", chan);
			continue;
		}
		ivars = device_get_ivars(child);
		ivars->pi_channel = chan;
	}

	bus_enumerate_hinted_children(dev);
	bus_generic_probe(dev);

	return (bus_generic_attach(dev));
}
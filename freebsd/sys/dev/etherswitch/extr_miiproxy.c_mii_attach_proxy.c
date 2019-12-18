#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct miiproxy_softc {int /*<<< orphan*/ * mdio; int /*<<< orphan*/ * proxy; int /*<<< orphan*/ * parent; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ bootverbose ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_get_name (int /*<<< orphan*/ *) ; 
 char* device_get_nameunit (int /*<<< orphan*/ *) ; 
 struct miiproxy_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_unit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,...) ; 
 TYPE_1__ miiproxy_driver ; 
 int /*<<< orphan*/  miiproxy_rendezvous_callback ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 scalar_t__ rendezvous_register_proxy (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ resource_string_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 

device_t
mii_attach_proxy(device_t dev)
{
	struct miiproxy_softc *sc;
	int		error;
	const char	*name;
	device_t	miiproxy;

	if (resource_string_value(device_get_name(dev),
	    device_get_unit(dev), "mdio", &name) != 0) {
	    	if (bootverbose)
			printf("mii_attach_proxy: not attaching, no mdio"
			    " device hint for %s\n", device_get_nameunit(dev));
		return (NULL);
	}

	miiproxy = device_add_child(dev, miiproxy_driver.name, -1);
	error = bus_generic_attach(dev);
	if (error != 0) {
		device_printf(dev, "can't attach miiproxy\n");
		return (NULL);
	}
	sc = device_get_softc(miiproxy);
	sc->parent = dev;
	sc->proxy = miiproxy;
	if (rendezvous_register_proxy(miiproxy, name, miiproxy_rendezvous_callback) != 0) {
		device_printf(dev, "can't attach proxy\n");
		return (NULL);
	}
	device_printf(miiproxy, "attached to target %s\n", device_get_nameunit(sc->mdio));
	return (miiproxy);
}
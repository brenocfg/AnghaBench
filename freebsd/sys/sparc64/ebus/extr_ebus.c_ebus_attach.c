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
struct ebus_softc {int /*<<< orphan*/  sc_iinfo; } ;
struct TYPE_2__ {int /*<<< orphan*/  obd_name; } ;
struct ebus_devinfo {TYPE_1__ edi_obdinfo; } ;
typedef  scalar_t__ phandle_t ;
typedef  int /*<<< orphan*/  ofw_isa_intr_t ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 scalar_t__ OF_child (scalar_t__) ; 
 scalar_t__ OF_peer (scalar_t__) ; 
 int bus_generic_attach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_ivars (int /*<<< orphan*/ *,struct ebus_devinfo*) ; 
 int /*<<< orphan*/  ebus_destroy_dinfo (struct ebus_devinfo*) ; 
 struct ebus_devinfo* ebus_setup_dinfo (int /*<<< orphan*/ *,struct ebus_softc*,scalar_t__) ; 
 int /*<<< orphan*/  ofw_bus_setup_iinfo (scalar_t__,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ebus_attach(device_t dev, struct ebus_softc *sc, phandle_t node)
{
	struct ebus_devinfo *edi;
	device_t cdev;

	ofw_bus_setup_iinfo(node, &sc->sc_iinfo, sizeof(ofw_isa_intr_t));

	/*
	 * Now attach our children.
	 */
	for (node = OF_child(node); node > 0; node = OF_peer(node)) {
		if ((edi = ebus_setup_dinfo(dev, sc, node)) == NULL)
			continue;
		if ((cdev = device_add_child(dev, NULL, -1)) == NULL) {
			device_printf(dev, "<%s>: device_add_child failed\n",
			    edi->edi_obdinfo.obd_name);
			ebus_destroy_dinfo(edi);
			continue;
		}
		device_set_ivars(cdev, edi);
	}
	return (bus_generic_attach(dev));
}
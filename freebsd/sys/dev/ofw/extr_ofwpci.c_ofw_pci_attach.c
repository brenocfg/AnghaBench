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
struct ofw_pci_softc {int /*<<< orphan*/  sc_initialized; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct ofw_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int ofw_pci_init (int /*<<< orphan*/ ) ; 

int
ofw_pci_attach(device_t dev)
{
	struct ofw_pci_softc *sc;
	int error;

	sc = device_get_softc(dev);
	if (!sc->sc_initialized) {
		error = ofw_pci_init(dev);
		if (error != 0)
			return (error);
	}

	device_add_child(dev, "pci", -1);
	return (bus_generic_attach(dev));
}
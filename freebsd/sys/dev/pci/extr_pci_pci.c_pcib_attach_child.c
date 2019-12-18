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
struct TYPE_2__ {scalar_t__ sec; } ;
struct pcib_softc {int /*<<< orphan*/  child; TYPE_1__ bus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcib_present (struct pcib_softc*) ; 

int
pcib_attach_child(device_t dev)
{
	struct pcib_softc *sc;

	sc = device_get_softc(dev);
	if (sc->bus.sec == 0) {
		/* no secondary bus; we should have fixed this */
		return(0);
	}

#ifdef PCI_HP
	if (!pcib_present(sc)) {
		/* An empty HotPlug slot, so don't add a PCI bus yet. */
		return (0);
	}
#endif

	sc->child = device_add_child(dev, "pci", -1);
	return (bus_generic_attach(dev));
}
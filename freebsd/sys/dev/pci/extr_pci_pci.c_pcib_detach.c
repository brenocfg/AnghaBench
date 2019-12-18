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
struct pcib_softc {int flags; int /*<<< orphan*/  bus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_HOTPLUG ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 struct pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pcib_detach_hotplug (struct pcib_softc*) ; 
 int /*<<< orphan*/  pcib_free_secbus (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcib_free_windows (struct pcib_softc*) ; 

int
pcib_detach(device_t dev)
{
#if defined(PCI_HP) || defined(NEW_PCIB)
	struct pcib_softc *sc;
#endif
	int error;

#if defined(PCI_HP) || defined(NEW_PCIB)
	sc = device_get_softc(dev);
#endif
	error = bus_generic_detach(dev);
	if (error)
		return (error);
#ifdef PCI_HP
	if (sc->flags & PCIB_HOTPLUG) {
		error = pcib_detach_hotplug(sc);
		if (error)
			return (error);
	}
#endif
	error = device_delete_children(dev);
	if (error)
		return (error);
#ifdef NEW_PCIB
	pcib_free_windows(sc);
#ifdef PCI_RES_BUS
	pcib_free_secbus(dev, &sc->bus);
#endif
#endif
	return (0);
}
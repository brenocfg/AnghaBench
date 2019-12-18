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
struct pcib_softc {int flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_HOTPLUG ; 
 int bus_child_present (int /*<<< orphan*/ ) ; 
 struct pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pcib_hotplug_present (struct pcib_softc*) ; 

int
pcib_child_present(device_t dev, device_t child)
{
#ifdef PCI_HP
	struct pcib_softc *sc = device_get_softc(dev);
	int retval;

	retval = bus_child_present(dev);
	if (retval != 0 && sc->flags & PCIB_HOTPLUG)
		retval = pcib_hotplug_present(sc);
	return (retval);
#else
	return (bus_child_present(dev));
#endif
}
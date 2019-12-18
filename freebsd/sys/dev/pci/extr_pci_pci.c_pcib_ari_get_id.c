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
typedef  int /*<<< orphan*/  uint8_t ;
struct pcib_softc {int flags; } ;
typedef  enum pci_id_type { ____Placeholder_pci_id_type } pci_id_type ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int PCIB_ENABLE_ARI ; 
 int PCIB_GET_ID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,uintptr_t*) ; 
 uintptr_t PCI_ARI_RID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PCI_ID_RID ; 
 uintptr_t PCI_RID (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct pcib_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_function (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_get_slot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pcib_ari_get_id(device_t pcib, device_t dev, enum pci_id_type type,
    uintptr_t *id)
{
	struct pcib_softc *sc;
	device_t bus_dev;
	uint8_t bus, slot, func;

	if (type != PCI_ID_RID) {
		bus_dev = device_get_parent(pcib);
		return (PCIB_GET_ID(device_get_parent(bus_dev), dev, type, id));
	}

	sc = device_get_softc(pcib);

	if (sc->flags & PCIB_ENABLE_ARI) {
		bus = pci_get_bus(dev);
		func = pci_get_function(dev);

		*id = (PCI_ARI_RID(bus, func));
	} else {
		bus = pci_get_bus(dev);
		slot = pci_get_slot(dev);
		func = pci_get_function(dev);

		*id = (PCI_RID(bus, slot, func));
	}

	return (0);
}
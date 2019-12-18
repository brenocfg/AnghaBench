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
struct bhnd_pci_softc {int /*<<< orphan*/  mem_res; int /*<<< orphan*/  mem_rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PCI_LOCK_DESTROY (struct bhnd_pci_softc*) ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bhnd_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 struct bhnd_pci_softc* device_get_softc (int /*<<< orphan*/ ) ; 

int
bhnd_pci_generic_detach(device_t dev)
{
	struct bhnd_pci_softc	*sc;
	int			 error;

	sc = device_get_softc(dev);

	if ((error = bus_generic_detach(dev)))
		return (error);

	bhnd_release_resource(dev, SYS_RES_MEMORY, sc->mem_rid, sc->mem_res);
	
	BHND_PCI_LOCK_DESTROY(sc);

	return (0);
}
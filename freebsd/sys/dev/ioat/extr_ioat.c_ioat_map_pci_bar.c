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
struct ioat_softc {int /*<<< orphan*/ * pci_resource; int /*<<< orphan*/  pci_bus_handle; int /*<<< orphan*/  pci_bus_tag; int /*<<< orphan*/  pci_resource_id; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  PCIR_BAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioat_log_message (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ioat_map_pci_bar(struct ioat_softc *ioat)
{

	ioat->pci_resource_id = PCIR_BAR(0);
	ioat->pci_resource = bus_alloc_resource_any(ioat->device,
	    SYS_RES_MEMORY, &ioat->pci_resource_id, RF_ACTIVE);

	if (ioat->pci_resource == NULL) {
		ioat_log_message(0, "unable to allocate pci resource\n");
		return (ENODEV);
	}

	ioat->pci_bus_tag = rman_get_bustag(ioat->pci_resource);
	ioat->pci_bus_handle = rman_get_bushandle(ioat->pci_resource);
	return (0);
}
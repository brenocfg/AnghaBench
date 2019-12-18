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
typedef  int u_int ;
struct TYPE_2__ {int /*<<< orphan*/  ecam; } ;
struct generic_pcie_acpi_softc {TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_ID_RID ; 
 int acpi_iort_map_pci_msi (int /*<<< orphan*/ ,uintptr_t,int*,int*) ; 
 struct generic_pcie_acpi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int pcib_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,uintptr_t*) ; 

__attribute__((used)) static u_int
generic_pcie_map_id(device_t pci, device_t child, uintptr_t *id)
{
	struct generic_pcie_acpi_softc *sc;
	uintptr_t rid;
	u_int xref, devid;
	int err;

	sc = device_get_softc(pci);
	err = pcib_get_id(pci, child, PCI_ID_RID, &rid);
	if (err != 0)
		return (err);
        err = acpi_iort_map_pci_msi(sc->base.ecam, rid, &xref, &devid);
	if (err == 0)
		*id = devid;
	else
		*id = rid;	/* RID not in IORT, likely FW bug, ignore */
	return (0);
}
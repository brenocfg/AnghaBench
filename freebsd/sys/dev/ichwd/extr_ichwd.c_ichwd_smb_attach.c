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
typedef  int uint32_t ;
struct ichwd_softc {int tco_rid; int gc_rid; int smi_rid; int /*<<< orphan*/ * smi_res; int /*<<< orphan*/ * gc_res; int /*<<< orphan*/ * tco_res; int /*<<< orphan*/  tco_version; int /*<<< orphan*/  ich_version; } ;
struct ichwd_device {int /*<<< orphan*/  tco_version; int /*<<< orphan*/  ich_version; } ;
typedef  int /*<<< orphan*/ * device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  ICH_PMBASE ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 scalar_t__ SMI_BASE ; 
 scalar_t__ SMI_LEN ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,scalar_t__,scalar_t__,scalar_t__,int) ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/ * device_get_parent (int /*<<< orphan*/ *) ; 
 struct ichwd_softc* device_get_softc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ichwd_find_smb_dev (int /*<<< orphan*/ *,struct ichwd_device**) ; 
 int /*<<< orphan*/ * pci_find_dbsf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pci_get_bus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_get_domain (int /*<<< orphan*/ *) ; 
 int pci_read_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ichwd_smb_attach(device_t dev)
{
	struct ichwd_softc *sc;
	struct ichwd_device *id_p;
	device_t isab, pmdev;
	device_t smb;
	uint32_t acpi_base;

	sc = device_get_softc(dev);
	smb = ichwd_find_smb_dev(device_get_parent(dev), &id_p);
	if (smb == NULL)
		return (ENXIO);

	sc->ich_version = id_p->ich_version;
	sc->tco_version = id_p->tco_version;

	/* Allocate TCO control I/O register space. */
	sc->tco_rid = 0;
	sc->tco_res = bus_alloc_resource_any(dev, SYS_RES_IOPORT, &sc->tco_rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->tco_res == NULL) {
		device_printf(dev, "unable to reserve TCO registers\n");
		return (ENXIO);
	}

	/*
	 * Allocate General Control I/O register in PCH
	 * Private Configuration Space (PCR).
	 */
	sc->gc_rid = 1;
	sc->gc_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->gc_rid,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->gc_res == NULL) {
		device_printf(dev, "unable to reserve hidden P2SB registers\n");
		return (ENXIO);
	}

	/* Get ACPI base address. */
	isab = device_get_parent(device_get_parent(dev));
	pmdev = pci_find_dbsf(pci_get_domain(isab), pci_get_bus(isab), 31, 2);
	if (pmdev == NULL) {
		device_printf(dev, "unable to find Power Management device\n");
		return (ENXIO);
	}
	acpi_base = pci_read_config(pmdev, ICH_PMBASE, 4) & 0xffffff00;
	if (acpi_base == 0) {
		device_printf(dev, "ACPI base address is not set\n");
		return (ENXIO);
	}

	/* Allocate SMI control I/O register space. */
	sc->smi_rid = 2;
	sc->smi_res = bus_alloc_resource(dev, SYS_RES_IOPORT, &sc->smi_rid,
	    acpi_base + SMI_BASE, acpi_base + SMI_BASE + SMI_LEN - 1, SMI_LEN,
	    RF_ACTIVE | RF_SHAREABLE);
	if (sc->smi_res == NULL) {
		device_printf(dev, "unable to reserve SMI registers\n");
		return (ENXIO);
	}

	return (0);
}
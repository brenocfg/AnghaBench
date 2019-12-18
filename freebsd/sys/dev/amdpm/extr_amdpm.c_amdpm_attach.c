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
typedef  int u_char ;
struct amdpm_softc {int /*<<< orphan*/  smbus; int /*<<< orphan*/  lock; int /*<<< orphan*/ * res; int /*<<< orphan*/  rid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AMDPCI_GEN_CONFIG_PM ; 
 int /*<<< orphan*/  AMDPCI_PMBASE ; 
 int AMDPCI_PMIOEN ; 
 scalar_t__ AMDPM_VENDORID_AMD ; 
 int EINVAL ; 
 int ENXIO ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  NFPCI_PMBASE ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  amdpm_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct amdpm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_get_vendor (int /*<<< orphan*/ ) ; 
 int pci_read_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pci_write_config (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int
amdpm_attach(device_t dev)
{
	struct amdpm_softc *amdpm_sc = device_get_softc(dev);
	u_char val_b;
	
	/* Enable I/O block access */
	val_b = pci_read_config(dev, AMDPCI_GEN_CONFIG_PM, 1);
	pci_write_config(dev, AMDPCI_GEN_CONFIG_PM, val_b | AMDPCI_PMIOEN, 1);

	/* Allocate I/O space */
	if (pci_get_vendor(dev) == AMDPM_VENDORID_AMD)
		amdpm_sc->rid = AMDPCI_PMBASE;
	else
		amdpm_sc->rid = NFPCI_PMBASE;
	amdpm_sc->res = bus_alloc_resource_any(dev, SYS_RES_IOPORT,
		&amdpm_sc->rid, RF_ACTIVE);
	
	if (amdpm_sc->res == NULL) {
		device_printf(dev, "could not map i/o space\n");
		return (ENXIO);
	}	     

	mtx_init(&amdpm_sc->lock, device_get_nameunit(dev), "amdpm", MTX_DEF);

	/* Allocate a new smbus device */
	amdpm_sc->smbus = device_add_child(dev, "smbus", -1);
	if (!amdpm_sc->smbus) {
		amdpm_detach(dev);
		return (EINVAL);
	}

	bus_generic_attach(dev);

	return (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int platform_attached; int /*<<< orphan*/ * intr_res; scalar_t__ intr_rid; int /*<<< orphan*/ * regs_res; scalar_t__ regs_rid; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ ig4iic_softc_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 scalar_t__ PCIR_BAR (int /*<<< orphan*/ ) ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ig4iic_attach (TYPE_1__*) ; 
 int /*<<< orphan*/  ig4iic_pci_detach (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int
ig4iic_pci_attach(device_t dev)
{
	ig4iic_softc_t *sc = device_get_softc(dev);
	int error;

	sc->dev = dev;
	sc->regs_rid = PCIR_BAR(0);
	sc->regs_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
					  &sc->regs_rid, RF_ACTIVE);
	if (sc->regs_res == NULL) {
		device_printf(dev, "unable to map registers\n");
		ig4iic_pci_detach(dev);
		return (ENXIO);
	}
	sc->intr_rid = 0;
	if (pci_alloc_msi(dev, &sc->intr_rid)) {
		device_printf(dev, "Using MSI\n");
	}
	sc->intr_res = bus_alloc_resource_any(dev, SYS_RES_IRQ,
					  &sc->intr_rid, RF_SHAREABLE | RF_ACTIVE);
	if (sc->intr_res == NULL) {
		device_printf(dev, "unable to map interrupt\n");
		ig4iic_pci_detach(dev);
		return (ENXIO);
	}
	sc->platform_attached = 1;

	error = ig4iic_attach(sc);
	if (error)
		ig4iic_pci_detach(dev);

	return (error);
}
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
struct pvscsi_softc {int use_msi_or_msix; int irq_id; int /*<<< orphan*/  dev; int /*<<< orphan*/  irq_handler; int /*<<< orphan*/ * irq_res; } ;

/* Variables and functions */
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_CAM ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct pvscsi_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ pci_alloc_msi (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_alloc_msix (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ pci_msi_count (int /*<<< orphan*/ ) ; 
 scalar_t__ pci_msix_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_free_interrupts (struct pvscsi_softc*) ; 
 int pvscsi_get_tunable (struct pvscsi_softc*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_intr ; 
 int /*<<< orphan*/  pvscsi_use_msi ; 
 int /*<<< orphan*/  pvscsi_use_msix ; 

__attribute__((used)) static int
pvscsi_setup_interrupts(struct pvscsi_softc *sc)
{
	int error;
	int flags;
	int use_msix;
	int use_msi;
	int count;

	sc->use_msi_or_msix = 0;

	use_msix = pvscsi_get_tunable(sc, "use_msix", pvscsi_use_msix);
	use_msi = pvscsi_get_tunable(sc, "use_msi", pvscsi_use_msi);

	if (use_msix && pci_msix_count(sc->dev) > 0) {
		count = 1;
		if (pci_alloc_msix(sc->dev, &count) == 0 && count == 1) {
			sc->use_msi_or_msix = 1;
			device_printf(sc->dev, "Interrupt: MSI-X\n");
		} else {
			pci_release_msi(sc->dev);
		}
	}

	if (sc->use_msi_or_msix == 0 && use_msi && pci_msi_count(sc->dev) > 0) {
		count = 1;
		if (pci_alloc_msi(sc->dev, &count) == 0 && count == 1) {
			sc->use_msi_or_msix = 1;
			device_printf(sc->dev, "Interrupt: MSI\n");
		} else {
			pci_release_msi(sc->dev);
		}
	}

	flags = RF_ACTIVE;
	if (sc->use_msi_or_msix) {
		sc->irq_id = 1;
	} else {
		device_printf(sc->dev, "Interrupt: INT\n");
		sc->irq_id = 0;
		flags |= RF_SHAREABLE;
	}

	sc->irq_res = bus_alloc_resource_any(sc->dev, SYS_RES_IRQ, &sc->irq_id,
	    flags);
	if (sc->irq_res == NULL) {
		device_printf(sc->dev, "IRQ allocation failed\n");
		if (sc->use_msi_or_msix) {
			pci_release_msi(sc->dev);
		}
		return (ENXIO);
	}

	error = bus_setup_intr(sc->dev, sc->irq_res,
	    INTR_TYPE_CAM | INTR_MPSAFE, NULL, pvscsi_intr, sc,
	    &sc->irq_handler);
	if (error) {
		device_printf(sc->dev, "IRQ handler setup failed\n");
		pvscsi_free_interrupts(sc);
		return (error);
	}

	return (0);
}
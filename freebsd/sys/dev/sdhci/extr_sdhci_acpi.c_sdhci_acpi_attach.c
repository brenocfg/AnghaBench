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
typedef  int u_int ;
struct TYPE_4__ {int quirks; } ;
struct sdhci_acpi_softc {TYPE_1__ slot; int /*<<< orphan*/  intrhand; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * mem_res; struct sdhci_acpi_device const* acpi_dev; } ;
struct sdhci_acpi_device {int quirks; int uid; int /*<<< orphan*/  hid; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES ; 
 int /*<<< orphan*/  SDHCI_CAPABILITIES2 ; 
 int SDHCI_QUIRK_DATA_TIMEOUT_1MHZ ; 
 int SDHCI_QUIRK_MMC_DDR52 ; 
 int SDHCI_READ_4 (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sdhci_acpi_softc*,int /*<<< orphan*/ *) ; 
 struct sdhci_acpi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdhci_acpi_detach (int /*<<< orphan*/ ) ; 
 struct sdhci_acpi_device* sdhci_acpi_find_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_acpi_intr ; 
 int sdhci_init_slot (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sdhci_quirk_clear ; 
 int sdhci_quirk_set ; 
 int /*<<< orphan*/  sdhci_start_slot (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
sdhci_acpi_attach(device_t dev)
{
	struct sdhci_acpi_softc *sc = device_get_softc(dev);
	int rid, err;
	u_int quirks;
	const struct sdhci_acpi_device *acpi_dev;

	acpi_dev = sdhci_acpi_find_device(dev);
	if (acpi_dev == NULL)
		return (ENXIO);

	sc->acpi_dev = acpi_dev;
	quirks = acpi_dev->quirks;

	/* Allocate IRQ. */
	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
		RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "can't allocate IRQ\n");
		return (ENOMEM);
	}

	rid = 0;
	sc->mem_res = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
	    &rid, RF_ACTIVE);
	if (sc->mem_res == NULL) {
		device_printf(dev, "can't allocate memory resource for slot\n");
		sdhci_acpi_detach(dev);
		return (ENOMEM);
	}

	/*
	 * Intel Bay Trail and Braswell eMMC controllers share the same IDs,
	 * but while with these former DDR52 is affected by the VLI54 erratum,
	 * these latter require the timeout clock to be hardcoded to 1 MHz.
	 */
	if (strcmp(acpi_dev->hid, "80860F14") == 0 && acpi_dev->uid == 1 &&
	    SDHCI_READ_4(dev, &sc->slot, SDHCI_CAPABILITIES) == 0x446cc8b2 &&
	    SDHCI_READ_4(dev, &sc->slot, SDHCI_CAPABILITIES2) == 0x00000807)
		quirks |= SDHCI_QUIRK_MMC_DDR52 | SDHCI_QUIRK_DATA_TIMEOUT_1MHZ;
	quirks &= ~sdhci_quirk_clear;
	quirks |= sdhci_quirk_set;
	sc->slot.quirks = quirks;

	err = sdhci_init_slot(dev, &sc->slot, 0);
	if (err) {
		device_printf(dev, "failed to init slot\n");
		sdhci_acpi_detach(dev);
		return (err);
	}

	/* Activate the interrupt */
	err = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, sdhci_acpi_intr, sc, &sc->intrhand);
	if (err) {
		device_printf(dev, "can't setup IRQ\n");
		sdhci_acpi_detach(dev);
		return (err);
	}

	/* Process cards detection. */
	sdhci_start_slot(&sc->slot);

	return (0);
}
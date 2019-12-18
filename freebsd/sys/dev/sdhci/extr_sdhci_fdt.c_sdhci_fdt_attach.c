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
struct sdhci_slot {int /*<<< orphan*/  sdma_boundary; int /*<<< orphan*/  max_clk; int /*<<< orphan*/  caps; int /*<<< orphan*/  quirks; } ;
struct sdhci_fdt_softc {int num_slots; struct sdhci_slot* slots; int /*<<< orphan*/  intrhand; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/  sdma_boundary; int /*<<< orphan*/  max_clk; int /*<<< orphan*/  caps; int /*<<< orphan*/  quirks; int /*<<< orphan*/ ** mem_res; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {scalar_t__ ocd_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 scalar_t__ SDHCI_FDT_RK3399 ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 void* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct sdhci_fdt_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compat_data ; 
 struct sdhci_fdt_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_1__* ofw_bus_search_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_fdt_intr ; 
 int sdhci_init_rk3399 (int /*<<< orphan*/ ) ; 
 scalar_t__ sdhci_init_slot (int /*<<< orphan*/ ,struct sdhci_slot*,int) ; 
 int /*<<< orphan*/  sdhci_start_slot (struct sdhci_slot*) ; 

__attribute__((used)) static int
sdhci_fdt_attach(device_t dev)
{
	struct sdhci_fdt_softc *sc = device_get_softc(dev);
	struct sdhci_slot *slot;
	int err, slots, rid, i;

	sc->dev = dev;

	/* Allocate IRQ. */
	rid = 0;
	sc->irq_res = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid,
	    RF_ACTIVE);
	if (sc->irq_res == NULL) {
		device_printf(dev, "Can't allocate IRQ\n");
		return (ENOMEM);
	}

#ifdef EXT_RESOURCES
	if (ofw_bus_search_compatible(dev, compat_data)->ocd_data ==
	    SDHCI_FDT_RK3399) {
		/* Initialize SDHCI */
		err = sdhci_init_rk3399(dev);
		if (err != 0) {
			device_printf(dev, "Cannot init RK3399 SDHCI\n");
			return (err);
		}
	}
#endif

	/* Scan all slots. */
	slots = sc->num_slots;	/* number of slots determined in probe(). */
	sc->num_slots = 0;
	for (i = 0; i < slots; i++) {
		slot = &sc->slots[sc->num_slots];

		/* Allocate memory. */
		rid = 0;
		sc->mem_res[i] = bus_alloc_resource_any(dev, SYS_RES_MEMORY,
							&rid, RF_ACTIVE);
		if (sc->mem_res[i] == NULL) {
			device_printf(dev,
			    "Can't allocate memory for slot %d\n", i);
			continue;
		}

		slot->quirks = sc->quirks;
		slot->caps = sc->caps;
		slot->max_clk = sc->max_clk;
		slot->sdma_boundary = sc->sdma_boundary;

		if (sdhci_init_slot(dev, slot, i) != 0)
			continue;

		sc->num_slots++;
	}
	device_printf(dev, "%d slot(s) allocated\n", sc->num_slots);

	/* Activate the interrupt */
	err = bus_setup_intr(dev, sc->irq_res, INTR_TYPE_MISC | INTR_MPSAFE,
	    NULL, sdhci_fdt_intr, sc, &sc->intrhand);
	if (err) {
		device_printf(dev, "Cannot setup IRQ\n");
		return (err);
	}

	/* Process cards detection. */
	for (i = 0; i < sc->num_slots; i++)
		sdhci_start_slot(&sc->slots[i]);

	return (0);
}
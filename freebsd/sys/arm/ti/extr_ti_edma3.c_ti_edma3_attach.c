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
typedef  int /*<<< orphan*/  uint32_t ;
struct ti_edma3_softc {int /*<<< orphan*/ * ih_cookie; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_2__ {int /*<<< orphan*/  description; int /*<<< orphan*/ * handler; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDMA_TPCC_CLK ; 
 int ENXIO ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  TI_EDMA3CC_PID ; 
 int TI_EDMA3_NUM_IRQS ; 
 int bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ti_edma3_softc*,int /*<<< orphan*/ *) ; 
 struct ti_edma3_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ti_edma3_cc_rd_4 (int /*<<< orphan*/ ) ; 
 TYPE_1__* ti_edma3_intrs ; 
 int /*<<< orphan*/  ti_edma3_irq_spec ; 
 int /*<<< orphan*/  ti_edma3_mem_spec ; 
 struct ti_edma3_softc* ti_edma3_sc ; 
 int /*<<< orphan*/  ti_prcm_clk_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_edma3_attach(device_t dev)
{
	struct ti_edma3_softc *sc = device_get_softc(dev);
	uint32_t reg;
	int err;
	int i;

	if (ti_edma3_sc)
		return (ENXIO);

	ti_edma3_sc = sc;
	sc->sc_dev = dev;

	/* Request the memory resources */
	err = bus_alloc_resources(dev, ti_edma3_mem_spec, sc->mem_res);
	if (err) {
		device_printf(dev, "Error: could not allocate mem resources\n");
		return (ENXIO);
	}

	/* Request the IRQ resources */
	err = bus_alloc_resources(dev, ti_edma3_irq_spec, sc->irq_res);
	if (err) {
		device_printf(dev, "Error: could not allocate irq resources\n");
		return (ENXIO);
	}

	/* Enable Channel Controller */
	ti_prcm_clk_enable(EDMA_TPCC_CLK);

	reg = ti_edma3_cc_rd_4(TI_EDMA3CC_PID);

	device_printf(dev, "EDMA revision %08x\n", reg);


	/* Attach interrupt handlers */
	for (i = 0; i < TI_EDMA3_NUM_IRQS; ++i) {
		err = bus_setup_intr(dev, sc->irq_res[i], INTR_TYPE_MISC |
		    INTR_MPSAFE, NULL, *ti_edma3_intrs[i].handler,
		    sc, &sc->ih_cookie[i]);
		if (err) {
			device_printf(dev, "could not setup %s\n",
			    ti_edma3_intrs[i].description);
			return (err);
		}
	}

	return (0);
}
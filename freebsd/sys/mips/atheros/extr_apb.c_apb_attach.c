#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* rm_descr; void* rm_type; } ;
struct apb_softc {int /*<<< orphan*/ * sc_intr_counter; int /*<<< orphan*/  sc_misc_ih; int /*<<< orphan*/ * sc_misc_irq; TYPE_1__ apb_irq_rman; TYPE_1__ apb_mem_rman; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t APB_INTR_PMC ; 
 scalar_t__ APB_IRQ_BASE ; 
 scalar_t__ APB_IRQ_END ; 
 scalar_t__ AR71XX_APB_BASE ; 
 scalar_t__ AR71XX_APB_SIZE ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 void* RMAN_ARRAY ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  apb_filter ; 
 int /*<<< orphan*/  apb_unmask_irq (void*) ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct apb_softc*,int /*<<< orphan*/ *) ; 
 struct apb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_set_desc (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mips_intrcnt_create (char*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 scalar_t__ rman_init (TYPE_1__*) ; 
 scalar_t__ rman_manage_region (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
apb_attach(device_t dev)
{
	struct apb_softc *sc = device_get_softc(dev);
	int rid = 0;

	device_set_desc(dev, "APB Bus bridge");

	sc->apb_mem_rman.rm_type = RMAN_ARRAY;
	sc->apb_mem_rman.rm_descr = "APB memory window";

	if (rman_init(&sc->apb_mem_rman) != 0 ||
	    rman_manage_region(&sc->apb_mem_rman, 
			AR71XX_APB_BASE, 
			AR71XX_APB_BASE + AR71XX_APB_SIZE - 1) != 0)
		panic("apb_attach: failed to set up memory rman");

	sc->apb_irq_rman.rm_type = RMAN_ARRAY;
	sc->apb_irq_rman.rm_descr = "APB IRQ";

	if (rman_init(&sc->apb_irq_rman) != 0 ||
	    rman_manage_region(&sc->apb_irq_rman, 
			APB_IRQ_BASE, APB_IRQ_END) != 0)
		panic("apb_attach: failed to set up IRQ rman");

	if ((sc->sc_misc_irq = bus_alloc_resource_any(dev, SYS_RES_IRQ, &rid, 
	    RF_SHAREABLE | RF_ACTIVE)) == NULL) {
		device_printf(dev, "unable to allocate IRQ resource\n");
		return (ENXIO);
	}

	if ((bus_setup_intr(dev, sc->sc_misc_irq, INTR_TYPE_MISC, 
	    apb_filter, NULL, sc, &sc->sc_misc_ih))) {
		device_printf(dev,
		    "WARNING: unable to register interrupt handler\n");
		return (ENXIO);
	}

	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);
	bus_generic_attach(dev);

	/*
	 * Unmask performance counter IRQ
	 */
	apb_unmask_irq((void*)APB_INTR_PMC);
	sc->sc_intr_counter[APB_INTR_PMC] = mips_intrcnt_create("apb irq5: pmc");

	return (0);
}
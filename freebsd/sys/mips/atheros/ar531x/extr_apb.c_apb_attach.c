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
struct apb_softc {int /*<<< orphan*/  sc_misc_ih; int /*<<< orphan*/ * sc_misc_irq; TYPE_1__ apb_irq_rman; TYPE_1__ apb_mem_rman; int /*<<< orphan*/  apb_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ APB_IRQ_BASE ; 
 scalar_t__ APB_IRQ_END ; 
 scalar_t__ AR5312_APB_BASE ; 
 scalar_t__ AR5312_APB_SIZE ; 
 int AR5312_IRQ_MISC ; 
 scalar_t__ AR5312_SYSREG_BASE ; 
 scalar_t__ AR5312_SYSREG_MISC_INTMASK ; 
 scalar_t__ AR5315_APB_BASE ; 
 scalar_t__ AR5315_APB_SIZE ; 
 int AR5315_CPU_IRQ_MISC ; 
 scalar_t__ AR5315_SYSREG_BASE ; 
 scalar_t__ AR5315_SYSREG_MISC_INTMASK ; 
 scalar_t__ AR531X_SOC_AR5315 ; 
 int /*<<< orphan*/  ATH_WRITE_REG (scalar_t__,int /*<<< orphan*/ ) ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int RF_ACTIVE ; 
 int RF_SHAREABLE ; 
 void* RMAN_ARRAY ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  apb_filter ; 
 scalar_t__ apb_pic_register_isrcs (struct apb_softc*) ; 
 scalar_t__ ar531x_soc ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  bus_enumerate_hinted_children (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 scalar_t__ bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct apb_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpu_establish_hardintr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct apb_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct apb_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * intr_pic_register (int /*<<< orphan*/ ,intptr_t) ; 
 int /*<<< orphan*/  panic (char*) ; 
 intptr_t pic_xref (int /*<<< orphan*/ ) ; 
 scalar_t__ rman_init (TYPE_1__*) ; 
 scalar_t__ rman_manage_region (TYPE_1__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
apb_attach(device_t dev)
{
	struct apb_softc *sc = device_get_softc(dev);
#ifdef INTRNG
	intptr_t xref = pic_xref(dev);
	int miscirq;
#else
	int rid = 0;
#endif

	sc->apb_dev = dev;

	sc->apb_mem_rman.rm_type = RMAN_ARRAY;
	sc->apb_mem_rman.rm_descr = "APB memory window";

	if(ar531x_soc >= AR531X_SOC_AR5315) {
		if (rman_init(&sc->apb_mem_rman) != 0 ||
		    rman_manage_region(&sc->apb_mem_rman, 
			AR5315_APB_BASE, 
			AR5315_APB_BASE + AR5315_APB_SIZE - 1) != 0)
			panic("apb_attach: failed to set up memory rman");
	} else {
		if (rman_init(&sc->apb_mem_rman) != 0 ||
		    rman_manage_region(&sc->apb_mem_rman, 
			AR5312_APB_BASE, 
			AR5312_APB_BASE + AR5312_APB_SIZE - 1) != 0)
			panic("apb_attach: failed to set up memory rman");
	}

	sc->apb_irq_rman.rm_type = RMAN_ARRAY;
	sc->apb_irq_rman.rm_descr = "APB IRQ";

	if (rman_init(&sc->apb_irq_rman) != 0 ||
	    rman_manage_region(&sc->apb_irq_rman, 
			APB_IRQ_BASE, APB_IRQ_END) != 0)
		panic("apb_attach: failed to set up IRQ rman");

#ifndef INTRNG
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
#else
	/* Register the interrupts */
	if (apb_pic_register_isrcs(sc) != 0) {
		device_printf(dev, "could not register PIC ISRCs\n");
		return (ENXIO);
	}

	/*
	 * Now, when everything is initialized, it's right time to
	 * register interrupt controller to interrupt framefork.
	 */
	if (intr_pic_register(dev, xref) == NULL) {
		device_printf(dev, "could not register PIC\n");
		return (ENXIO);
	}

	if(ar531x_soc >= AR531X_SOC_AR5315) {
		miscirq = AR5315_CPU_IRQ_MISC;
	} else {
		miscirq = AR5312_IRQ_MISC;
	}
	cpu_establish_hardintr("aric", apb_filter, NULL, sc, miscirq,
	    INTR_TYPE_MISC, NULL);
#endif

	/* mask all misc interrupt */
	if(ar531x_soc >= AR531X_SOC_AR5315) {
		ATH_WRITE_REG(AR5315_SYSREG_BASE
			+ AR5315_SYSREG_MISC_INTMASK, 0);
	} else {
		ATH_WRITE_REG(AR5312_SYSREG_BASE
			+ AR5312_SYSREG_MISC_INTMASK, 0);
	}

	bus_generic_probe(dev);
	bus_enumerate_hinted_children(dev);
	bus_generic_attach(dev);

	return (0);
}
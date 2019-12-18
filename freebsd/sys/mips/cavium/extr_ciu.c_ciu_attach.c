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
struct TYPE_3__ {char* rm_descr; int /*<<< orphan*/  rm_type; } ;
struct ciu_softc {TYPE_1__ irq_rman; int /*<<< orphan*/ * ciu_irq; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int CIU_IRQ_EN0_BEGIN ; 
 unsigned int CIU_IRQ_EN0_COUNT ; 
 int CIU_IRQ_EN1_BEGIN ; 
 unsigned int CIU_IRQ_EN1_COUNT ; 
 int /*<<< orphan*/  CIU_IRQ_EN1_END ; 
 int CIU_IRQ_HARD ; 
 int ENXIO ; 
 int /*<<< orphan*/  INTR_TYPE_MISC ; 
 int /*<<< orphan*/  MAXCOMLEN ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  RMAN_ARRAY ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/ * bus_alloc_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_probe (int /*<<< orphan*/ ) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ciu_softc*,int /*<<< orphan*/ *) ; 
 void** ciu_en0_intrcnt ; 
 void** ciu_en1_intrcnt ; 
 int /*<<< orphan*/  ciu_intr ; 
 struct ciu_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 void* mips_intrcnt_create (char*) ; 
 int rman_init (TYPE_1__*) ; 
 int rman_manage_region (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

__attribute__((used)) static int
ciu_attach(device_t dev)
{
	char name[MAXCOMLEN + 1];
	struct ciu_softc *sc;
	unsigned i;
	int error;
	int rid;

	sc = device_get_softc(dev);

	rid = 0;
	sc->ciu_irq = bus_alloc_resource(dev, SYS_RES_IRQ, &rid, CIU_IRQ_HARD,
					 CIU_IRQ_HARD, 1, RF_ACTIVE);
	if (sc->ciu_irq == NULL) {
		device_printf(dev, "could not allocate irq%d\n", CIU_IRQ_HARD);
		return (ENXIO);
	}

	error = bus_setup_intr(dev, sc->ciu_irq, INTR_TYPE_MISC, ciu_intr,
			       NULL, sc, NULL);
	if (error != 0) {
		device_printf(dev, "bus_setup_intr failed: %d\n", error);
		return (error);
	}

	sc->irq_rman.rm_type = RMAN_ARRAY;
	sc->irq_rman.rm_descr = "CIU IRQ";
	
	error = rman_init(&sc->irq_rman);
	if (error != 0)
		return (error);

	/*
	 * We have two contiguous IRQ regions, use a single rman.
	 */
	error = rman_manage_region(&sc->irq_rman, CIU_IRQ_EN0_BEGIN,
				   CIU_IRQ_EN1_END);
	if (error != 0)
		return (error);

	for (i = 0; i < CIU_IRQ_EN0_COUNT; i++) {
		snprintf(name, sizeof name, "int%d:", i + CIU_IRQ_EN0_BEGIN);
		ciu_en0_intrcnt[i] = mips_intrcnt_create(name);
	}

	for (i = 0; i < CIU_IRQ_EN1_COUNT; i++) {
		snprintf(name, sizeof name, "int%d:", i + CIU_IRQ_EN1_BEGIN);
		ciu_en1_intrcnt[i] = mips_intrcnt_create(name);
	}

	bus_generic_probe(dev);
	bus_generic_attach(dev);

	return (0);
}
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
typedef  scalar_t__ u_int ;
struct resource {int dummy; } ;
struct bcm_mips_softc {int /*<<< orphan*/  dev; } ;
struct bcm_mips_cpuirq {int irq_rid; scalar_t__ refs; int /*<<< orphan*/ * isrc_solo; void* irq_cookie; struct resource* irq_res; scalar_t__ mips_irq; struct bcm_mips_softc* sc; } ;
typedef  int /*<<< orphan*/  driver_filter_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_MIPS_LOCK (struct bcm_mips_softc*) ; 
 int /*<<< orphan*/  BCM_MIPS_UNLOCK (struct bcm_mips_softc*) ; 
 int EINVAL ; 
 int ENXIO ; 
 int INTR_EXCL ; 
 int INTR_MPSAFE ; 
 int INTR_TYPE_MISC ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ NHARD_IRQS ; 
 scalar_t__ NSOFT_IRQS ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 struct resource* bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct resource*) ; 
 int bus_set_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int) ; 
 int bus_setup_intr (int /*<<< orphan*/ ,struct resource*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct bcm_mips_cpuirq*,void**) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  printf (char*,int) ; 

__attribute__((used)) static int
bcm_mips_init_cpuirq(struct bcm_mips_softc *sc, struct bcm_mips_cpuirq *cpuirq,
    int rid, u_int irq, driver_filter_t filter)
{
	struct resource	*res;
	void		*cookie;
	u_int		 irq_real;
	int		 error;

	/* Must fall within MIPS HW IRQ range */
	if (irq >= NHARD_IRQS)
		return (EINVAL);

	/* HW IRQs are numbered relative to SW IRQs */
	irq_real = irq + NSOFT_IRQS;

	/* Try to assign and allocate the resource */
	BCM_MIPS_LOCK(sc);

	KASSERT(cpuirq->sc == NULL, ("cpuirq already initialized"));

	error = bus_set_resource(sc->dev, SYS_RES_IRQ, rid, irq_real, 1);
	if (error) {
		BCM_MIPS_UNLOCK(sc);
		device_printf(sc->dev, "failed to assign interrupt %u: "
		    "%d\n", irq, error);
		return (error);
	}

	res = bus_alloc_resource_any(sc->dev, SYS_RES_IRQ, &rid, RF_ACTIVE);
	if (res == NULL) {
		BCM_MIPS_UNLOCK(sc);
		device_printf(sc->dev, "failed to allocate interrupt "
			"%u resource\n", irq);
		bus_delete_resource(sc->dev, SYS_RES_IRQ, rid);
		return (ENXIO);
	}

	error = bus_setup_intr(sc->dev, res,
	    INTR_TYPE_MISC | INTR_MPSAFE | INTR_EXCL, filter, NULL, cpuirq,
	    &cookie);
	if (error) {
		BCM_MIPS_UNLOCK(sc);

		printf("failed to setup internal interrupt handler: %d\n",
		    error);

		bus_release_resource(sc->dev, SYS_RES_IRQ, rid, res);
		bus_delete_resource(sc->dev, SYS_RES_IRQ, rid);

		return (error);
	}

	/* Initialize CPU IRQ state */
	cpuirq->sc = sc;
	cpuirq->mips_irq = irq;
	cpuirq->irq_rid = rid;
	cpuirq->irq_res = res;
	cpuirq->irq_cookie = cookie;
	cpuirq->isrc_solo = NULL;
	cpuirq->refs = 0;

	BCM_MIPS_UNLOCK(sc);
	return (0);
}
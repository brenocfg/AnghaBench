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
struct bcm_mips_softc {int /*<<< orphan*/  dev; } ;
struct bcm_mips_cpuirq {scalar_t__ refs; int irq_rid; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ * irq_cookie; int /*<<< orphan*/ * sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_MIPS_LOCK (struct bcm_mips_softc*) ; 
 int /*<<< orphan*/  BCM_MIPS_UNLOCK (struct bcm_mips_softc*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  bus_delete_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bcm_mips_fini_cpuirq(struct bcm_mips_softc *sc, struct bcm_mips_cpuirq *cpuirq)
{
	int error;

	BCM_MIPS_LOCK(sc);

	if (cpuirq->sc == NULL) {
		KASSERT(cpuirq->irq_res == NULL, ("leaking cpuirq resource"));

		BCM_MIPS_UNLOCK(sc);
		return (0);	/* not initialized */
	}

	if (cpuirq->refs != 0) {
		BCM_MIPS_UNLOCK(sc);
		return (EBUSY);
	}

	if (cpuirq->irq_cookie != NULL) {
		KASSERT(cpuirq->irq_res != NULL, ("resource missing"));

		error = bus_teardown_intr(sc->dev, cpuirq->irq_res,
			cpuirq->irq_cookie);
		if (error) {
			BCM_MIPS_UNLOCK(sc);
			return (error);
		}

		cpuirq->irq_cookie = NULL;
	}

	if (cpuirq->irq_res != NULL) {
		bus_release_resource(sc->dev, SYS_RES_IRQ, cpuirq->irq_rid,
		    cpuirq->irq_res);
		cpuirq->irq_res = NULL;
	}

	if (cpuirq->irq_rid != -1) {
		bus_delete_resource(sc->dev, SYS_RES_IRQ, cpuirq->irq_rid);
		cpuirq->irq_rid = -1;
	}

	BCM_MIPS_UNLOCK(sc);

	return (0);
}
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
struct bcm_mips_softc {int dummy; } ;
struct bcm_mips_cpuirq {int irq_rid; scalar_t__ refs; int /*<<< orphan*/ * isrc_solo; int /*<<< orphan*/ * irq_cookie; int /*<<< orphan*/ * irq_res; scalar_t__ mips_irq; struct bcm_mips_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_MIPS_LOCK (struct bcm_mips_softc*) ; 
 int /*<<< orphan*/  BCM_MIPS_UNLOCK (struct bcm_mips_softc*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
bcm_mips_init_cpuirq_unavail(struct bcm_mips_softc *sc,
    struct bcm_mips_cpuirq *cpuirq)
{
	BCM_MIPS_LOCK(sc);

	KASSERT(cpuirq->sc == NULL, ("cpuirq already initialized"));
	cpuirq->sc = sc;
	cpuirq->mips_irq = 0;
	cpuirq->irq_rid = -1;
	cpuirq->irq_res = NULL;
	cpuirq->irq_cookie = NULL;
	cpuirq->isrc_solo = NULL;
	cpuirq->refs = 0;

	BCM_MIPS_UNLOCK(sc);

	return (0);
}
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
struct resource {int dummy; } ;
struct bcm_mips_softc {int dummy; } ;
struct bcm_mips_irqsrc {scalar_t__ refs; struct bcm_mips_cpuirq* cpuirq; } ;
struct bcm_mips_cpuirq {int refs; struct bcm_mips_irqsrc* isrc_solo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_MIPS_LOCK_ASSERT (struct bcm_mips_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 

__attribute__((used)) static int
bcm_mips_release_cpu_intr(struct bcm_mips_softc *sc,
    struct bcm_mips_irqsrc *isrc, struct resource *res)
{
	struct bcm_mips_cpuirq *cpuirq;

	BCM_MIPS_LOCK_ASSERT(sc, MA_OWNED);

	/* Decrement the refcount */
	KASSERT(isrc->refs > 0, ("isrc over-release"));
	isrc->refs--;

	/* Nothing else to do if the isrc is still actively referenced */
	if (isrc->refs > 0)
		return (0);

	/* Otherwise, we need to release our CPU IRQ reference */
	cpuirq = isrc->cpuirq;
	isrc->cpuirq = NULL;

	KASSERT(cpuirq != NULL, ("no assigned IRQ"));
	KASSERT(cpuirq->refs > 0, ("cpuirq over-release"));

	/* Disable single isrc dispatch path */
	if (cpuirq->refs == 1 && cpuirq->isrc_solo != NULL) {
		KASSERT(cpuirq->isrc_solo == isrc, ("invalid solo isrc"));
		cpuirq->isrc_solo = NULL;
	}

	cpuirq->refs--;

	return (0);
}
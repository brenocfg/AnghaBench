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
typedef  int uint32_t ;
struct bcm_lintc_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  isrc_cpu; } ;
struct bcm_lintc_irqsrc {TYPE_1__ bli_isrc; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_LINTC_LOCK (struct bcm_lintc_softc*) ; 
 int BCM_LINTC_PIRR_IRQ_EN_CORE (int) ; 
 int /*<<< orphan*/  BCM_LINTC_PMU_ROUTING_CLR_REG ; 
 int /*<<< orphan*/  BCM_LINTC_UNLOCK (struct bcm_lintc_softc*) ; 
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcm_lintc_write_4 (struct bcm_lintc_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
bcm_lintc_pmu_mask(struct bcm_lintc_softc *sc, struct bcm_lintc_irqsrc *bli)
{
	cpuset_t *cpus;
	uint32_t cpu, mask;

	mask = 0;
	cpus = &bli->bli_isrc.isrc_cpu;

	BCM_LINTC_LOCK(sc);
	for (cpu = 0; cpu < 4; cpu++)
		if (CPU_ISSET(cpu, cpus))
			mask |= BCM_LINTC_PIRR_IRQ_EN_CORE(cpu);
	/* Write-clear register. */
	bcm_lintc_write_4(sc, BCM_LINTC_PMU_ROUTING_CLR_REG, mask);
	BCM_LINTC_UNLOCK(sc);
}
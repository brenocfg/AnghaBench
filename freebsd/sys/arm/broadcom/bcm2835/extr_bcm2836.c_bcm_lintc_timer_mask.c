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
struct bcm_lintc_irqsrc {int /*<<< orphan*/  bli_mask; TYPE_1__ bli_isrc; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_LINTC_LOCK (struct bcm_lintc_softc*) ; 
 int /*<<< orphan*/  BCM_LINTC_TIMER_CFG_REG (int) ; 
 int /*<<< orphan*/  BCM_LINTC_UNLOCK (struct bcm_lintc_softc*) ; 
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bcm_lintc_rwreg_clr (struct bcm_lintc_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcm_lintc_timer_mask(struct bcm_lintc_softc *sc, struct bcm_lintc_irqsrc *bli)
{
	cpuset_t *cpus;
	uint32_t cpu;

	cpus = &bli->bli_isrc.isrc_cpu;

	BCM_LINTC_LOCK(sc);
	for (cpu = 0; cpu < 4; cpu++)
		if (CPU_ISSET(cpu, cpus))
			bcm_lintc_rwreg_clr(sc, BCM_LINTC_TIMER_CFG_REG(cpu),
			    bli->bli_mask);
	BCM_LINTC_UNLOCK(sc);
}
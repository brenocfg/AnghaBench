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
typedef  char uint8_t ;
struct pmu_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMU_POWER_OFF ; 
 int /*<<< orphan*/  PMU_RESET_CPU ; 
 int RB_HALT ; 
 int /*<<< orphan*/  pmu_send (struct pmu_softc*,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pmu_shutdown(void *xsc, int howto)
{
	struct pmu_softc *sc = xsc;
	uint8_t cmd[] = {'M', 'A', 'T', 'T'};
	
	if (howto & RB_HALT)
		pmu_send(sc, PMU_POWER_OFF, 4, cmd, 0, NULL);
	else
		pmu_send(sc, PMU_RESET_CPU, 0, NULL, 0, NULL);

	for (;;);
}
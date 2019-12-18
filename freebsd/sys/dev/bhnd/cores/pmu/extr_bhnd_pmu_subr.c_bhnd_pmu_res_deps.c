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
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct bhnd_pmu_softc {int dummy; } ;

/* Variables and functions */
 int BHND_PMURES_BIT (scalar_t__) ; 
 int BHND_PMU_READ_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ BHND_PMU_RESNUM_MAX ; 
 int /*<<< orphan*/  BHND_PMU_RES_DEP_MASK ; 
 int /*<<< orphan*/  BHND_PMU_RES_TABLE_SEL ; 
 int /*<<< orphan*/  BHND_PMU_WRITE_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static uint32_t
bhnd_pmu_res_deps(struct bhnd_pmu_softc *sc, uint32_t rsrcs, bool all)
{
	uint32_t deps;

	deps = 0;
	for (uint8_t i = 0; i <= BHND_PMU_RESNUM_MAX; i++) {
		if (!(rsrcs & BHND_PMURES_BIT(i)))
			continue;

		BHND_PMU_WRITE_4(sc, BHND_PMU_RES_TABLE_SEL, i);
		deps |= BHND_PMU_READ_4(sc, BHND_PMU_RES_DEP_MASK);
	}

	/* None found? */
	if (deps == 0)
		return (0);

	/* Recurse dependencies */
	if (all)
		deps |= bhnd_pmu_res_deps(sc, deps, true);

	return (deps);
}
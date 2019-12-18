#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct bhnd_pmu_query {int dummy; } ;
struct TYPE_4__ {int fref; scalar_t__ xf; } ;
typedef  TYPE_1__ pmu1_xtaltab0_t ;

/* Variables and functions */
 int /*<<< orphan*/  BHND_PMU_CTRL ; 
 int /*<<< orphan*/  BHND_PMU_CTRL_XTALFREQ ; 
 scalar_t__ BHND_PMU_GET_BITS (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ BHND_PMU_READ_4 (struct bhnd_pmu_query*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMU_LOG (struct bhnd_pmu_query*,char*) ; 
 TYPE_1__* bhnd_pmu1_xtaldef0 (struct bhnd_pmu_query*) ; 
 TYPE_1__* bhnd_pmu1_xtaltab0 (struct bhnd_pmu_query*) ; 

__attribute__((used)) static uint32_t
bhnd_pmu1_alpclk0(struct bhnd_pmu_query *sc)
{
	const pmu1_xtaltab0_t	*xt;
	uint32_t		 xf;

	/* Find the frequency in the table */
	xf = BHND_PMU_READ_4(sc, BHND_PMU_CTRL);
	xf = BHND_PMU_GET_BITS(xf, BHND_PMU_CTRL_XTALFREQ);

	for (xt = bhnd_pmu1_xtaltab0(sc); xt != NULL && xt->fref != 0; xt++) {
		if (xt->xf == xf)
			break;
	}

	/* Could not find it so assign a default value */
	if (xt == NULL || xt->fref == 0)
		xt = bhnd_pmu1_xtaldef0(sc);

	if (xt == NULL || xt->fref == 0) {
		PMU_LOG(sc, "no matching ALP/XTAL frequency found\n");
		return (0);
	}

	return (xt->fref * 1000);
}
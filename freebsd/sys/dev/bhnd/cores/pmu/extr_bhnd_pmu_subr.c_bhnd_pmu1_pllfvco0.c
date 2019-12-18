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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int chip_id; } ;
struct bhnd_pmu_query {TYPE_1__ cid; } ;

/* Variables and functions */
#define  BHND_CHIPID_BCM4319 131 
#define  BHND_CHIPID_BCM4329 130 
#define  BHND_CHIPID_BCM4330 129 
#define  BHND_CHIPID_BCM4336 128 
 int /*<<< orphan*/  FVCO_1440 ; 
 int /*<<< orphan*/  FVCO_880 ; 
 int /*<<< orphan*/  FVCO_960 ; 
 int /*<<< orphan*/  PMU_CST4330_SDIOD_CHIPMODE (struct bhnd_pmu_query*) ; 
 int /*<<< orphan*/  PMU_DEBUG (struct bhnd_pmu_query*,char*,int) ; 

__attribute__((used)) static uint32_t
bhnd_pmu1_pllfvco0(struct bhnd_pmu_query *sc)
{
	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4329:
		return (FVCO_880);
	case BHND_CHIPID_BCM4319:
		return (FVCO_1440);
	case BHND_CHIPID_BCM4336:
		return (FVCO_960);
	case BHND_CHIPID_BCM4330:
		if (PMU_CST4330_SDIOD_CHIPMODE(sc))
			return (FVCO_960);
		else
			return (FVCO_1440);
	default:
		PMU_DEBUG(sc, "bhnd_pmu1_pllfvco0: Unknown chipid %#hx\n",
		    sc->cid.chip_id);
		return (0);
	}
}
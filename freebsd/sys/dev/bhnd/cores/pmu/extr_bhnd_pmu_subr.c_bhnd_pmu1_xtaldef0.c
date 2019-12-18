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
struct TYPE_2__ {int chip_id; } ;
struct bhnd_pmu_query {TYPE_1__ cid; } ;
typedef  int /*<<< orphan*/  pmu1_xtaltab0_t ;

/* Variables and functions */
#define  BHND_CHIPID_BCM4315 133 
#define  BHND_CHIPID_BCM4319 132 
#define  BHND_CHIPID_BCM4325 131 
#define  BHND_CHIPID_BCM4329 130 
#define  BHND_CHIPID_BCM4330 129 
#define  BHND_CHIPID_BCM4336 128 
 size_t PMU1_XTALTAB0_1440_30000K ; 
 size_t PMU1_XTALTAB0_1440_37400K ; 
 size_t PMU1_XTALTAB0_1760_26000K ; 
 size_t PMU1_XTALTAB0_880_26000K ; 
 size_t PMU1_XTALTAB0_880_38400K ; 
 size_t PMU1_XTALTAB0_960_26000K ; 
 size_t PMU1_XTALTAB0_960_37400K ; 
 int /*<<< orphan*/  PMU_CST4330_SDIOD_CHIPMODE (struct bhnd_pmu_query*) ; 
 int /*<<< orphan*/  PMU_DEBUG (struct bhnd_pmu_query*,char*,int) ; 
 int /*<<< orphan*/  const* pmu1_xtaltab0_1440 ; 
 int /*<<< orphan*/  const* pmu1_xtaltab0_1760 ; 
 int /*<<< orphan*/  const* pmu1_xtaltab0_880 ; 
 int /*<<< orphan*/  const* pmu1_xtaltab0_880_4329 ; 
 int /*<<< orphan*/  const* pmu1_xtaltab0_960 ; 

__attribute__((used)) static const pmu1_xtaltab0_t *
bhnd_pmu1_xtaldef0(struct bhnd_pmu_query *sc)
{
	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4315:
		/* Default to 26000Khz */
		return (&pmu1_xtaltab0_1760[PMU1_XTALTAB0_1760_26000K]);
	case BHND_CHIPID_BCM4319:
		/* Default to 30000Khz */
		return (&pmu1_xtaltab0_1440[PMU1_XTALTAB0_1440_30000K]);
	case BHND_CHIPID_BCM4325:
		/* Default to 26000Khz */
		return (&pmu1_xtaltab0_880[PMU1_XTALTAB0_880_26000K]);
	case BHND_CHIPID_BCM4329:
		/* Default to 38400Khz */
		return (&pmu1_xtaltab0_880_4329[PMU1_XTALTAB0_880_38400K]);
	case BHND_CHIPID_BCM4336:
		/* Default to 26000Khz */
		return (&pmu1_xtaltab0_960[PMU1_XTALTAB0_960_26000K]);
	case BHND_CHIPID_BCM4330:
		/* Default to 37400Khz */
		if (PMU_CST4330_SDIOD_CHIPMODE(sc))
			return (&pmu1_xtaltab0_960[PMU1_XTALTAB0_960_37400K]);
		else
			return (&pmu1_xtaltab0_1440[PMU1_XTALTAB0_1440_37400K]);
	default:
		PMU_DEBUG(sc, "bhnd_pmu1_xtaldef0: Unknown chipid %#hx\n",
		    sc->cid.chip_id);
		return (NULL);
	}
}
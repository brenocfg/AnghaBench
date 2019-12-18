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
 int /*<<< orphan*/  PMU_CST4330_SDIOD_CHIPMODE (struct bhnd_pmu_query*) ; 
 int /*<<< orphan*/  PMU_DEBUG (struct bhnd_pmu_query*,char*,int) ; 
 int /*<<< orphan*/  const* pmu1_xtaltab0_1440 ; 
 int /*<<< orphan*/  const* pmu1_xtaltab0_1760 ; 
 int /*<<< orphan*/  const* pmu1_xtaltab0_880 ; 
 int /*<<< orphan*/  const* pmu1_xtaltab0_880_4329 ; 
 int /*<<< orphan*/  const* pmu1_xtaltab0_960 ; 

__attribute__((used)) static const pmu1_xtaltab0_t *
bhnd_pmu1_xtaltab0(struct bhnd_pmu_query *sc)
{
	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4315:
		return (pmu1_xtaltab0_1760);
	case BHND_CHIPID_BCM4319:
		return (pmu1_xtaltab0_1440);
	case BHND_CHIPID_BCM4325:
		return (pmu1_xtaltab0_880);
	case BHND_CHIPID_BCM4329:
		return (pmu1_xtaltab0_880_4329);
	case BHND_CHIPID_BCM4336:
		return (pmu1_xtaltab0_960);
	case BHND_CHIPID_BCM4330:
		if (PMU_CST4330_SDIOD_CHIPMODE(sc))
			return (pmu1_xtaltab0_960);
		else
			return (pmu1_xtaltab0_1440);
	default:
		PMU_DEBUG(sc, "bhnd_pmu1_xtaltab0: Unknown chipid %#hx\n",
		    sc->cid.chip_id);
		return (NULL);
	}
}
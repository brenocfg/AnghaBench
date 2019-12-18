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
struct TYPE_2__ {int chip_id; } ;
struct bhnd_pmu_softc {TYPE_1__ cid; } ;

/* Variables and functions */
#define  BHND_CHIPID_BCM4315 137 
#define  BHND_CHIPID_BCM4319 136 
#define  BHND_CHIPID_BCM4322 135 
#define  BHND_CHIPID_BCM43221 134 
#define  BHND_CHIPID_BCM43231 133 
#define  BHND_CHIPID_BCM4325 132 
#define  BHND_CHIPID_BCM4329 131 
#define  BHND_CHIPID_BCM4330 130 
#define  BHND_CHIPID_BCM4336 129 
#define  BHND_CHIPID_BCM4342 128 
 int /*<<< orphan*/  BHND_PMU_AND_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int) ; 
 int BHND_PMU_MAX_TRANSITION_DLY ; 
 int /*<<< orphan*/  BHND_PMU_MIN_RES_MASK ; 
 int /*<<< orphan*/  BHND_PMU_OR_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ,int) ; 
 int BHND_PMU_READ_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_RES_STATE ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
 int PMURES_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMU_DEBUG (struct bhnd_pmu_softc*,char*,int) ; 
 int /*<<< orphan*/  PMU_LOG (struct bhnd_pmu_softc*,char*) ; 
 int /*<<< orphan*/  RES4315_OTP_PU ; 
 int /*<<< orphan*/  RES4319_OTP_PU ; 
 int /*<<< orphan*/  RES4322_OTP_PU ; 
 int /*<<< orphan*/  RES4325_OTP_PU ; 
 int /*<<< orphan*/  RES4329_OTP_PU ; 
 int /*<<< orphan*/  RES4330_OTP_PU ; 
 int /*<<< orphan*/  RES4336_OTP_PU ; 
 int bhnd_pmu_res_deps (struct bhnd_pmu_softc*,int,int) ; 
 int bhnd_pmu_res_masks (struct bhnd_pmu_softc*,int*,int /*<<< orphan*/ *) ; 

int
bhnd_pmu_otp_power(struct bhnd_pmu_softc *sc, bool on)
{
	uint32_t	deps;
	uint32_t	min_mask;
	uint32_t	rsrcs;
	int		error;

	/* Determine rsrcs to turn on/off OTP power */
	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4322:
	case BHND_CHIPID_BCM43221:
	case BHND_CHIPID_BCM43231:
	case BHND_CHIPID_BCM4342:
		rsrcs = PMURES_BIT(RES4322_OTP_PU);
		break;
	case BHND_CHIPID_BCM4315:
		rsrcs = PMURES_BIT(RES4315_OTP_PU);
		break;
	case BHND_CHIPID_BCM4325:
		rsrcs = PMURES_BIT(RES4325_OTP_PU);
		break;
	case BHND_CHIPID_BCM4329:
		rsrcs = PMURES_BIT(RES4329_OTP_PU);
		break;
	case BHND_CHIPID_BCM4319:
		rsrcs = PMURES_BIT(RES4319_OTP_PU);
		break;
	case BHND_CHIPID_BCM4336:
		rsrcs = PMURES_BIT(RES4336_OTP_PU);
		break;
	case BHND_CHIPID_BCM4330:
		rsrcs = PMURES_BIT(RES4330_OTP_PU);
		break;
	default:
		/* Not required? */
		return (0);
	}

	/* Fetch all dependencies */
	deps = bhnd_pmu_res_deps(sc, rsrcs, true);

	/* Exclude the minimum resource set */
	if ((error = bhnd_pmu_res_masks(sc, &min_mask, NULL)))
		return (error);

	deps &= ~min_mask;

	/* Turn on/off the power */
	if (on) {
		uint32_t state;

		PMU_DEBUG(sc, "Adding rsrc 0x%x to min_res_mask\n",
		    rsrcs | deps);
		BHND_PMU_OR_4(sc, BHND_PMU_MIN_RES_MASK, (rsrcs|deps));

		/* Wait for all resources to become available */
		for (int i = 0; i < BHND_PMU_MAX_TRANSITION_DLY; i += 10) {	
			state = BHND_PMU_READ_4(sc, BHND_PMU_RES_STATE);
			if ((state & rsrcs) == rsrcs)
				break;

			DELAY(10);
		}

		if ((state & rsrcs) != rsrcs) {
			PMU_LOG(sc, "timeout waiting for OTP resource "
			    "enable\n");
			return (ENXIO);
		}
	} else {
		PMU_DEBUG(sc, "Removing rsrc 0x%x from min_res_mask\n",
		    rsrcs | deps);
		BHND_PMU_AND_4(sc, BHND_PMU_MIN_RES_MASK, ~(rsrcs|deps));
	}

	return (0);
}
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
#define  BHND_CHIPID_BCM4319 137 
#define  BHND_CHIPID_BCM43224 136 
#define  BHND_CHIPID_BCM43225 135 
#define  BHND_CHIPID_BCM43235 134 
#define  BHND_CHIPID_BCM43236 133 
#define  BHND_CHIPID_BCM43238 132 
#define  BHND_CHIPID_BCM4329 131 
#define  BHND_CHIPID_BCM4330 130 
#define  BHND_CHIPID_BCM4336 129 
#define  BHND_CHIPID_BCM43421 128 
 int BHND_PMU_READ_4 (struct bhnd_pmu_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BHND_PMU_RES_STATE ; 
 int PMURES_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RES4319_OTP_PU ; 
 int /*<<< orphan*/  RES4329_OTP_PU ; 
 int /*<<< orphan*/  RES4330_OTP_PU ; 
 int /*<<< orphan*/  RES4336_OTP_PU ; 

bool
bhnd_pmu_is_otp_powered(struct bhnd_pmu_softc *sc)
{
	uint32_t			 otp_res;

	/* Determine per-chip OTP resource */
	switch (sc->cid.chip_id) {
	case BHND_CHIPID_BCM4329:
		otp_res = PMURES_BIT(RES4329_OTP_PU);
		break;
	case BHND_CHIPID_BCM4319:
		otp_res = PMURES_BIT(RES4319_OTP_PU);
		break;
	case BHND_CHIPID_BCM4336:
		otp_res = PMURES_BIT(RES4336_OTP_PU);
		break;
	case BHND_CHIPID_BCM4330:
		otp_res = PMURES_BIT(RES4330_OTP_PU);
		break;

	/* These chips don't use PMU bit to power up/down OTP. OTP always on.
	 * Use OTP_INIT command to reset/refresh state.
	 */
	case BHND_CHIPID_BCM43224:
	case BHND_CHIPID_BCM43225:
	case BHND_CHIPID_BCM43421:
	case BHND_CHIPID_BCM43236:
	case BHND_CHIPID_BCM43235:
	case BHND_CHIPID_BCM43238:
		return (true);

	default:
		return (true);
	}

	/* Check resource state */
	if ((BHND_PMU_READ_4(sc, BHND_PMU_RES_STATE) & otp_res) == 0)
		return (false);

	return (true);
}
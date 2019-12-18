#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ath_hal {int dummy; } ;
typedef  int int16_t ;
struct TYPE_4__ {TYPE_1__* ah_curchan; } ;
struct TYPE_3__ {int /*<<< orphan*/  ic_freq; } ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_PHY (int) ; 
 int /*<<< orphan*/  AR_PHY_ACTIVE ; 
 int /*<<< orphan*/  AR_PHY_AGC_CONTROL ; 
 int AR_PHY_AGC_CONTROL_NF ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  HAL_DEBUG_NFCAL ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int ar5211GetNoiseFloor (struct ath_hal*) ; 

int16_t
ar5211RunNoiseFloor(struct ath_hal *ah, uint8_t runTime, int16_t startingNF)
{
	int i, searchTime;

	HALASSERT(runTime <= 7);

	/* Setup  noise floor run time and starting value */
	OS_REG_WRITE(ah, AR_PHY(25),
		(OS_REG_READ(ah, AR_PHY(25)) & ~0xFFF) |
			 ((runTime << 9) & 0xE00) | (startingNF & 0x1FF));
	/* Calibrate the noise floor */
	OS_REG_WRITE(ah, AR_PHY_AGC_CONTROL,
		OS_REG_READ(ah, AR_PHY_AGC_CONTROL) | AR_PHY_AGC_CONTROL_NF);

	/* Compute the required amount of searchTime needed to finish NF */
	if (runTime == 0) {
		/* 8 search windows * 6.4us each */
		searchTime = 8  * 7;
	} else {
		/* 512 * runtime search windows * 6.4us each */
		searchTime = (runTime * 512)  * 7;
	}

	/*
	 * Do not read noise floor until it has been updated
	 *
	 * As a guesstimate - we may only get 1/60th the time on
	 * the air to see search windows  in a heavily congested
	 * network (40 us every 2400 us of time)
	 */
	for (i = 0; i < 60; i++) {
		if ((OS_REG_READ(ah, AR_PHY_AGC_CONTROL) & AR_PHY_AGC_CONTROL_NF) == 0)
			break;
		OS_DELAY(searchTime);
	}
	if (i >= 60) {
		HALDEBUG(ah, HAL_DEBUG_NFCAL,
		    "NF with runTime %d failed to end on channel %d\n",
		    runTime, AH_PRIVATE(ah)->ah_curchan->ic_freq);
		HALDEBUG(ah, HAL_DEBUG_NFCAL,
		    "  PHY NF Reg state:	 0x%x\n",
		    OS_REG_READ(ah, AR_PHY_AGC_CONTROL));
		HALDEBUG(ah, HAL_DEBUG_NFCAL,
		    "  PHY Active Reg state: 0x%x\n",
		    OS_REG_READ(ah, AR_PHY_ACTIVE));
		return 0;
	}

	return ar5211GetNoiseFloor(ah);
}
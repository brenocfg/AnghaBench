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
typedef  int uint16_t ;
struct ath_hal_5212 {size_t* ah_ratesArray; int /*<<< orphan*/ * ah_pcdacTable; } ;
struct ath_hal {scalar_t__ ah_magic; } ;
typedef  int /*<<< orphan*/  ratesIndex ;
typedef  size_t int32_t ;
typedef  size_t int16_t ;
struct TYPE_4__ {TYPE_1__* ah_eeprom; } ;
struct TYPE_3__ {size_t ee_cckOfdmGainDelta; } ;
typedef  TYPE_1__ HAL_EEPROM ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 scalar_t__ AR5212_MAGIC ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int N (size_t*) ; 
 int /*<<< orphan*/  OS_MEMCPY (size_t*,size_t*,int) ; 
 size_t PWR_TABLE_SIZE ; 

__attribute__((used)) static void
ar5212CorrectGainDelta(struct ath_hal *ah, int twiceOfdmCckDelta)
{
#define	N(_a)	(sizeof(_a) / sizeof(_a[0]))
	struct ath_hal_5212 *ahp = AH5212(ah);
	const HAL_EEPROM *ee = AH_PRIVATE(ah)->ah_eeprom;
	int16_t ratesIndex[N(ahp->ah_ratesArray)];
	uint16_t ii, jj, iter;
	int32_t cckIndex;
	int16_t gainDeltaAdjust;

	HALASSERT(ah->ah_magic == AR5212_MAGIC);

	gainDeltaAdjust = ee->ee_cckOfdmGainDelta;

	/* make a local copy of desired powers as initial indices */
	OS_MEMCPY(ratesIndex, ahp->ah_ratesArray, sizeof(ratesIndex));

	/* fix only the CCK indices */
	for (ii = 8; ii < 15; ii++) {
		/* apply a gain_delta correction of -15 for CCK */
		ratesIndex[ii] -= gainDeltaAdjust;

		/* Now check for contention with all ofdm target powers */
		jj = 0;
		iter = 0;
		/* indicates not all ofdm rates checked forcontention yet */
		while (jj < 16) {
			if (ratesIndex[ii] < 0)
				ratesIndex[ii] = 0;
			if (jj == 8) {		/* skip CCK rates */
				jj = 15;
				continue;
			}
			if (ratesIndex[ii] == ahp->ah_ratesArray[jj]) {
				if (ahp->ah_ratesArray[jj] == 0)
					ratesIndex[ii]++;
				else if (iter > 50) {
					/*
					 * To avoid pathological case of of
					 * dm target powers 0 and 0.5dBm
					 */
					ratesIndex[ii]++;
				} else
					ratesIndex[ii]--;
				/* check with all rates again */
				jj = 0;
				iter++;
			} else
				jj++;
		}
		if (ratesIndex[ii] >= PWR_TABLE_SIZE)
			ratesIndex[ii] = PWR_TABLE_SIZE -1;
		cckIndex = ahp->ah_ratesArray[ii] - twiceOfdmCckDelta;
		if (cckIndex < 0)
			cckIndex = 0;

		/* 
		 * Validate that the indexes for the powv are not
		 * out of bounds.
		 */
		HALASSERT(cckIndex < PWR_TABLE_SIZE);
		HALASSERT(ratesIndex[ii] < PWR_TABLE_SIZE);
		ahp->ah_pcdacTable[ratesIndex[ii]] =
			ahp->ah_pcdacTable[cckIndex];
	}
	/* Override rate per power table with new values */
	for (ii = 8; ii < 15; ii++)
		ahp->ah_ratesArray[ii] = ratesIndex[ii];
#undef N
}
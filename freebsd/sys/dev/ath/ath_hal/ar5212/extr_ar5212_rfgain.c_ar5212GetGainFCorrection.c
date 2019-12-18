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
typedef  int uint32_t ;
struct TYPE_4__ {TYPE_1__* currStep; } ;
struct ath_hal_5212 {TYPE_2__ ah_gainValues; } ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int* paramVal; } ;
typedef  TYPE_2__ GAIN_VALUES ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_RADX112_REV2 (struct ath_hal*) ; 
 int /*<<< orphan*/  ar5212GetRfBank (struct ath_hal*,int) ; 
 int ar5212GetRfField (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
ar5212GetGainFCorrection(struct ath_hal *ah)
{
	struct ath_hal_5212 *ahp = AH5212(ah);
	uint32_t correction;

	HALASSERT(IS_RADX112_REV2(ah));

	correction = 0;
	if (ar5212GetRfField(ar5212GetRfBank(ah, 7), 1, 36, 0) == 1) {
		const GAIN_VALUES *gv = &ahp->ah_gainValues;
		uint32_t mixGain = gv->currStep->paramVal[0];
		uint32_t gainStep =
			ar5212GetRfField(ar5212GetRfBank(ah, 7), 4, 32, 0);
		switch (mixGain) {
		case 0 :
			correction = 0;
			break;
		case 1 :
			correction = gainStep;
			break;
		case 2 :
			correction = 2 * gainStep - 5;
			break;
		case 3 :
			correction = 2 * gainStep;
			break;
		}
	}
	return correction;
}
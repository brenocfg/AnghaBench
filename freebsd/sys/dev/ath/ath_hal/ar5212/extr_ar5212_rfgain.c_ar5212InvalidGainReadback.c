#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int hiTrig; int loTrig; int currGain; } ;
typedef  int HAL_BOOL ;
typedef  TYPE_1__ GAIN_VALUES ;

/* Variables and functions */
 int DYN_ADJ_LO_MARGIN ; 
 int DYN_ADJ_UP_MARGIN ; 
 scalar_t__ IS_RAD5112_ANY (struct ath_hal*) ; 
 int /*<<< orphan*/  ar5212GetRfBank (struct ath_hal*,int) ; 
 int ar5212GetRfField (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HAL_BOOL
ar5212InvalidGainReadback(struct ath_hal *ah, GAIN_VALUES *gv)
{
	uint32_t gStep, g, mixOvr;
	uint32_t L1, L2, L3, L4;

	if (IS_RAD5112_ANY(ah)) {
		mixOvr = ar5212GetRfField(ar5212GetRfBank(ah, 7), 1, 36, 0);
		L1 = 0;
		L2 = 107;
		L3 = 0;
		L4 = 107;
		if (mixOvr == 1) {
			L2 = 83;
			L4 = 83;
			gv->hiTrig = 55;
		}
	} else {
		gStep = ar5212GetRfField(ar5212GetRfBank(ah, 7), 6, 37, 0);

		L1 = 0;
		L2 = (gStep == 0x3f) ? 50 : gStep + 4;
		L3 = (gStep != 0x3f) ? 0x40 : L1;
		L4 = L3 + 50;

		gv->loTrig = L1 + (gStep == 0x3f ? DYN_ADJ_LO_MARGIN : 0);
		/* never adjust if != 0x3f */
		gv->hiTrig = L4 - (gStep == 0x3f ? DYN_ADJ_UP_MARGIN : -5);
	}
	g = gv->currGain;

	return !((g >= L1 && g<= L2) || (g >= L3 && g <= L4));
}
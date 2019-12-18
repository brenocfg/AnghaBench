#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t currStepNum; int loTrig; int hiTrig; void* active; int /*<<< orphan*/ * currStep; } ;
struct ath_hal_5212 {TYPE_1__ ah_gainValues; } ;
struct ath_hal {int dummy; } ;
struct TYPE_6__ {size_t defaultStepNum; int /*<<< orphan*/ * optStep; } ;
struct TYPE_5__ {size_t defaultStepNum; int /*<<< orphan*/ * optStep; } ;
typedef  TYPE_1__ GAIN_VALUES ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 void* AH_TRUE ; 
 scalar_t__ IS_RAD5112_ANY (struct ath_hal*) ; 
 TYPE_3__ gainLadder ; 
 TYPE_2__ gainLadder5112 ; 

void
ar5212InitializeGainValues(struct ath_hal *ah)
{
	struct ath_hal_5212 *ahp = AH5212(ah);
	GAIN_VALUES *gv = &ahp->ah_gainValues;

	/* initialize gain optimization values */
	if (IS_RAD5112_ANY(ah)) {
		gv->currStepNum = gainLadder5112.defaultStepNum;
		gv->currStep =
			&gainLadder5112.optStep[gainLadder5112.defaultStepNum];
		gv->active = AH_TRUE;
		gv->loTrig = 20;
		gv->hiTrig = 85;
	} else {
		gv->currStepNum = gainLadder.defaultStepNum;
		gv->currStep = &gainLadder.optStep[gainLadder.defaultStepNum];
		gv->active = AH_TRUE;
		gv->loTrig = 20;
		gv->hiTrig = 35;
	}
}
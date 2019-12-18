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
struct TYPE_3__ {size_t currStepNum; int loTrig; int hiTrig; int /*<<< orphan*/  active; int /*<<< orphan*/ * currStep; } ;
struct ath_hal_5211 {TYPE_1__ ah_gainValues; } ;
struct ath_hal {int dummy; } ;
struct TYPE_4__ {size_t defaultStepNum; int /*<<< orphan*/ * optStep; } ;
typedef  TYPE_1__ GAIN_VALUES ;

/* Variables and functions */
 struct ath_hal_5211* AH5211 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 TYPE_2__ gainLadder ; 

void
ar5211InitializeGainValues(struct ath_hal *ah)
{
	struct ath_hal_5211 *ahp = AH5211(ah);
	GAIN_VALUES *gv = &ahp->ah_gainValues;

	/* initialize gain optimization values */
	gv->currStepNum = gainLadder.defaultStepNum;
	gv->currStep = &gainLadder.optStep[gainLadder.defaultStepNum];
	gv->active = AH_TRUE;
	gv->loTrig = 20;
	gv->hiTrig = 35;
}
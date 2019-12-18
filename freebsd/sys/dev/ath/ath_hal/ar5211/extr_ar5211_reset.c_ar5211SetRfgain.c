#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
struct TYPE_11__ {TYPE_3__* ah_eeprom; } ;
struct TYPE_10__ {TYPE_2__* currStep; int /*<<< orphan*/  active; } ;
struct TYPE_7__ {int /*<<< orphan*/  gSel; int /*<<< orphan*/  pd84; int /*<<< orphan*/  pd90; int /*<<< orphan*/  clip; } ;
struct TYPE_9__ {TYPE_1__ ee_cornerCal; } ;
struct TYPE_8__ {int /*<<< orphan*/ * paramVal; } ;
typedef  TYPE_3__ HAL_EEPROM ;
typedef  TYPE_4__ GAIN_VALUES ;

/* Variables and functions */
 TYPE_6__* AH_PRIVATE (struct ath_hal*) ; 

__attribute__((used)) static void
ar5211SetRfgain(struct ath_hal *ah, const GAIN_VALUES *gv)
{
	HAL_EEPROM *ee = AH_PRIVATE(ah)->ah_eeprom;

	if (!gv->active)
		return;
	ee->ee_cornerCal.clip = gv->currStep->paramVal[0]; /* bb_tx_clip */
	ee->ee_cornerCal.pd90 = gv->currStep->paramVal[1]; /* rf_pwd_90 */
	ee->ee_cornerCal.pd84 = gv->currStep->paramVal[2]; /* rf_pwd_84 */
	ee->ee_cornerCal.gSel = gv->currStep->paramVal[3]; /* rf_rfgainsel */
}
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
typedef  int /*<<< orphan*/  uint16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ah_eeprom; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** ee_spurChans; } ;
typedef  TYPE_1__ HAL_EEPROM ;
typedef  size_t HAL_BOOL ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int AR_EEPROM_MODAL_SPURS ; 
 int /*<<< orphan*/  HALASSERT (int) ; 

__attribute__((used)) static uint16_t
legacyEepromGetSpurChan(struct ath_hal *ah, int ix, HAL_BOOL is2GHz)
{
	HAL_EEPROM *ee = AH_PRIVATE(ah)->ah_eeprom;

	HALASSERT(0 <= ix && ix < AR_EEPROM_MODAL_SPURS);
	return ee->ee_spurChans[ix][is2GHz];
}
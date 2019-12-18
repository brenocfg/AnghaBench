#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_10__ {TYPE_4__* ah_eeprom; } ;
struct TYPE_7__ {TYPE_1__* spurChans; } ;
struct TYPE_8__ {TYPE_2__ modalHeader; } ;
struct TYPE_9__ {TYPE_3__ ee_base; } ;
struct TYPE_6__ {int /*<<< orphan*/  spurChan; } ;
typedef  TYPE_4__ HAL_EEPROM_v4k ;
typedef  int HAL_BOOL ;

/* Variables and functions */
 TYPE_5__* AH_PRIVATE (struct ath_hal*) ; 
 int AR5416_EEPROM_MODAL_SPURS ; 
 int /*<<< orphan*/  HALASSERT (int) ; 

__attribute__((used)) static uint16_t 
v4kEepromGetSpurChan(struct ath_hal *ah, int ix, HAL_BOOL is2GHz)
{ 
	HAL_EEPROM_v4k *ee = AH_PRIVATE(ah)->ah_eeprom;
	
	HALASSERT(0 <= ix && ix <  AR5416_EEPROM_MODAL_SPURS);
	HALASSERT(is2GHz);
	return ee->ee_base.modalHeader.spurChans[ix].spurChan;
}
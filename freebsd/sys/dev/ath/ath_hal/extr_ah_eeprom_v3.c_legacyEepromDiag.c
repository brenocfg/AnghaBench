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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_6__ {TYPE_1__* ah_eeprom; } ;
struct TYPE_5__ {int numChannels; void* pChannels; } ;
struct TYPE_4__ {TYPE_2__* ee_modePowerArray5112; } ;
typedef  TYPE_1__ HAL_EEPROM ;
typedef  int /*<<< orphan*/  HAL_BOOL ;
typedef  int /*<<< orphan*/  EXPN_DATA_PER_CHANNEL_5112 ;
typedef  TYPE_2__ EEPROM_POWER_EXPN_5112 ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 void* AH_NULL ; 
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
#define  HAL_DIAG_EEPROM 131 
#define  HAL_DIAG_EEPROM_EXP_11A 130 
#define  HAL_DIAG_EEPROM_EXP_11B 129 
#define  HAL_DIAG_EEPROM_EXP_11G 128 
 int /*<<< orphan*/  roundup (int,int) ; 

__attribute__((used)) static HAL_BOOL
legacyEepromDiag(struct ath_hal *ah, int request,
     const void *args, uint32_t argsize, void **result, uint32_t *resultsize)
{
	HAL_EEPROM *ee = AH_PRIVATE(ah)->ah_eeprom;
	const EEPROM_POWER_EXPN_5112 *pe;

	switch (request) {
	case HAL_DIAG_EEPROM:
		*result = ee;
		*resultsize = sizeof(*ee);
		return AH_TRUE;
	case HAL_DIAG_EEPROM_EXP_11A:
	case HAL_DIAG_EEPROM_EXP_11B:
	case HAL_DIAG_EEPROM_EXP_11G:
		pe = &ee->ee_modePowerArray5112[
		    request - HAL_DIAG_EEPROM_EXP_11A];
		*result = pe->pChannels;
		*resultsize = (*result == AH_NULL) ? 0 :
			roundup(sizeof(uint16_t) * pe->numChannels,
				sizeof(uint32_t)) +
			sizeof(EXPN_DATA_PER_CHANNEL_5112) * pe->numChannels;
		return AH_TRUE;
	}
	return AH_FALSE;
}
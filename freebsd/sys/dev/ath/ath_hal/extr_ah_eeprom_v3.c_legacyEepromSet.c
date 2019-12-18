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
struct ath_hal {int dummy; } ;
struct TYPE_4__ {TYPE_1__* ah_eeprom; } ;
struct TYPE_3__ {int ee_Amode; int ee_Bmode; int ee_Gmode; int ee_turbo5Disable; int ee_turbo2Disable; int /*<<< orphan*/  ee_opCap; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  TYPE_1__ HAL_EEPROM ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_EEPROM_EEPCAP_AES_DIS ; 
 int /*<<< orphan*/  AR_EEPROM_EEPCAP_BURST_DIS ; 
 int /*<<< orphan*/  AR_EEPROM_EEPCAP_COMPRESS_DIS ; 
 int /*<<< orphan*/  AR_EEPROM_EEPCAP_FASTFRAME_DIS ; 
#define  AR_EEP_AES 136 
#define  AR_EEP_AMODE 135 
#define  AR_EEP_BMODE 134 
#define  AR_EEP_BURST 133 
#define  AR_EEP_COMPRESS 132 
#define  AR_EEP_FASTFRAME 131 
#define  AR_EEP_GMODE 130 
#define  AR_EEP_TURBO2DISABLE 129 
#define  AR_EEP_TURBO5DISABLE 128 
 int /*<<< orphan*/  HAL_EINVAL ; 
 int /*<<< orphan*/  HAL_OK ; 

__attribute__((used)) static HAL_STATUS
legacyEepromSet(struct ath_hal *ah, int param, int v)
{
	HAL_EEPROM *ee = AH_PRIVATE(ah)->ah_eeprom;

	switch (param) {
	case AR_EEP_AMODE:
		ee->ee_Amode = v;
		return HAL_OK;
	case AR_EEP_BMODE:
		ee->ee_Bmode = v;
		return HAL_OK;
	case AR_EEP_GMODE:
		ee->ee_Gmode = v;
		return HAL_OK;
	case AR_EEP_TURBO5DISABLE:
		ee->ee_turbo5Disable = v;
		return HAL_OK;
	case AR_EEP_TURBO2DISABLE:
		ee->ee_turbo2Disable = v;
		return HAL_OK;
	case AR_EEP_COMPRESS:
		if (v)
			ee->ee_opCap &= ~AR_EEPROM_EEPCAP_COMPRESS_DIS;
		else
			ee->ee_opCap |= AR_EEPROM_EEPCAP_COMPRESS_DIS;
		return HAL_OK;
	case AR_EEP_FASTFRAME:
		if (v)
			ee->ee_opCap &= ~AR_EEPROM_EEPCAP_FASTFRAME_DIS;
		else
			ee->ee_opCap |= AR_EEPROM_EEPCAP_FASTFRAME_DIS;
		return HAL_OK;
	case AR_EEP_AES:
		if (v)
			ee->ee_opCap &= ~AR_EEPROM_EEPCAP_AES_DIS;
		else
			ee->ee_opCap |= AR_EEPROM_EEPCAP_AES_DIS;
		return HAL_OK;
	case AR_EEP_BURST:
		if (v)
			ee->ee_opCap &= ~AR_EEPROM_EEPCAP_BURST_DIS;
		else
			ee->ee_opCap |= AR_EEPROM_EEPCAP_BURST_DIS;
		return HAL_OK;
	}
	return HAL_EINVAL;
}
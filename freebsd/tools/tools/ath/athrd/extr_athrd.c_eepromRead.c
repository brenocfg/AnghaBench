#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u_int16_t ;
typedef  int u_int ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_EEPROM_EEREGCAP_EN_KK_NEW_11A ; 
 int /*<<< orphan*/  AR_EEPROM_EEREGCAP_EN_KK_NEW_11A_PRE4_0 ; 
#define  AR_EEPROM_REG_CAPABILITIES_OFFSET 130 
#define  AR_EEPROM_REG_CAPABILITIES_OFFSET_PRE4_0 129 
#define  AR_EEPROM_VERSION 128 
 int /*<<< orphan*/  eeversion ; 

__attribute__((used)) static HAL_BOOL
eepromRead(struct ath_hal *ah, u_int off, u_int16_t *data)
{
	/* emulate enough stuff to handle japan channel shift */
	switch (off) {
	case AR_EEPROM_VERSION:
		*data = eeversion;
		return AH_TRUE;
	case AR_EEPROM_REG_CAPABILITIES_OFFSET:
		*data = AR_EEPROM_EEREGCAP_EN_KK_NEW_11A;
		return AH_TRUE;
	case AR_EEPROM_REG_CAPABILITIES_OFFSET_PRE4_0:
		*data = AR_EEPROM_EEREGCAP_EN_KK_NEW_11A_PRE4_0;
		return AH_TRUE;
	}
	return AH_FALSE;
}
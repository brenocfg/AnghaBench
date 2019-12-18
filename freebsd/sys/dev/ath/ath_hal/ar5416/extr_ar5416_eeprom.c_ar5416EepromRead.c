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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int u_int ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 scalar_t__ AR5416_EEPROM_OFFSET ; 
 int AR5416_EEPROM_S ; 
 scalar_t__ AR_EEPROM_STATUS_DATA ; 
 int AR_EEPROM_STATUS_DATA_BUSY ; 
 int AR_EEPROM_STATUS_DATA_PROT_ACCESS ; 
 int /*<<< orphan*/  AR_EEPROM_STATUS_DATA_VAL ; 
 int /*<<< orphan*/  MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,scalar_t__) ; 
 int /*<<< orphan*/  ath_hal_wait (struct ath_hal*,scalar_t__,int,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5416EepromRead(struct ath_hal *ah, u_int off, uint16_t *data)
{
        OS_REG_READ(ah,  AR5416_EEPROM_OFFSET + (off << AR5416_EEPROM_S));
       	if (!ath_hal_wait(ah, AR_EEPROM_STATUS_DATA,
	    AR_EEPROM_STATUS_DATA_BUSY | AR_EEPROM_STATUS_DATA_PROT_ACCESS, 0))
		return AH_FALSE;
       	*data = MS(OS_REG_READ(ah, AR_EEPROM_STATUS_DATA),
		   AR_EEPROM_STATUS_DATA_VAL);
	return AH_TRUE;
}
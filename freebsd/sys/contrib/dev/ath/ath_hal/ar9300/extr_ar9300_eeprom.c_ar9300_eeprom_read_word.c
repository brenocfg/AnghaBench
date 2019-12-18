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
typedef  scalar_t__ u_int16_t ;
typedef  int u_int ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 scalar_t__ AR9300_EEPROM_OFFSET ; 
 int AR9300_EEPROM_S ; 
 int /*<<< orphan*/  AR_EEPROM_STATUS_DATA ; 
 int AR_EEPROM_STATUS_DATA_BUSY ; 
 int AR_EEPROM_STATUS_DATA_PROT_ACCESS ; 
 int /*<<< orphan*/  AR_EEPROM_STATUS_DATA_VAL ; 
 scalar_t__ AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 scalar_t__ AR_SREV_OSPREY (struct ath_hal*) ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 scalar_t__ MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,scalar_t__) ; 
 int /*<<< orphan*/  ath_hal_wait (struct ath_hal*,scalar_t__,int,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_eeprom_read_word(struct ath_hal *ah, u_int off, u_int16_t *data)
{
    if (AR_SREV_OSPREY(ah) || AR_SREV_POSEIDON(ah))
    {
        (void) OS_REG_READ(ah, AR9300_EEPROM_OFFSET + (off << AR9300_EEPROM_S));
        if (!ath_hal_wait(ah,
			  AR_HOSTIF_REG(ah, AR_EEPROM_STATUS_DATA),
			  AR_EEPROM_STATUS_DATA_BUSY | AR_EEPROM_STATUS_DATA_PROT_ACCESS,
			  0))
	{
            return AH_FALSE;
	}
        *data = MS(OS_REG_READ(ah,
			       AR_HOSTIF_REG(ah, AR_EEPROM_STATUS_DATA)), AR_EEPROM_STATUS_DATA_VAL);
       return AH_TRUE;
    }
    else
    {
        *data = 0;
        return AH_FALSE;
    }
}
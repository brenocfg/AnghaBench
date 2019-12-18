#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int calibration_data_source; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  ar9300_calibration_data_read_eeprom (struct ath_hal*,long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ar9300_calibration_data_read_flash (struct ath_hal*,long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ar9300_calibration_data_read_nand (struct ath_hal*,long,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ar9300_calibration_data_read_otp (struct ath_hal*,long,int /*<<< orphan*/ *,int,int) ; 
#define  calibration_data_eeprom 131 
#define  calibration_data_flash 130 
#define  calibration_data_nand 129 
#define  calibration_data_otp 128 

HAL_BOOL
ar9300_calibration_data_read(struct ath_hal *ah, long address,
    u_int8_t *buffer, int many)
{
    switch (AH9300(ah)->calibration_data_source) {
    case calibration_data_flash:
        return ar9300_calibration_data_read_flash(ah, address, buffer, many);
    case calibration_data_eeprom:
        return ar9300_calibration_data_read_eeprom(ah, address, buffer, many);
    case calibration_data_otp:
        return ar9300_calibration_data_read_otp(ah, address, buffer, many, 1);
#ifdef ATH_CAL_NAND_FLASH
    case calibration_data_nand:
        return ar9300_calibration_data_read_nand(ah,address,buffer,many);
#endif

    }
    return AH_FALSE;
}
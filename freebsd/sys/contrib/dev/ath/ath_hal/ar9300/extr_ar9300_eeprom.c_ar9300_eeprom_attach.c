#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct TYPE_9__ {void* op_flags; } ;
struct TYPE_11__ {int txrx_mask; int txrxgain; TYPE_1__ op_cap_flags; } ;
struct TYPE_12__ {int* mac_addr; TYPE_3__ base_eep_header; } ;
struct ath_hal_9300 {int try_dram; int try_eeprom; int try_otp; int try_nand; int try_flash; int ah_emu_eeprom; TYPE_4__ ah_eeprom; scalar_t__ calibration_data_try_address; int /*<<< orphan*/  calibration_data_try; scalar_t__ calibration_data_source_address; int /*<<< orphan*/  calibration_data_source; } ;
struct ath_hal {int dummy; } ;
typedef  TYPE_4__ ar9300_eeprom_t ;
struct TYPE_10__ {scalar_t__ ath_hal_skip_eeprom_read; } ;
struct TYPE_13__ {TYPE_2__ ah_config; int /*<<< orphan*/  ah_getSpurChan; } ;
typedef  int /*<<< orphan*/  HAL_STATUS ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 TYPE_8__* AH_PRIVATE (struct ath_hal*) ; 
 void* AR9300_OPFLAGS_11G ; 
 scalar_t__ AR_SREV_HONEYBEE (struct ath_hal*) ; 
 scalar_t__ AR_SREV_HORNET (struct ath_hal*) ; 
 scalar_t__ AR_SREV_POSEIDON (struct ath_hal*) ; 
 scalar_t__ AR_SREV_SCORPION (struct ath_hal*) ; 
 scalar_t__ AR_SREV_WASP (struct ath_hal*) ; 
 int /*<<< orphan*/  FLASH_BASE_CALDATA_OFFSET ; 
 int /*<<< orphan*/  HAL_EIO ; 
 int /*<<< orphan*/  HAL_OK ; 
 int /*<<< orphan*/  ar9300_calibration_data_read_flash (struct ath_hal*,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ar9300_eeprom_get_spur_chan ; 
 int /*<<< orphan*/  ar9300_eeprom_restore (struct ath_hal*) ; 
 int ar9300_eeprom_struct_size () ; 
 size_t ar9300_eeprom_template_default ; 
 int /*<<< orphan*/  ar9300_fill_eeprom (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_flash_map (struct ath_hal*) ; 
 TYPE_4__ ar9300_template_ap121 ; 
 TYPE_4__ ar9300_template_generic ; 
 int /*<<< orphan*/  ath_hal_printf (struct ath_hal*,char*) ; 
 int /*<<< orphan*/  calibration_data_flash ; 
 int /*<<< orphan*/  calibration_data_none ; 
 int /*<<< orphan*/  calibration_data_source ; 
 int /*<<< orphan*/  calibration_data_try ; 
 TYPE_4__** default9300 ; 
 int /*<<< orphan*/  printf (char*,int) ; 

HAL_STATUS
ar9300_eeprom_attach(struct ath_hal *ah)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    ahp->try_dram = 1;
    ahp->try_eeprom = 1;
    ahp->try_otp = 1;
#ifdef ATH_CAL_NAND_FLASH
    ahp->try_nand = 1;
#else
    ahp->try_flash = 1;
#endif
    ahp->calibration_data_source = calibration_data_none;
    ahp->calibration_data_source_address = 0;
    ahp->calibration_data_try = calibration_data_try;
    ahp->calibration_data_try_address = 0;

    /*
     * In case flash will be used for EEPROM. Otherwise ahp->ah_cal_mem
     * must be set to NULL or the real EEPROM address.
     */
    ar9300_flash_map(ah);
    /*
     * ###### This function always return NO SPUR.
     * This is not true for many board designs.
     * Does anyone use this?
     */
    AH_PRIVATE(ah)->ah_getSpurChan = ar9300_eeprom_get_spur_chan;

#ifdef OLDCODE
    /* XXX Needs to be moved for dynamic selection */
    ahp->ah_eeprom = *(default9300[ar9300_eeprom_template_default]);


    if (AR_SREV_HORNET(ah)) {
        /* Set default values for Hornet. */
        ahp->ah_eeprom.base_eep_header.op_cap_flags.op_flags =
            AR9300_OPFLAGS_11G;
        ahp->ah_eeprom.base_eep_header.txrx_mask = 0x11;
    } else if (AR_SREV_POSEIDON(ah)) {
        /* Set default values for Poseidon. */
        ahp->ah_eeprom.base_eep_header.op_cap_flags.op_flags =
            AR9300_OPFLAGS_11G;
        ahp->ah_eeprom.base_eep_header.txrx_mask = 0x11;
    }

    if (AH_PRIVATE(ah)->ah_config.ath_hal_skip_eeprom_read) {
        ahp->ah_emu_eeprom = 1;
        return HAL_OK;
    }

    ahp->ah_emu_eeprom = 1;

#ifdef UNUSED
#endif
    
    if (!ar9300_fill_eeprom(ah)) {
        return HAL_EIO;
    }

    return HAL_OK;
    /* return ar9300_check_eeprom(ah); */
#else
    ahp->ah_emu_eeprom = 1;

#if 0
/*#ifdef MDK_AP*/ /* MDK_AP is defined only in NART AP build */
    u_int8_t buffer[10];
    int caldata_check = 0;

    ar9300_calibration_data_read_flash(
        ah, FLASH_BASE_CALDATA_OFFSET, buffer, 4);
    printf("flash caldata:: %x\n", buffer[0]);
    if (buffer[0] != 0xff) {
        caldata_check = 1;
    }
    if (!caldata_check) {
        ar9300_eeprom_t *mptr;
        int mdata_size;
        if (AR_SREV_HORNET(ah)) {
            /* XXX: For initial testing */
            mptr = &ahp->ah_eeprom;
            mdata_size = ar9300_eeprom_struct_size();
            ahp->ah_eeprom = ar9300_template_ap121;
            ahp->ah_emu_eeprom = 1;
            /* need it to let art save in to flash ????? */
            calibration_data_source = calibration_data_flash;
        } else if (AR_SREV_WASP(ah)) {
            /* XXX: For initial testing */
            ath_hal_printf(ah, " wasp eep attach\n");
            mptr = &ahp->ah_eeprom;
            mdata_size = ar9300_eeprom_struct_size();
            ahp->ah_eeprom = ar9300_template_generic;
            ahp->ah_eeprom.mac_addr[0] = 0x00;
            ahp->ah_eeprom.mac_addr[1] = 0x03;
            ahp->ah_eeprom.mac_addr[2] = 0x7F;
            ahp->ah_eeprom.mac_addr[3] = 0xBA;
            ahp->ah_eeprom.mac_addr[4] = 0xD0;
            ahp->ah_eeprom.mac_addr[5] = 0x00;
            ahp->ah_emu_eeprom = 1;
            ahp->ah_eeprom.base_eep_header.txrx_mask = 0x33;
            ahp->ah_eeprom.base_eep_header.txrxgain = 0x10;
            /* need it to let art save in to flash ????? */
            calibration_data_source = calibration_data_flash;
        }
        return HAL_OK;
    }
#endif
    if (AR_SREV_HORNET(ah) || AR_SREV_WASP(ah) || AR_SREV_SCORPION(ah)
        || AR_SREV_HONEYBEE(ah)) {
        ahp->try_eeprom = 0;
    }

    if (AR_SREV_HONEYBEE(ah)) {
        ahp->try_otp = 0;
    }

    if (!ar9300_eeprom_restore(ah)) {
        return HAL_EIO;
    }
    return HAL_OK;
#endif
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int8_t ;
struct TYPE_7__ {int tx_gain_cap; } ;
struct TYPE_6__ {int tx_gain_cap; } ;
struct TYPE_5__ {scalar_t__ misc_enable; } ;
struct TYPE_8__ {TYPE_3__ modal_header_5g; TYPE_2__ modal_header_2g; TYPE_1__ base_ext1; } ;
struct ath_hal_9300 {TYPE_4__ ah_eeprom; } ;
struct ath_hal {scalar_t__ ah_reset; } ;
typedef  TYPE_4__ ar9300_eeprom_t ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int AH_FALSE ; 
 int AH_TRUE ; 
 int /*<<< orphan*/  ar9300_eeprom_get_pcdac_tx_gain_table_i (struct ath_hal*,int,int*) ; 
 int ar9300_eeprom_get_tx_gain_table_number_max (struct ath_hal*) ; 

u_int8_t ar9300_eeprom_set_tx_gain_cap(struct ath_hal *ah, 
                                               int *tx_gain_max)
// pcdac read back from reg, read back value depends on reset 2GHz/5GHz ini 
// tx_gain_table, this function will be called twice after each 
// band's calibration.
// after 2GHz cal, tx_gain_max[0] has 2GHz, calibration max txgain, 
// tx_gain_max[1]=-100
// after 5GHz cal, tx_gain_max[0],tx_gain_max[1] have calibration 
// value for both band
// reset is on 5GHz, reg reading from tx_gain_table is for 5GHz,
// so program can't recalculate 2g.tx_gain_cap at this point.
{
    int i = 0, ig, im = 0;
    u_int8_t pcdac = 0;
    u_int8_t tx_gain_table_max;
    ar9300_eeprom_t *ahp_Eeprom;
    struct ath_hal_9300 *ahp = AH9300(ah);

    ahp_Eeprom = &ahp->ah_eeprom;

    if (ahp_Eeprom->base_ext1.misc_enable == 0)
        return AH_FALSE;

    tx_gain_table_max = ar9300_eeprom_get_tx_gain_table_number_max(ah);

    for (i = 0; i < 2; i++) {
        if (tx_gain_max[i]>-100) {	// -100 didn't cal that band.
            if ( i== 0) {
                if (tx_gain_max[1]>-100) {
                    continue;
                    // both band are calibrated, skip 2GHz 2g.tx_gain_cap reset
                }
            }
            for (ig = 1; ig <= tx_gain_table_max; ig++) {
                if (ah != 0 && ah->ah_reset != 0)
                {
                    ar9300_eeprom_get_pcdac_tx_gain_table_i(ah, ig, &pcdac);
                    if (pcdac >= tx_gain_max[i])
                        break;
                }
            }
            if (ig+1 <= tx_gain_table_max) {
                if (pcdac == tx_gain_max[i])
                    im = ig;
                else
                    im = ig + 1;
                if (i == 0) {
                    ahp_Eeprom->modal_header_2g.tx_gain_cap = im;
                } else {
                    ahp_Eeprom->modal_header_5g.tx_gain_cap = im;
                }
            } else {
                if (i == 0) {
                    ahp_Eeprom->modal_header_2g.tx_gain_cap = ig;
                } else {
                    ahp_Eeprom->modal_header_5g.tx_gain_cap = ig;
                }
            }
        }
    }
    return AH_TRUE;
}
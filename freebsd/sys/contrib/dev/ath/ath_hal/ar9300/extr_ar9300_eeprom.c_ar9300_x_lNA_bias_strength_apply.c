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
typedef  int u_int8_t ;
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_8__ {int xLNA_bias_strength; } ;
struct TYPE_7__ {int xLNA_bias_strength; } ;
struct TYPE_6__ {int misc_configuration; } ;
struct TYPE_9__ {TYPE_3__ modal_header_5g; TYPE_2__ modal_header_2g; TYPE_1__ base_eep_header; } ;
typedef  TYPE_4__ ar9300_eeprom_t ;
struct TYPE_10__ {TYPE_4__ ah_eeprom; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 TYPE_5__* AH9300 (struct ath_hal*) ; 
 scalar_t__ AH_TRUE ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH0_RXTX4 ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH1_RXTX4 ; 
 int /*<<< orphan*/  AR_PHY_65NM_CH2_RXTX4 ; 
 int /*<<< orphan*/  AR_PHY_65NM_RXTX4_XLNA_BIAS ; 
 scalar_t__ AR_SREV_OSPREY (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_RMW_FIELD (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

HAL_BOOL ar9300_x_lNA_bias_strength_apply(struct ath_hal *ah, HAL_BOOL is_2ghz)
{
    u_int8_t x_lNABias;
    u_int32_t value = 0;
    ar9300_eeprom_t *eep = &AH9300(ah)->ah_eeprom;

    if ((eep->base_eep_header.misc_configuration & 0x40) >> 6) {
        if (AR_SREV_OSPREY(ah)) {
            if (is_2ghz) {
                x_lNABias = eep->modal_header_2g.xLNA_bias_strength;
            } else {
                x_lNABias = eep->modal_header_5g.xLNA_bias_strength;
            }
            value = x_lNABias & ( 0x03 );	// bit0,1 for chain0
            OS_REG_RMW_FIELD(ah,
					AR_PHY_65NM_CH0_RXTX4, AR_PHY_65NM_RXTX4_XLNA_BIAS, value);
            value = (x_lNABias >> 2) & ( 0x03 );	// bit2,3 for chain1
            OS_REG_RMW_FIELD(ah,
					AR_PHY_65NM_CH1_RXTX4, AR_PHY_65NM_RXTX4_XLNA_BIAS, value);
            value = (x_lNABias >> 4) & ( 0x03 );	// bit4,5 for chain2
            OS_REG_RMW_FIELD(ah,
					AR_PHY_65NM_CH2_RXTX4, AR_PHY_65NM_RXTX4_XLNA_BIAS, value);
        }
    }
    return AH_TRUE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_6__ {int version; int pwdclkind; } ;
struct TYPE_5__ {TYPE_2__ base_eep_header; } ;
typedef  TYPE_1__ ar9300_eeprom_t ;
struct TYPE_7__ {int ah_devid; } ;
typedef  TYPE_2__ BASE_EEPDEF_HEADER ;

/* Variables and functions */
 int /*<<< orphan*/  AH_NULL ; 
 TYPE_4__* AH_PRIVATE (struct ath_hal*) ; 
#define  AR9300_DEVID_AR9300_PCI 128 
 int AR_AN_TOP2_PWDCLKIND ; 
 int AR_AN_TOP2_PWDCLKIND_S ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  HAL_DEBUG_EEPROM ; 
 int /*<<< orphan*/  HAL_DEBUG_UNMASKABLE ; 

u_int32_t
ar9300_ini_fixup(struct ath_hal *ah, ar9300_eeprom_t *p_eep_data,
    u_int32_t reg, u_int32_t value)
{
    HALDEBUG(AH_NULL, HAL_DEBUG_UNMASKABLE,
        "ar9300_eeprom_def_ini_fixup: FIXME\n");
#if 0
    BASE_EEPDEF_HEADER  *p_base  = &(p_eep_data->base_eep_header);

    switch (AH_PRIVATE(ah)->ah_devid)
    {
    case AR9300_DEVID_AR9300_PCI:
        /*
        ** Need to set the external/internal regulator bit to the proper value.
        ** Can only write this ONCE.
        */

        if ( reg == 0x7894 )
        {
            /*
            ** Check for an EEPROM data structure of "0x0b" or better
            */

            HALDEBUG(ah, HAL_DEBUG_EEPROM, "ini VAL: %x  EEPROM: %x\n",
                     value, (p_base->version & 0xff));

            if ( (p_base->version & 0xff) > 0x0a) {
                HALDEBUG(ah, HAL_DEBUG_EEPROM,
                    "PWDCLKIND: %d\n", p_base->pwdclkind);
                value &= ~AR_AN_TOP2_PWDCLKIND;
                value |=
                    AR_AN_TOP2_PWDCLKIND &
                    (p_base->pwdclkind <<  AR_AN_TOP2_PWDCLKIND_S);
            } else {
                HALDEBUG(ah, HAL_DEBUG_EEPROM, "PWDCLKIND Earlier Rev\n");
            }

            HALDEBUG(ah, HAL_DEBUG_EEPROM, "final ini VAL: %x\n", value);
        }
        break;

    }

    return (value);
#else
    return 0;
#endif
}
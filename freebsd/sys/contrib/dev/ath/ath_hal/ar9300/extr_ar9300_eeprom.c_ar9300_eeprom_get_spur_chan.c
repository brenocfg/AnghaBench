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
typedef  int /*<<< orphan*/  u_int16_t ;
struct ath_hal_9300 {int /*<<< orphan*/  ah_eeprom; } ;
struct ath_hal {int dummy; } ;
struct TYPE_9__ {TYPE_3__* modal_header; } ;
typedef  TYPE_4__ ar9300_eeprom_t ;
struct TYPE_6__ {int ath_hal_spur_mode; int /*<<< orphan*/ ** ath_hal_spur_chans; } ;
struct TYPE_10__ {TYPE_1__ ah_config; } ;
struct TYPE_8__ {TYPE_2__* spur_chans; } ;
struct TYPE_7__ {int /*<<< orphan*/  spur_chan; } ;
typedef  size_t HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 TYPE_5__* AH_PRIVATE (struct ath_hal*) ; 
 int AR_EEPROM_MODAL_SPURS ; 
 int /*<<< orphan*/  AR_NO_SPUR ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int /*<<< orphan*/  HALDEBUG (struct ath_hal*,int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  HAL_DEBUG_ANI ; 
#define  SPUR_DISABLE 130 
#define  SPUR_ENABLE_EEPROM 129 
#define  SPUR_ENABLE_IOCTL 128 

__attribute__((used)) static u_int16_t
ar9300_eeprom_get_spur_chan(struct ath_hal *ah, int i, HAL_BOOL is_2ghz)
{
    u_int16_t   spur_val = AR_NO_SPUR;
#if 0
    struct ath_hal_9300 *ahp = AH9300(ah);
    ar9300_eeprom_t *eep = (ar9300_eeprom_t *)&ahp->ah_eeprom;

    HALASSERT(i <  AR_EEPROM_MODAL_SPURS );

    HALDEBUG(ah, HAL_DEBUG_ANI,
             "Getting spur idx %d is2Ghz. %d val %x\n",
             i, is_2ghz,
             AH_PRIVATE(ah)->ah_config.ath_hal_spur_chans[i][is_2ghz]);

    switch (AH_PRIVATE(ah)->ah_config.ath_hal_spur_mode) {
    case SPUR_DISABLE:
        /* returns AR_NO_SPUR */
        break;
    case SPUR_ENABLE_IOCTL:
        spur_val = AH_PRIVATE(ah)->ah_config.ath_hal_spur_chans[i][is_2ghz];
        HALDEBUG(ah, HAL_DEBUG_ANI,
            "Getting spur val from new loc. %d\n", spur_val);
        break;
    case SPUR_ENABLE_EEPROM:
        spur_val = eep->modal_header[is_2ghz].spur_chans[i].spur_chan;
        break;

    }
#endif
    return spur_val;
}
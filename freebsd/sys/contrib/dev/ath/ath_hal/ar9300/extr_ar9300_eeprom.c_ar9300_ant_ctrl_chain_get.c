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
typedef  int /*<<< orphan*/  u_int16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/ * ant_ctrl_chain; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ant_ctrl_chain; } ;
struct TYPE_7__ {TYPE_2__ modal_header_5g; TYPE_1__ modal_header_2g; } ;
typedef  TYPE_3__ ar9300_eeprom_t ;
struct TYPE_8__ {TYPE_3__ ah_eeprom; } ;
typedef  scalar_t__ HAL_BOOL ;

/* Variables and functions */
 TYPE_4__* AH9300 (struct ath_hal*) ; 
 int OSPREY_MAX_CHAINS ; 

u_int16_t ar9300_ant_ctrl_chain_get(struct ath_hal *ah, int chain,
    HAL_BOOL is_2ghz)
{
    ar9300_eeprom_t *eep = &AH9300(ah)->ah_eeprom;
    if (chain >= 0 && chain < OSPREY_MAX_CHAINS) {
        if (is_2ghz) {
            return eep->modal_header_2g.ant_ctrl_chain[chain];
        } else {
            return eep->modal_header_5g.ant_ctrl_chain[chain];
        }
    }
    return 0;
}
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
typedef  int u_int16_t ;
struct ath_hal {int dummy; } ;
struct TYPE_6__ {int tx_end_to_xpa_off; } ;
struct TYPE_5__ {int tx_end_to_xpa_off; } ;
struct TYPE_7__ {TYPE_2__ modal_header_5g; TYPE_1__ modal_header_2g; } ;
typedef  TYPE_3__ ar9300_eeprom_t ;
struct TYPE_8__ {TYPE_3__ ah_eeprom; } ;

/* Variables and functions */
 TYPE_4__* AH9300 (struct ath_hal*) ; 

__attribute__((used)) static u_int16_t ar9300_tx_end_to_xpa_off_get(struct ath_hal *ah, u_int16_t channel)
{
    ar9300_eeprom_t *eep = &AH9300(ah)->ah_eeprom;

    if (channel < 4000) {
        return eep->modal_header_2g.tx_end_to_xpa_off;
    } else {
        return eep->modal_header_5g.tx_end_to_xpa_off;
    }
}
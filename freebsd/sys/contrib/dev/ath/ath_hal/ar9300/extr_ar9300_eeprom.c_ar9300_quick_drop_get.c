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
typedef  int u_int16_t ;
struct ath_hal {int dummy; } ;
typedef  int int32_t ;
struct TYPE_8__ {int quick_drop_low; int quick_drop_high; } ;
struct TYPE_7__ {int quick_drop; } ;
struct TYPE_6__ {int quick_drop; } ;
struct TYPE_9__ {TYPE_3__ base_ext1; TYPE_2__ modal_header_5g; TYPE_1__ modal_header_2g; } ;
typedef  TYPE_4__ ar9300_eeprom_t ;
struct TYPE_10__ {TYPE_4__ ah_eeprom; } ;

/* Variables and functions */
 TYPE_5__* AH9300 (struct ath_hal*) ; 
 int interpolate (int,int*,int*,int) ; 

__attribute__((used)) static u_int16_t ar9300_quick_drop_get(struct ath_hal *ah, 
								int chain, u_int16_t channel)
{
    int32_t f[3], t[3];
    u_int16_t value;
    ar9300_eeprom_t *eep = &AH9300(ah)->ah_eeprom;

    if (channel < 4000) {
        return eep->modal_header_2g.quick_drop;
    } else {
        t[0] = eep->base_ext1.quick_drop_low;
        f[0] = 5180;
        t[1] = eep->modal_header_5g.quick_drop;
        f[1] = 5500;
        t[2] = eep->base_ext1.quick_drop_high;
        f[2] = 5785;
        value = interpolate(channel, f, t, 3);
        return value;
    }
}
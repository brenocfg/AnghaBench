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
struct TYPE_8__ {int* xatten1_margin; } ;
struct TYPE_7__ {scalar_t__* xatten1_margin_low; int* xatten1_margin_high; } ;
struct TYPE_6__ {int* xatten1_margin; } ;
struct TYPE_9__ {TYPE_3__ modal_header_5g; TYPE_2__ base_ext2; TYPE_1__ modal_header_2g; } ;
typedef  TYPE_4__ ar9300_eeprom_t ;
struct TYPE_10__ {TYPE_4__ ah_eeprom; } ;

/* Variables and functions */
 TYPE_5__* AH9300 (struct ath_hal*) ; 
 int OSPREY_MAX_CHAINS ; 
 int interpolate (int,int*,int*,int) ; 

__attribute__((used)) static u_int16_t
ar9300_attenuation_margin_chain_get(struct ath_hal *ah, int chain,
    u_int16_t channel)
{
    int32_t f[3], t[3];
    u_int16_t value;
    ar9300_eeprom_t *eep = &AH9300(ah)->ah_eeprom;
    if (chain >= 0 && chain < OSPREY_MAX_CHAINS) {
        if (channel < 4000) {
            return eep->modal_header_2g.xatten1_margin[chain];
        } else {
            if (eep->base_ext2.xatten1_margin_low[chain] != 0) {    
                t[0] = eep->base_ext2.xatten1_margin_low[chain];
                f[0] = 5180;
                t[1] = eep->modal_header_5g.xatten1_margin[chain];
                f[1] = 5500;
                t[2] = eep->base_ext2.xatten1_margin_high[chain];
                f[2] = 5785;
                value = interpolate(channel, f, t, 3);
                return value;
            } else {
                return eep->modal_header_5g.xatten1_margin[chain];
            }
        }
    }
    return 0;
}
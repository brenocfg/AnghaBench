#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int misc_configuration; } ;
struct TYPE_4__ {TYPE_1__ base_eep_header; } ;
struct ath_hal_9300 {TYPE_2__ ah_eeprom; } ;
struct ath_hal {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 

int32_t ar9300_thermometer_get(struct ath_hal *ah)
{
    struct ath_hal_9300 *ahp = AH9300(ah);
    int thermometer;
    thermometer =
        (ahp->ah_eeprom.base_eep_header.misc_configuration >> 1) & 0x3;
    thermometer--;
    return thermometer;
}
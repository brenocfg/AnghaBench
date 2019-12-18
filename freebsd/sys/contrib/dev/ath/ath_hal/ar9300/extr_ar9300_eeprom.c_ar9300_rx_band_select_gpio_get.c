#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_4__ {int /*<<< orphan*/  rx_band_select_gpio; } ;
struct TYPE_5__ {TYPE_1__ base_eep_header; } ;
typedef  TYPE_2__ ar9300_eeprom_t ;
struct TYPE_6__ {TYPE_2__ ah_eeprom; } ;

/* Variables and functions */
 TYPE_3__* AH9300 (struct ath_hal*) ; 

int32_t 
ar9300_rx_band_select_gpio_get(struct ath_hal *ah)
{
    ar9300_eeprom_t *eep = &AH9300(ah)->ah_eeprom;
    return eep->base_eep_header.rx_band_select_gpio;
}
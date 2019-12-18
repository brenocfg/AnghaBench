#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {scalar_t__ ah_devid; } ;

/* Variables and functions */
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 scalar_t__ AR9300_DEVID_AR9380_PCIE ; 
 int AR9382_GPIO_PIN_8_RESERVED ; 
 int AR9382_MAX_GPIO_INPUT_PIN_NUM ; 
 int AR9382_MAX_GPIO_PIN_NUM ; 

u_int32_t
ar9300_gpio_get_mask(struct ath_hal *ah)
{
    u_int32_t mask = (1 << (AR9382_MAX_GPIO_INPUT_PIN_NUM + 1) ) - 1;

    if (AH_PRIVATE(ah)->ah_devid == AR9300_DEVID_AR9380_PCIE) {
        mask = (1 << AR9382_MAX_GPIO_PIN_NUM) - 1;
        mask &= ~(1 << AR9382_GPIO_PIN_8_RESERVED);
    }
    return mask;
}
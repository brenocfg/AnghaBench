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
typedef  int u_int32_t ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {int halNumGpioPins; } ;
struct TYPE_4__ {TYPE_1__ ah_caps; } ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_GPIO_INTR_POL ; 
 int /*<<< orphan*/  AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_INTR_SYNC_CAUSE_CLR ; 
 int AR_INTR_SYNC_ENABLE_GPIO_S ; 
 int /*<<< orphan*/  OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar9300_gpio_set_polarity(struct ath_hal *ah, u_int32_t pol_map,
                         u_int32_t changed_mask)
{
    u_int32_t gpio_mask;

    gpio_mask = (1 << AH_PRIVATE(ah)->ah_caps.halNumGpioPins) - 1;
    OS_REG_WRITE(ah, AR_HOSTIF_REG(ah, AR_GPIO_INTR_POL), gpio_mask & pol_map);

#ifndef ATH_GPIO_USE_ASYNC_CAUSE
    /*
     * For SYNC_CAUSE type interrupts, we need to clear the cause register
     * explicitly. Otherwise an interrupt with the original polarity setting
     * will come up immediately (if there is already an interrupt source),
     * which is not what we want usually.
     */
    OS_REG_WRITE(ah, AR_HOSTIF_REG(ah, AR_INTR_SYNC_CAUSE_CLR),
                 changed_mask << AR_INTR_SYNC_ENABLE_GPIO_S);
    OS_REG_READ(ah, AR_HOSTIF_REG(ah, AR_INTR_SYNC_CAUSE_CLR));
#endif
}
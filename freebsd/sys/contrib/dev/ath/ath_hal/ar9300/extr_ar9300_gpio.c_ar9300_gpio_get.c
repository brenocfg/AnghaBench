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
 int AR9382_GPIO_PIN_8_RESERVED ; 
 int AR_GPIO_BIT (int) ; 
 int /*<<< orphan*/  AR_GPIO_IN ; 
 int /*<<< orphan*/  AR_GPIO_IN_VAL ; 
 int /*<<< orphan*/  AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int MS (int,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW (struct ath_hal*,int /*<<< orphan*/ ,int,int) ; 

u_int32_t
ar9300_gpio_get(struct ath_hal *ah, u_int32_t gpio)
{
    u_int32_t gpio_in;
    HALASSERT(gpio < AH_PRIVATE(ah)->ah_caps.halNumGpioPins);
    if (gpio == AR9382_GPIO_PIN_8_RESERVED)
    {
        return 0xffffffff;
    }

    gpio_in = OS_REG_READ(ah, AR_HOSTIF_REG(ah, AR_GPIO_IN));
    OS_REG_RMW(ah, AR_HOSTIF_REG(ah, AR_GPIO_IN),
        (1 << gpio), AR_GPIO_BIT(gpio));
    return (MS(gpio_in, AR_GPIO_IN_VAL) & AR_GPIO_BIT(gpio)) != 0;
}
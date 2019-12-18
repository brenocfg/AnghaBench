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
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int AR9382_GPIO_9_INPUT_ONLY ; 
 int AR9382_GPIO_PIN_8_RESERVED ; 
 int /*<<< orphan*/  AR_GPIO_BIT (int) ; 
 int /*<<< orphan*/  AR_GPIO_OUT ; 
 int /*<<< orphan*/  AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int /*<<< orphan*/  OS_REG_RMW (struct ath_hal*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_gpio_set(struct ath_hal *ah, u_int32_t gpio, u_int32_t val)
{
    HALASSERT(gpio < AH_PRIVATE(ah)->ah_caps.halNumGpioPins);
    if ((gpio == AR9382_GPIO_PIN_8_RESERVED)  ||
        (gpio == AR9382_GPIO_9_INPUT_ONLY))
    {
        return AH_FALSE;
    }
    OS_REG_RMW(ah, AR_HOSTIF_REG(ah, AR_GPIO_OUT),
        ((val & 1) << gpio), AR_GPIO_BIT(gpio));

    return AH_TRUE;
}
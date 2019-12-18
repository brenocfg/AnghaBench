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
 int AR9382_GPIO_PIN_8_RESERVED ; 
 int AR9382_MAX_GPIO_INPUT_PIN_NUM ; 
 int AR9382_MAX_JTAG_GPIO_PIN_NUM ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_EN_VAL ; 
 int /*<<< orphan*/  AR_GPIO_JTAG_DISABLE ; 
 int /*<<< orphan*/  AR_GPIO_OE_OUT ; 
 int AR_GPIO_OE_OUT_DRV ; 
 int AR_GPIO_OE_OUT_DRV_NO ; 
 int /*<<< orphan*/  AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 int /*<<< orphan*/  OS_REG_RMW (struct ath_hal*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_gpio_cfg_input(struct ath_hal *ah, u_int32_t gpio)
{
    u_int32_t    gpio_shift;

    HALASSERT(gpio < AH_PRIVATE(ah)->ah_caps.halNumGpioPins);
    if ((gpio == AR9382_GPIO_PIN_8_RESERVED)  ||
        (gpio > AR9382_MAX_GPIO_INPUT_PIN_NUM))
    {
        return AH_FALSE;
    }

    if (gpio <= AR9382_MAX_JTAG_GPIO_PIN_NUM) {
        OS_REG_SET_BIT(ah,
            AR_HOSTIF_REG(ah, AR_GPIO_INPUT_EN_VAL), AR_GPIO_JTAG_DISABLE);
    }
    /* TODO: configure input mux for AR9300 */
    /* If configured as input, set output to tristate */
    gpio_shift = 2 * gpio;

    OS_REG_RMW(ah,
               AR_HOSTIF_REG(ah, AR_GPIO_OE_OUT),
               (AR_GPIO_OE_OUT_DRV_NO << gpio_shift),
               (AR_GPIO_OE_OUT_DRV << gpio_shift));
    return AH_TRUE;
}
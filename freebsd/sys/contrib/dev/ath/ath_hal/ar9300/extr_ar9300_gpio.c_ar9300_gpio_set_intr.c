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
typedef  scalar_t__ u_int32_t ;
typedef  scalar_t__ u_int ;
struct ath_hal {int dummy; } ;
struct TYPE_3__ {scalar_t__ halNumGpioPins; } ;
struct TYPE_4__ {TYPE_1__ ah_caps; } ;

/* Variables and functions */
 TYPE_2__* AH_PRIVATE (struct ath_hal*) ; 
 scalar_t__ AR9382_GPIO_PIN_8_RESERVED ; 
 scalar_t__ AR9382_MAX_GPIO_INPUT_PIN_NUM ; 
 int ARRAY_LENGTH (scalar_t__*) ; 
 int /*<<< orphan*/  AR_GPIO_INTR_POL ; 
 scalar_t__ AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_INTR_ASYNC_ENABLE ; 
 scalar_t__ AR_INTR_ASYNC_ENABLE_GPIO_S ; 
 int /*<<< orphan*/  AR_INTR_ASYNC_MASK ; 
 scalar_t__ AR_INTR_ASYNC_MASK_GPIO_S ; 
 int /*<<< orphan*/  AR_INTR_SYNC_ENABLE ; 
 scalar_t__ AR_INTR_SYNC_ENABLE_GPIO_S ; 
 int /*<<< orphan*/  AR_INTR_SYNC_MASK ; 
 scalar_t__ AR_INTR_SYNC_MASK_GPIO_S ; 
 int /*<<< orphan*/  HALASSERT (int) ; 
 scalar_t__ HAL_GPIO_INTR_DISABLE ; 
 scalar_t__ HAL_GPIO_INTR_HIGH ; 
 scalar_t__ HAL_GPIO_INTR_LOW ; 
 scalar_t__ OS_REG_READ (struct ath_hal*,scalar_t__) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,scalar_t__,scalar_t__) ; 

void
ar9300_gpio_set_intr(struct ath_hal *ah, u_int gpio, u_int32_t ilevel)
{


    int i, reg_bit;
    u_int32_t reg_val;
    u_int32_t regs[2], shifts[2];

#ifdef AH_ASSERT
    u_int32_t gpio_mask;
    u_int32_t old_field_val = 0, field_val = 0;
#endif

#ifdef ATH_GPIO_USE_ASYNC_CAUSE
    regs[0] = AR_HOSTIF_REG(ah, AR_INTR_ASYNC_ENABLE);
    regs[1] = AR_HOSTIF_REG(ah, AR_INTR_ASYNC_MASK);
    shifts[0] = AR_INTR_ASYNC_ENABLE_GPIO_S;
    shifts[1] = AR_INTR_ASYNC_MASK_GPIO_S;
#else
    regs[0] = AR_HOSTIF_REG(ah, AR_INTR_SYNC_ENABLE);
    regs[1] = AR_HOSTIF_REG(ah, AR_INTR_SYNC_MASK);
    shifts[0] = AR_INTR_SYNC_ENABLE_GPIO_S;
    shifts[1] = AR_INTR_SYNC_MASK_GPIO_S;
#endif

    HALASSERT(gpio < AH_PRIVATE(ah)->ah_caps.halNumGpioPins);

    if ((gpio == AR9382_GPIO_PIN_8_RESERVED) ||
        (gpio > AR9382_MAX_GPIO_INPUT_PIN_NUM))
    {
        return;
    }

#ifdef AH_ASSERT
    gpio_mask = (1 << AH_PRIVATE(ah)->ah_caps.halNumGpioPins) - 1;
#endif
    if (ilevel == HAL_GPIO_INTR_DISABLE) {
        /* clear this GPIO's bit in the interrupt registers */
        for (i = 0; i < ARRAY_LENGTH(regs); i++) {
            reg_val = OS_REG_READ(ah, regs[i]);
            reg_bit = shifts[i] + gpio;
            reg_val &= ~(1 << reg_bit);
            OS_REG_WRITE(ah, regs[i], reg_val);

            /* check that each register has same GPIOs enabled */
#ifdef AH_ASSERT
            field_val = (reg_val >> shifts[i]) & gpio_mask;
            HALASSERT(i == 0 || old_field_val == field_val);
            old_field_val = field_val;
#endif
        }

    } else {
        reg_val = OS_REG_READ(ah, AR_HOSTIF_REG(ah, AR_GPIO_INTR_POL));
        reg_bit = gpio;
        if (ilevel == HAL_GPIO_INTR_HIGH) {
            /* 0 == interrupt on pin high */
            reg_val &= ~(1 << reg_bit);
        } else if (ilevel == HAL_GPIO_INTR_LOW) {
            /* 1 == interrupt on pin low */
            reg_val |= (1 << reg_bit);
        }
        OS_REG_WRITE(ah, AR_HOSTIF_REG(ah, AR_GPIO_INTR_POL), reg_val);

        /* set this GPIO's bit in the interrupt registers */
        for (i = 0; i < ARRAY_LENGTH(regs); i++) {
            reg_val = OS_REG_READ(ah, regs[i]);
            reg_bit = shifts[i] + gpio;
            reg_val |= (1 << reg_bit);
            OS_REG_WRITE(ah, regs[i], reg_val);

            /* check that each register has same GPIOs enabled */
#ifdef AH_ASSERT
            field_val = (reg_val >> shifts[i]) & gpio_mask;
            HALASSERT(i == 0 || old_field_val == field_val);
            old_field_val = field_val;
#endif
        }
    }
}
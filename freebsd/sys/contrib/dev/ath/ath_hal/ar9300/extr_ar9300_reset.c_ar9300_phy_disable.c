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
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ah_curchan; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_NULL ; 
 TYPE_1__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_GPIO_OUTPUT_MUX1 ; 
 int /*<<< orphan*/  AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 scalar_t__ AR_SREV_HONEYBEE (struct ath_hal*) ; 
 scalar_t__ AR_SREV_OSPREY (struct ath_hal*) ; 
 scalar_t__ AR_SREV_SCORPION (struct ath_hal*) ; 
 scalar_t__ AR_SREV_WASP (struct ath_hal*) ; 
 int /*<<< orphan*/  ATH_GPIO_OE ; 
 int /*<<< orphan*/  ATH_GPIO_OUT ; 
 int /*<<< orphan*/  HAL_RESET_WARM ; 
 scalar_t__ IS_CHAN_2GHZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_RMW (struct ath_hal*,int /*<<< orphan*/ ,int,int) ; 
 int REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9300_disable_pll_lock_detect (struct ath_hal*) ; 
 int /*<<< orphan*/  ar9300_init_pll (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar9300_set_reset_reg (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar9300_phy_disable(struct ath_hal *ah)
{
    if (!ar9300_set_reset_reg(ah, HAL_RESET_WARM)) {
        return AH_FALSE;
    }

#ifdef ATH_SUPPORT_LED
#define REG_READ(_reg)          *((volatile u_int32_t *)(_reg))
#define REG_WRITE(_reg, _val)   *((volatile u_int32_t *)(_reg)) = (_val);
#define ATH_GPIO_OE             0xB8040000
#define ATH_GPIO_OUT            0xB8040008 /* GPIO Ouput Value reg.*/
    if (AR_SREV_WASP(ah)) {
        if (IS_CHAN_2GHZ((AH_PRIVATE(ah)->ah_curchan))) {
            REG_WRITE(ATH_GPIO_OE, (REG_READ(ATH_GPIO_OE) | (0x1 << 13)));
        }
        else { 
            REG_WRITE(ATH_GPIO_OE, (REG_READ(ATH_GPIO_OE) | (0x1 << 12)));
        }
    }
    else if (AR_SREV_SCORPION(ah)) {
        if (IS_CHAN_2GHZ((AH_PRIVATE(ah)->ah_curchan))) {
            REG_WRITE(ATH_GPIO_OE, (REG_READ(ATH_GPIO_OE) | (0x1 << 13)));
        }
        else {
            REG_WRITE(ATH_GPIO_OE, (REG_READ(ATH_GPIO_OE) | (0x1 << 12)));
        }
        /* Turn off JMPST led */
        REG_WRITE(ATH_GPIO_OUT, (REG_READ(ATH_GPIO_OUT) | (0x1 << 15)));
    }
    else if (AR_SREV_HONEYBEE(ah)) {
        REG_WRITE(ATH_GPIO_OE, (REG_READ(ATH_GPIO_OE) | (0x1 << 12)));
    }
#undef REG_READ
#undef REG_WRITE
#endif

    if ( AR_SREV_OSPREY(ah) ) { 
        OS_REG_RMW(ah, AR_HOSTIF_REG(ah, AR_GPIO_OUTPUT_MUX1), 0x0, 0x1f);
    }


    ar9300_init_pll(ah, AH_NULL);
    ar9300_disable_pll_lock_detect(ah);

    return AH_TRUE;
}
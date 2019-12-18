#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ath_hal_9300 {int ah_gpio_select; scalar_t__ ah_polarity; scalar_t__ ah_gpio_bit; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_EN_VAL ; 
 int AR_GPIO_INPUT_EN_VAL_RFSILENT_BB ; 
 int /*<<< orphan*/  AR_GPIO_INPUT_MUX2 ; 
 int AR_GPIO_INPUT_MUX2_RFSILENT ; 
 int /*<<< orphan*/  AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_PHY_TEST ; 
 int /*<<< orphan*/  AR_RFSILENT ; 
 int AR_RFSILENT_FORCE ; 
 scalar_t__ AR_SREV_APHRODITE (struct ath_hal*) ; 
 scalar_t__ AR_SREV_JUPITER (struct ath_hal*) ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int RFSILENT_BB ; 
 scalar_t__ ar9300_gpio_get (struct ath_hal*,int) ; 
 int /*<<< orphan*/  ar9300_gpio_set_intr (struct ath_hal*,int,int) ; 
 int /*<<< orphan*/  ath_hal_gpioCfgInput (struct ath_hal*,int) ; 
 scalar_t__ ath_hal_hasrfkill_int (struct ath_hal*) ; 

void
ar9300_enable_rf_kill(struct ath_hal *ah)
{
    /* TODO - can this really be above the hal on the GPIO interface for
     * TODO - the client only?
     */
    struct ath_hal_9300    *ahp = AH9300(ah);

    if (AR_SREV_JUPITER(ah) || AR_SREV_APHRODITE(ah)) {
    	/* Check RF kill GPIO before set/clear RFSILENT bits. */
    	if (ar9300_gpio_get(ah, ahp->ah_gpio_select) == ahp->ah_polarity) {
            OS_REG_SET_BIT(ah, AR_HOSTIF_REG(ah, AR_RFSILENT), 
                           AR_RFSILENT_FORCE);
            OS_REG_SET_BIT(ah, AR_PHY_TEST, RFSILENT_BB);
        }
        else {
            OS_REG_CLR_BIT(ah, AR_HOSTIF_REG(ah, AR_RFSILENT), 
                           AR_RFSILENT_FORCE);
            OS_REG_CLR_BIT(ah, AR_PHY_TEST, RFSILENT_BB);
        }
    }
    else {
        /* Connect rfsilent_bb_l to baseband */
        OS_REG_SET_BIT(ah, AR_HOSTIF_REG(ah, AR_GPIO_INPUT_EN_VAL),
            AR_GPIO_INPUT_EN_VAL_RFSILENT_BB);

        /* Set input mux for rfsilent_bb_l to GPIO #0 */
        OS_REG_CLR_BIT(ah, AR_HOSTIF_REG(ah, AR_GPIO_INPUT_MUX2),
            AR_GPIO_INPUT_MUX2_RFSILENT);
        OS_REG_SET_BIT(ah, AR_HOSTIF_REG(ah, AR_GPIO_INPUT_MUX2),
            (ahp->ah_gpio_select & 0x0f) << 4);

        /*
         * Configure the desired GPIO port for input and
         * enable baseband rf silence
         */
        ath_hal_gpioCfgInput(ah, ahp->ah_gpio_select);
        OS_REG_SET_BIT(ah, AR_PHY_TEST, RFSILENT_BB);
    }

    /*
     * If radio disable switch connection to GPIO bit x is enabled
     * program GPIO interrupt.
     * If rfkill bit on eeprom is 1, setupeeprommap routine has already
     * verified that it is a later version of eeprom, it has a place for
     * rfkill bit and it is set to 1, indicating that GPIO bit x hardware
     * connection is present.
     */
     /*
      * RFKill uses polling not interrupt,
      * disable interrupt to avoid Eee PC 2.6.21.4 hang up issue
      */
    if (ath_hal_hasrfkill_int(ah)) {
        if (ahp->ah_gpio_bit == ar9300_gpio_get(ah, ahp->ah_gpio_select)) {
            /* switch already closed, set to interrupt upon open */
            ar9300_gpio_set_intr(ah, ahp->ah_gpio_select, !ahp->ah_gpio_bit);
        } else {
            ar9300_gpio_set_intr(ah, ahp->ah_gpio_select, ahp->ah_gpio_bit);
        }
    }
}
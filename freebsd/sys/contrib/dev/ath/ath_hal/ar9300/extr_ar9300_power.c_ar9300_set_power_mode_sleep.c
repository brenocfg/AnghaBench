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
struct ath_hal_9300 {int ah_wa_reg_val; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_9300* AH9300 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_GEN_TIMERS2_MODE ; 
 int /*<<< orphan*/  AR_HOSTIF_REG (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AR_MCI_INTERRUPT_RX_MSG_EN ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE_EN ; 
 int /*<<< orphan*/  AR_RTC_RESET ; 
 int /*<<< orphan*/  AR_RTC_RESET_EN ; 
 int /*<<< orphan*/  AR_SLP32_INC ; 
 scalar_t__ AR_SREV_APHRODITE (struct ath_hal*) ; 
 scalar_t__ AR_SREV_JUPITER (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_JUPITER_10 (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int /*<<< orphan*/  AR_STA_ID1_PWR_SAV ; 
 int /*<<< orphan*/  AR_TIMER_MODE ; 
 int /*<<< orphan*/  AR_WA ; 
 int AR_WA_D3_TO_L1_DISABLE ; 
 int /*<<< orphan*/  HAL_WOW_CTRL (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HAL_WOW_OFFLOAD_SET_4004_BIT14 ; 
 int /*<<< orphan*/  OS_DELAY (int) ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar9300_set_power_mode_sleep(struct ath_hal *ah, int set_chip)
{
    struct ath_hal_9300 *ahp = AH9300(ah);

    OS_REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);
    if (set_chip ) {
        if (AR_SREV_JUPITER(ah) || AR_SREV_APHRODITE(ah)) {
            OS_REG_WRITE(ah, AR_TIMER_MODE,
                    OS_REG_READ(ah, AR_TIMER_MODE) & 0xFFFFFF00);
            OS_REG_WRITE(ah, AR_GEN_TIMERS2_MODE,
                    OS_REG_READ(ah, AR_GEN_TIMERS2_MODE) & 0xFFFFFF00);
            OS_REG_WRITE(ah, AR_SLP32_INC,
                    OS_REG_READ(ah, AR_SLP32_INC) & 0xFFF00000);
            OS_REG_WRITE(ah, AR_MCI_INTERRUPT_RX_MSG_EN, 0);
            OS_DELAY(100);
        }
        /* Clear the RTC force wake bit to allow the mac to go to sleep */
        OS_REG_CLR_BIT(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_EN);

        if (AR_SREV_JUPITER(ah) || AR_SREV_APHRODITE(ah)) {
            /*
             * In Jupiter, after enter sleep mode, hardware will send
             * a SYS_SLEEPING message through MCI interface. Add a
             * few us delay to make sure the message can reach BT side.
             */
            OS_DELAY(100);
        }

        if (!AR_SREV_JUPITER_10(ah)) {
            /* Shutdown chip. Active low */
            OS_REG_CLR_BIT(ah, AR_RTC_RESET, AR_RTC_RESET_EN);
            /* Settle time */
            OS_DELAY(2);
        }
    }

#if ATH_WOW_OFFLOAD
    if (!AR_SREV_JUPITER(ah) || !HAL_WOW_CTRL(ah, HAL_WOW_OFFLOAD_SET_4004_BIT14))
#endif /* ATH_WOW_OFFLOAD */
    {
        /* Clear Bit 14 of AR_WA after putting chip into Full Sleep mode. */
        OS_REG_WRITE(ah, AR_HOSTIF_REG(ah, AR_WA),
               ahp->ah_wa_reg_val & ~AR_WA_D3_TO_L1_DISABLE);
    }
}
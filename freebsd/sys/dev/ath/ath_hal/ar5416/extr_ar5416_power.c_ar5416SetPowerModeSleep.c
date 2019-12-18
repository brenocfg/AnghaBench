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
struct ath_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_RC ; 
 int AR_RC_AHB ; 
 int AR_RC_HOSTIF ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE_EN ; 
 int /*<<< orphan*/  AR_RTC_RESET ; 
 int /*<<< orphan*/  AR_RTC_RESET_EN ; 
 int /*<<< orphan*/  AR_SREV_HOWL (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_SREV_OWL (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int /*<<< orphan*/  AR_STA_ID1_PWR_SAV ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ar5416SetPowerModeSleep(struct ath_hal *ah, int setChip)
{
	OS_REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_PWR_SAV);
	if (setChip) {
		/* Clear the RTC force wake bit to allow the mac to sleep */
		OS_REG_CLR_BIT(ah, AR_RTC_FORCE_WAKE, AR_RTC_FORCE_WAKE_EN);
		if (! AR_SREV_HOWL(ah))
			OS_REG_WRITE(ah, AR_RC, AR_RC_AHB|AR_RC_HOSTIF);
		/* Shutdown chip. Active low */
		if (! AR_SREV_OWL(ah))
			OS_REG_CLR_BIT(ah, AR_RTC_RESET, AR_RTC_RESET_EN);
	}
}
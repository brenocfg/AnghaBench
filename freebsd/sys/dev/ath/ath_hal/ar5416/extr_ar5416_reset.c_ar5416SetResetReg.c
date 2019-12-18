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
typedef  int uint32_t ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AR_RTC_FORCE_WAKE ; 
 int AR_RTC_FORCE_WAKE_EN ; 
 int AR_RTC_FORCE_WAKE_ON_INT ; 
 int /*<<< orphan*/  HALASSERT (int /*<<< orphan*/ ) ; 
#define  HAL_RESET_COLD 130 
#define  HAL_RESET_POWER_ON 129 
#define  HAL_RESET_WARM 128 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar5416SetReset (struct ath_hal*,int) ; 
 int /*<<< orphan*/  ar5416SetResetPowerOn (struct ath_hal*) ; 

HAL_BOOL
ar5416SetResetReg(struct ath_hal *ah, uint32_t type)
{
	/*
	 * Set force wake
	 */
	OS_REG_WRITE(ah, AR_RTC_FORCE_WAKE,
	    AR_RTC_FORCE_WAKE_EN | AR_RTC_FORCE_WAKE_ON_INT);

	switch (type) {
	case HAL_RESET_POWER_ON:
		return ar5416SetResetPowerOn(ah);
	case HAL_RESET_WARM:
	case HAL_RESET_COLD:
		return ar5416SetReset(ah, type);
	default:
		HALASSERT(AH_FALSE);
		return AH_FALSE;
	}
}
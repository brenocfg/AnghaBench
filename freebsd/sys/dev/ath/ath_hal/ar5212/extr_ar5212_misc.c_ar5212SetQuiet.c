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
typedef  int /*<<< orphan*/  HAL_STATUS ;
typedef  int HAL_QUIET_FLAG ;

/* Variables and functions */
 int /*<<< orphan*/  AR_QUIET1 ; 
 int /*<<< orphan*/  AR_QUIET2 ; 
 int AR_QUIET2_QUIET_DUR_S ; 
 int /*<<< orphan*/  HAL_OK ; 
 int HAL_QUIET_ENABLE ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

HAL_STATUS
ar5212SetQuiet(struct ath_hal *ah, uint32_t period, uint32_t duration,
    uint32_t nextStart, HAL_QUIET_FLAG flag)
{
	OS_REG_WRITE(ah, AR_QUIET2, period | (duration << AR_QUIET2_QUIET_DUR_S));
	if (flag & HAL_QUIET_ENABLE) {
		OS_REG_WRITE(ah, AR_QUIET1, nextStart | (1 << 16));
	}
	else {
		OS_REG_WRITE(ah, AR_QUIET1, nextStart);
	}
	return HAL_OK;
}
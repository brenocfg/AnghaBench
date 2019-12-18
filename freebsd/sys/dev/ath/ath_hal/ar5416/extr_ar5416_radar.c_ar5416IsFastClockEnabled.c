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
struct ath_hal_private {int /*<<< orphan*/  ah_curchan; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_private* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  IS_5GHZ_FAST_CLOCK_EN (struct ath_hal*,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5416IsFastClockEnabled(struct ath_hal *ah)
{
	struct ath_hal_private *ahp = AH_PRIVATE(ah);

	return IS_5GHZ_FAST_CLOCK_EN(ah, ahp->ah_curchan);
}
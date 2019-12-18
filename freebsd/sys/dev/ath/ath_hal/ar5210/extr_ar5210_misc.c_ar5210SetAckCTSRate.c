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
typedef  scalar_t__ u_int ;
struct ath_hal_5210 {int /*<<< orphan*/  ah_staId1Defaults; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_5210* AH5210 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int /*<<< orphan*/  AR_STA_ID1_ACKCTS_6MB ; 
 int /*<<< orphan*/  OS_REG_CLR_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_SET_BIT (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5210SetAckCTSRate(struct ath_hal *ah, u_int high)
{
	struct ath_hal_5210 *ahp = AH5210(ah);

	if (high) {
		OS_REG_CLR_BIT(ah, AR_STA_ID1, AR_STA_ID1_ACKCTS_6MB);
		ahp->ah_staId1Defaults &= ~AR_STA_ID1_ACKCTS_6MB;
	} else {
		OS_REG_SET_BIT(ah, AR_STA_ID1, AR_STA_ID1_ACKCTS_6MB);
		ahp->ah_staId1Defaults |= AR_STA_ID1_ACKCTS_6MB;
	}
	return AH_TRUE;
}
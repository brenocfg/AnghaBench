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
typedef  int /*<<< orphan*/  uint8_t ;
struct ath_hal_5212 {scalar_t__ ah_bssidmask; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_BSSMSKL ; 
 int /*<<< orphan*/  AR_BSSMSKU ; 
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  LE_READ_2 (scalar_t__) ; 
 int /*<<< orphan*/  LE_READ_4 (scalar_t__) ; 
 int /*<<< orphan*/  OS_MEMCPY (scalar_t__,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5212SetBssIdMask(struct ath_hal *ah, const uint8_t *mask)
{
	struct ath_hal_5212 *ahp = AH5212(ah);

	/* save it since it must be rewritten on reset */
	OS_MEMCPY(ahp->ah_bssidmask, mask, IEEE80211_ADDR_LEN);

	OS_REG_WRITE(ah, AR_BSSMSKL, LE_READ_4(ahp->ah_bssidmask));
	OS_REG_WRITE(ah, AR_BSSMSKU, LE_READ_2(ahp->ah_bssidmask + 4));
	return AH_TRUE;
}
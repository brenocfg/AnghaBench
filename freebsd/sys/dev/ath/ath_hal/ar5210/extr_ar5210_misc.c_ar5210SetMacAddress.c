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
struct ath_hal_5210 {int /*<<< orphan*/  ah_macaddr; } ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 struct ath_hal_5210* AH5210 (struct ath_hal*) ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

HAL_BOOL
ar5210SetMacAddress(struct ath_hal *ah, const uint8_t *mac)
{
	struct ath_hal_5210 *ahp = AH5210(ah);

	OS_MEMCPY(ahp->ah_macaddr, mac, IEEE80211_ADDR_LEN);
	return AH_TRUE;
}
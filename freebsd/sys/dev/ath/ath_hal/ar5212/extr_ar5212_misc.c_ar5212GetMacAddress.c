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
struct ath_hal_5212 {int /*<<< orphan*/  ah_macaddr; } ;
struct ath_hal {int dummy; } ;

/* Variables and functions */
 struct ath_hal_5212* AH5212 (struct ath_hal*) ; 
 int /*<<< orphan*/  IEEE80211_ADDR_LEN ; 
 int /*<<< orphan*/  OS_MEMCPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ar5212GetMacAddress(struct ath_hal *ah, uint8_t *mac)
{
	struct ath_hal_5212 *ahp = AH5212(ah);

	OS_MEMCPY(mac, ahp->ah_macaddr, IEEE80211_ADDR_LEN);
}
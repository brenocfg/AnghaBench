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
typedef  int uint16_t ;
struct ath_hal {int dummy; } ;
typedef  int /*<<< orphan*/  HAL_BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  AH_FALSE ; 
 int /*<<< orphan*/  AH_TRUE ; 
 int /*<<< orphan*/  AR_EEP_BMODE ; 
 int IEEE80211_CHAN_2GHZ ; 
 int IEEE80211_CHAN_5GHZ ; 
 scalar_t__ ath_hal_eepromGetFlag (struct ath_hal*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HAL_BOOL
ar5211GetChannelEdges(struct ath_hal *ah,
	uint16_t flags, uint16_t *low, uint16_t *high)
{
	if (flags & IEEE80211_CHAN_5GHZ) {
		*low = 4920;
		*high = 6100;
		return AH_TRUE;
	}
	if (flags & IEEE80211_CHAN_2GHZ &&
	    ath_hal_eepromGetFlag(ah, AR_EEP_BMODE)) {
		*low = 2312;
		*high = 2732;
		return AH_TRUE;
	}
	return AH_FALSE;
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_5__ {struct ieee80211_channel* ah_curchan; } ;
struct TYPE_4__ {int rs_count; int* rs_rates; } ;
typedef  TYPE_1__ HAL_RATE_SET ;

/* Variables and functions */
 struct ieee80211_channel const* AH_NULL ; 
 TYPE_3__* AH_PRIVATE (struct ath_hal*) ; 
 int /*<<< orphan*/  AR_STA_ID1 ; 
 int AR_STA_ID1_BASE_RATE_11B ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_CCK (struct ieee80211_channel const*) ; 
 int OS_REG_READ (struct ath_hal*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OS_REG_WRITE (struct ath_hal*,int /*<<< orphan*/ ,int) ; 

void
ar5212SetBasicRate(struct ath_hal *ah, HAL_RATE_SET *rs)
{
	const struct ieee80211_channel *chan = AH_PRIVATE(ah)->ah_curchan;
	uint32_t reg;
	uint8_t xset;
	int i;

	if (chan == AH_NULL || !IEEE80211_IS_CHAN_CCK(chan))
		return;
	xset = 0;
	for (i = 0; i < rs->rs_count; i++) {
		uint8_t rset = rs->rs_rates[i];
		/* Basic rate defined? */
		if ((rset & 0x80) && (rset &= 0x7f) >= xset)
			xset = rset;
	}
	/*
	 * Set the h/w bit to reflect whether or not the basic
	 * rate is found to be equal or less than 2Mbps.
	 */
	reg = OS_REG_READ(ah, AR_STA_ID1);
	if (xset && xset/2 <= 2)
		OS_REG_WRITE(ah, AR_STA_ID1, reg | AR_STA_ID1_BASE_RATE_11B);
	else
		OS_REG_WRITE(ah, AR_STA_ID1, reg &~ AR_STA_ID1_BASE_RATE_11B);
}
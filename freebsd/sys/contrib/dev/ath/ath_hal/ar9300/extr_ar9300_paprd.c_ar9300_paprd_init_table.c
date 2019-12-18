#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_channel {int dummy; } ;
struct ath_hal {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  paprd_gain_table_index; int /*<<< orphan*/  paprd_gain_table_entries; } ;
typedef  int /*<<< orphan*/  HAL_CHANNEL_INTERNAL ;

/* Variables and functions */
 TYPE_1__* AH9300 (struct ath_hal*) ; 
 scalar_t__ AR_SREV_WASP (struct ath_hal*) ; 
 scalar_t__ IS_CHAN_5GHZ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OS_MEMZERO (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ar9300_gain_table_entries (struct ath_hal*) ; 
 scalar_t__ ar9300_paprd_setup_single_table (struct ath_hal*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/ * ath_hal_checkchannel (struct ath_hal*,struct ieee80211_channel*) ; 

int ar9300_paprd_init_table(struct ath_hal *ah, struct ieee80211_channel * chan)
{
    HAL_CHANNEL_INTERNAL *ichan = ath_hal_checkchannel(ah, chan);

    if ((AR_SREV_WASP(ah) && IS_CHAN_5GHZ(ichan)) ||
         ar9300_paprd_setup_single_table(ah, chan)) {
        goto FAIL;
    }
    OS_MEMZERO(AH9300(ah)->paprd_gain_table_entries,
        sizeof(AH9300(ah)->paprd_gain_table_entries));
    OS_MEMZERO(AH9300(ah)->paprd_gain_table_index,
        sizeof(AH9300(ah)->paprd_gain_table_index));

    ar9300_gain_table_entries(ah);
    return 0;
FAIL:
    return -1;
}
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
typedef  int /*<<< orphan*/  uint32_t ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_2GHZ (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  IWM_PHY_BAND_24 ; 
 int /*<<< orphan*/  IWM_PHY_BAND_5 ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
iwm_mvm_scan_rxon_flags(struct ieee80211_channel *c)
{
	if (IEEE80211_IS_CHAN_2GHZ(c))
		return htole32(IWM_PHY_BAND_24);
	else
		return htole32(IWM_PHY_BAND_5);
}
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
typedef  int uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_DFS ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NOADHOC ; 
 int /*<<< orphan*/  IEEE80211_CHAN_PASSIVE ; 
 int IWM_NVM_CHANNEL_ACTIVE ; 
 int IWM_NVM_CHANNEL_IBSS ; 
 int IWM_NVM_CHANNEL_RADAR ; 

__attribute__((used)) static uint32_t
iwm_eeprom_channel_flags(uint16_t ch_flags)
{
	uint32_t nflags;

	nflags = 0;
	if ((ch_flags & IWM_NVM_CHANNEL_ACTIVE) == 0)
		nflags |= IEEE80211_CHAN_PASSIVE;
	if ((ch_flags & IWM_NVM_CHANNEL_IBSS) == 0)
		nflags |= IEEE80211_CHAN_NOADHOC;
	if (ch_flags & IWM_NVM_CHANNEL_RADAR) {
		nflags |= IEEE80211_CHAN_DFS;
		/* Just in case. */
		nflags |= IEEE80211_CHAN_NOADHOC;
	}

	return (nflags);
}
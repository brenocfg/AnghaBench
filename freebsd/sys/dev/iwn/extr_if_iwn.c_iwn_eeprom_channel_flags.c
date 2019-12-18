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
struct iwn_eeprom_chan {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_DFS ; 
 int /*<<< orphan*/  IEEE80211_CHAN_NOADHOC ; 
 int /*<<< orphan*/  IEEE80211_CHAN_PASSIVE ; 
 int IWN_EEPROM_CHAN_ACTIVE ; 
 int IWN_EEPROM_CHAN_IBSS ; 
 int IWN_EEPROM_CHAN_RADAR ; 

__attribute__((used)) static uint32_t
iwn_eeprom_channel_flags(struct iwn_eeprom_chan *channel)
{
	uint32_t nflags;

	nflags = 0;
	if ((channel->flags & IWN_EEPROM_CHAN_ACTIVE) == 0)
		nflags |= IEEE80211_CHAN_PASSIVE;
	if ((channel->flags & IWN_EEPROM_CHAN_IBSS) == 0)
		nflags |= IEEE80211_CHAN_NOADHOC;
	if (channel->flags & IWN_EEPROM_CHAN_RADAR) {
		nflags |= IEEE80211_CHAN_DFS;
		/* XXX apparently IBSS may still be marked */
		nflags |= IEEE80211_CHAN_NOADHOC;
	}

	return nflags;
}
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
typedef  int uint32_t ;
struct wpi_eeprom_chan {int flags; } ;

/* Variables and functions */
 int IEEE80211_CHAN_DFS ; 
 int IEEE80211_CHAN_NOADHOC ; 
 int IEEE80211_CHAN_NOHOSTAP ; 
 int IEEE80211_CHAN_PASSIVE ; 
 int WPI_EEPROM_CHAN_ACTIVE ; 
 int WPI_EEPROM_CHAN_IBSS ; 
 int WPI_EEPROM_CHAN_RADAR ; 

__attribute__((used)) static uint32_t
wpi_eeprom_channel_flags(struct wpi_eeprom_chan *channel)
{
	uint32_t nflags;

	nflags = 0;
	if ((channel->flags & WPI_EEPROM_CHAN_ACTIVE) == 0)
		nflags |= IEEE80211_CHAN_PASSIVE;
	if ((channel->flags & WPI_EEPROM_CHAN_IBSS) == 0)
		nflags |= IEEE80211_CHAN_NOADHOC;
	if (channel->flags & WPI_EEPROM_CHAN_RADAR) {
		nflags |= IEEE80211_CHAN_DFS;
		/* XXX apparently IBSS may still be marked */
		nflags |= IEEE80211_CHAN_NOADHOC;
	}

	/* XXX HOSTAP uses WPI_MODE_IBSS */
	if (nflags & IEEE80211_CHAN_NOADHOC)
		nflags |= IEEE80211_CHAN_NOHOSTAP;

	return nflags;
}
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
typedef  int uint8_t ;

/* Variables and functions */
 int IEEE80211_CHANSTATE_CACDONE ; 
 int IEEE80211_CHANSTATE_CWINT ; 
 int IEEE80211_CHANSTATE_NORADAR ; 
 int IEEE80211_CHANSTATE_RADAR ; 
 int WlanIfaceChannelStateType_cacDone ; 
 int WlanIfaceChannelStateType_interferenceDetected ; 
 int WlanIfaceChannelStateType_radar ; 
 int WlanIfaceChannelStateType_radarClear ; 

uint8_t
wlan_channel_state_to_snmp(uint8_t cstate)
{
	uint8_t cs = 0;

	if ((cstate & IEEE80211_CHANSTATE_RADAR) != 0)
		cs |= (0x1 << WlanIfaceChannelStateType_radar);
	if ((cstate & IEEE80211_CHANSTATE_CACDONE) != 0)
		cs |= (0x1 << WlanIfaceChannelStateType_cacDone);
	if ((cstate & IEEE80211_CHANSTATE_CWINT) != 0)
		cs |= (0x1 << WlanIfaceChannelStateType_interferenceDetected);
	if ((cstate & IEEE80211_CHANSTATE_NORADAR) != 0)
		cs |= (0x1 << WlanIfaceChannelStateType_radarClear);

	return (cs);
}
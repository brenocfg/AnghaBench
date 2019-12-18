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

/* Variables and functions */
 int IEEE80211_CAPINFO_CF_POLLABLE ; 
 int IEEE80211_CAPINFO_CF_POLLREQ ; 
 int IEEE80211_CAPINFO_CHNL_AGILITY ; 
 int IEEE80211_CAPINFO_DSSSOFDM ; 
 int IEEE80211_CAPINFO_ESS ; 
 int IEEE80211_CAPINFO_IBSS ; 
 int IEEE80211_CAPINFO_PBCC ; 
 int IEEE80211_CAPINFO_PRIVACY ; 
 int IEEE80211_CAPINFO_RSN ; 
 int IEEE80211_CAPINFO_SHORT_PREAMBLE ; 
 int IEEE80211_CAPINFO_SHORT_SLOTTIME ; 
 int WlanPeerCapabilityFlags_cfPollRequest ; 
 int WlanPeerCapabilityFlags_cfPollable ; 
 int WlanPeerCapabilityFlags_channelAgility ; 
 int WlanPeerCapabilityFlags_dsssofdm ; 
 int WlanPeerCapabilityFlags_ess ; 
 int WlanPeerCapabilityFlags_ibss ; 
 int WlanPeerCapabilityFlags_pbcc ; 
 int WlanPeerCapabilityFlags_privacy ; 
 int WlanPeerCapabilityFlags_rsn ; 
 int WlanPeerCapabilityFlags_shortPreamble ; 
 int WlanPeerCapabilityFlags_shortSlotTime ; 

__attribute__((used)) static uint32_t
wlan_peercaps_to_snmp(uint32_t pcaps)
{
	uint32_t scaps = 0;

	if ((pcaps & IEEE80211_CAPINFO_ESS) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_ess);
	if ((pcaps & IEEE80211_CAPINFO_IBSS) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_ibss);
	if ((pcaps & IEEE80211_CAPINFO_CF_POLLABLE) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_cfPollable);
	if ((pcaps & IEEE80211_CAPINFO_CF_POLLREQ) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_cfPollRequest);
	if ((pcaps & IEEE80211_CAPINFO_PRIVACY) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_privacy);
	if ((pcaps & IEEE80211_CAPINFO_SHORT_PREAMBLE) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_shortPreamble);
	if ((pcaps & IEEE80211_CAPINFO_PBCC) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_pbcc);
	if ((pcaps & IEEE80211_CAPINFO_CHNL_AGILITY) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_channelAgility);
	if ((pcaps & IEEE80211_CAPINFO_SHORT_SLOTTIME) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_shortSlotTime);
	if ((pcaps & IEEE80211_CAPINFO_RSN) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_rsn);
	if ((pcaps & IEEE80211_CAPINFO_DSSSOFDM) != 0)
		scaps |= (0x1 << WlanPeerCapabilityFlags_dsssofdm);

	return (scaps);
}
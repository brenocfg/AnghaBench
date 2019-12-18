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
 int IEEE80211_CHAN_11D ; 
 int IEEE80211_CHAN_2GHZ ; 
 int IEEE80211_CHAN_4MSXMIT ; 
 int IEEE80211_CHAN_5GHZ ; 
 int IEEE80211_CHAN_CCK ; 
 int IEEE80211_CHAN_DFS ; 
 int IEEE80211_CHAN_DYN ; 
 int IEEE80211_CHAN_GFSK ; 
 int IEEE80211_CHAN_GSM ; 
 int IEEE80211_CHAN_HALF ; 
 int IEEE80211_CHAN_HT20 ; 
 int IEEE80211_CHAN_HT40D ; 
 int IEEE80211_CHAN_HT40U ; 
 int IEEE80211_CHAN_NOADHOC ; 
 int IEEE80211_CHAN_NOHOSTAP ; 
 int IEEE80211_CHAN_OFDM ; 
 int IEEE80211_CHAN_PASSIVE ; 
 int IEEE80211_CHAN_QUARTER ; 
 int IEEE80211_CHAN_STURBO ; 
 int IEEE80211_CHAN_TURBO ; 
 int WlanIfaceChannelFlagsType_cck ; 
 int WlanIfaceChannelFlagsType_dfs ; 
 int WlanIfaceChannelFlagsType_dot11aStaticTurbo ; 
 int WlanIfaceChannelFlagsType_dot11d ; 
 int WlanIfaceChannelFlagsType_dynamicCckOfdm ; 
 int WlanIfaceChannelFlagsType_gfsk ; 
 int WlanIfaceChannelFlagsType_halfRate ; 
 int WlanIfaceChannelFlagsType_ht20 ; 
 int WlanIfaceChannelFlagsType_ht40d ; 
 int WlanIfaceChannelFlagsType_ht40u ; 
 int WlanIfaceChannelFlagsType_noAdhoc ; 
 int WlanIfaceChannelFlagsType_noHostAp ; 
 int WlanIfaceChannelFlagsType_ofdm ; 
 int WlanIfaceChannelFlagsType_passiveScan ; 
 int WlanIfaceChannelFlagsType_quarterRate ; 
 int WlanIfaceChannelFlagsType_spectrum2Ghz ; 
 int WlanIfaceChannelFlagsType_spectrum5Ghz ; 
 int WlanIfaceChannelFlagsType_spectrum900Mhz ; 
 int WlanIfaceChannelFlagsType_turbo ; 
 int WlanIfaceChannelFlagsType_xmit4ms ; 

uint32_t
wlan_channel_flags_to_snmp(uint32_t cflags)
{
	uint32_t cf = 0;

	if ((cflags & IEEE80211_CHAN_TURBO) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_turbo);
	if ((cflags & IEEE80211_CHAN_CCK) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_cck);
	if ((cflags & IEEE80211_CHAN_OFDM) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_ofdm);
	if ((cflags & IEEE80211_CHAN_2GHZ) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_spectrum2Ghz);
	if ((cflags & IEEE80211_CHAN_5GHZ) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_spectrum5Ghz);
	if ((cflags & IEEE80211_CHAN_PASSIVE) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_passiveScan);
	if ((cflags & IEEE80211_CHAN_DYN) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_dynamicCckOfdm);
	if ((cflags & IEEE80211_CHAN_GFSK) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_gfsk);
	if ((cflags & IEEE80211_CHAN_GSM) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_spectrum900Mhz);
	if ((cflags & IEEE80211_CHAN_STURBO) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_dot11aStaticTurbo);
	if ((cflags & IEEE80211_CHAN_HALF) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_halfRate);
	if ((cflags & IEEE80211_CHAN_QUARTER) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_quarterRate);
	if ((cflags & IEEE80211_CHAN_HT20) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_ht20);
	if ((cflags & IEEE80211_CHAN_HT40U) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_ht40u);
	if ((cflags & IEEE80211_CHAN_HT40D) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_ht40d);
	if ((cflags & IEEE80211_CHAN_DFS) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_dfs);
	if ((cflags & IEEE80211_CHAN_4MSXMIT) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_xmit4ms);
	if ((cflags & IEEE80211_CHAN_NOADHOC) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_noAdhoc);
	if ((cflags & IEEE80211_CHAN_NOHOSTAP) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_noHostAp);
	if ((cflags & IEEE80211_CHAN_11D) != 0)
		cf |= (0x1 << WlanIfaceChannelFlagsType_dot11d);

	return (cf);
}
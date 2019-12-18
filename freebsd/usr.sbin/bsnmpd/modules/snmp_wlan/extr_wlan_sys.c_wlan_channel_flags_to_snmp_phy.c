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
typedef  enum WlanIfPhyMode { ____Placeholder_WlanIfPhyMode } WlanIfPhyMode ;

/* Variables and functions */
 int IEEE80211_CHAN_A ; 
 int IEEE80211_CHAN_B ; 
 int IEEE80211_CHAN_FHSS ; 
 int IEEE80211_CHAN_G ; 
 int IEEE80211_CHAN_HALF ; 
 int IEEE80211_CHAN_PUREG ; 
 int IEEE80211_CHAN_QUARTER ; 
 int IEEE80211_CHAN_STURBO ; 
 int IEEE80211_CHAN_TURBO ; 
 int WlanIfPhyMode_auto ; 
 int WlanIfPhyMode_dot11a ; 
 int WlanIfPhyMode_dot11b ; 
 int WlanIfPhyMode_dot11g ; 
 int WlanIfPhyMode_fh ; 
 int WlanIfPhyMode_ofdmHalf ; 
 int WlanIfPhyMode_ofdmQuarter ; 
 int WlanIfPhyMode_sturboA ; 
 int WlanIfPhyMode_turboA ; 
 int WlanIfPhyMode_turboG ; 

__attribute__((used)) static enum WlanIfPhyMode
wlan_channel_flags_to_snmp_phy(uint32_t cflags)
{
	/* XXX: recheck */
	if ((cflags & IEEE80211_CHAN_A) != 0)
		return (WlanIfPhyMode_dot11a);
	if ((cflags & IEEE80211_CHAN_B) != 0)
		return (WlanIfPhyMode_dot11b);
	if ((cflags & IEEE80211_CHAN_G) != 0 ||
	    (cflags & IEEE80211_CHAN_PUREG) != 0)
		return (WlanIfPhyMode_dot11g);
	if ((cflags & IEEE80211_CHAN_FHSS) != 0)
		return (WlanIfPhyMode_fh);
	if ((cflags & IEEE80211_CHAN_TURBO) != 0 &&
	    (cflags & IEEE80211_CHAN_A) != 0)
		return (WlanIfPhyMode_turboA);
	if ((cflags & IEEE80211_CHAN_TURBO) != 0 &&
	    (cflags & IEEE80211_CHAN_G) != 0)
		return (WlanIfPhyMode_turboG);
	if ((cflags & IEEE80211_CHAN_STURBO) != 0)
		return (WlanIfPhyMode_sturboA);
	if ((cflags & IEEE80211_CHAN_HALF) != 0)
		return (WlanIfPhyMode_ofdmHalf);
	if ((cflags & IEEE80211_CHAN_QUARTER) != 0)
		return (WlanIfPhyMode_ofdmQuarter);

	return (WlanIfPhyMode_auto);
}
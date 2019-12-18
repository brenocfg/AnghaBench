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
 int IEEE80211_C_8023ENCAP ; 
 int IEEE80211_C_AHDEMO ; 
 int IEEE80211_C_BGSCAN ; 
 int IEEE80211_C_BURST ; 
 int IEEE80211_C_DFS ; 
 int IEEE80211_C_FF ; 
 int IEEE80211_C_HOSTAP ; 
 int IEEE80211_C_IBSS ; 
 int IEEE80211_C_MBSS ; 
 int IEEE80211_C_MONITOR ; 
 int IEEE80211_C_PMGT ; 
 int IEEE80211_C_SHPREAMBLE ; 
 int IEEE80211_C_SHSLOT ; 
 int IEEE80211_C_STA ; 
 int IEEE80211_C_SWRETRY ; 
 int IEEE80211_C_TDMA ; 
 int IEEE80211_C_TURBOP ; 
 int IEEE80211_C_TXFRAG ; 
 int IEEE80211_C_TXPMGT ; 
 int IEEE80211_C_WDS ; 
 int IEEE80211_C_WME ; 
 int IEEE80211_C_WPA1 ; 
 int IEEE80211_C_WPA2 ; 
 int WlanDriverCaps_ahDemo ; 
 int WlanDriverCaps_athFastFrames ; 
 int WlanDriverCaps_athTurbo ; 
 int WlanDriverCaps_bgScan ; 
 int WlanDriverCaps_burst ; 
 int WlanDriverCaps_dfs ; 
 int WlanDriverCaps_hostAp ; 
 int WlanDriverCaps_ibss ; 
 int WlanDriverCaps_ieee8023encap ; 
 int WlanDriverCaps_mbss ; 
 int WlanDriverCaps_monitor ; 
 int WlanDriverCaps_pmgt ; 
 int WlanDriverCaps_shortPreamble ; 
 int WlanDriverCaps_shortSlot ; 
 int WlanDriverCaps_station ; 
 int WlanDriverCaps_swRetry ; 
 int WlanDriverCaps_tdma ; 
 int WlanDriverCaps_txFrag ; 
 int WlanDriverCaps_txPmgt ; 
 int WlanDriverCaps_wds ; 
 int WlanDriverCaps_wme ; 
 int WlanDriverCaps_wpa1 ; 
 int WlanDriverCaps_wpa2 ; 

__attribute__((used)) static uint32_t
wlan_drivercaps_to_snmp(uint32_t dcaps)
{
	uint32_t scaps = 0;

	if ((dcaps & IEEE80211_C_STA) != 0)
		scaps |= (0x1 << WlanDriverCaps_station);
	if ((dcaps & IEEE80211_C_8023ENCAP) != 0)
		scaps |= (0x1 << WlanDriverCaps_ieee8023encap);
	if ((dcaps & IEEE80211_C_FF) != 0)
		scaps |= (0x1 << WlanDriverCaps_athFastFrames);
	if ((dcaps & IEEE80211_C_TURBOP) != 0)
		scaps |= (0x1 << WlanDriverCaps_athTurbo);
	if ((dcaps & IEEE80211_C_IBSS) != 0)
		scaps |= (0x1 << WlanDriverCaps_ibss);
	if ((dcaps & IEEE80211_C_PMGT) != 0)
		scaps |= (0x1 << WlanDriverCaps_pmgt);
	if ((dcaps & IEEE80211_C_HOSTAP) != 0)
		scaps |= (0x1 << WlanDriverCaps_hostAp);
	if ((dcaps & IEEE80211_C_AHDEMO) != 0)
		scaps |= (0x1 << WlanDriverCaps_ahDemo);
	if ((dcaps & IEEE80211_C_SWRETRY) != 0)
		scaps |= (0x1 << WlanDriverCaps_swRetry);
	if ((dcaps & IEEE80211_C_TXPMGT) != 0)
		scaps |= (0x1 << WlanDriverCaps_txPmgt);
	if ((dcaps & IEEE80211_C_SHSLOT) != 0)
		scaps |= (0x1 << WlanDriverCaps_shortSlot);
	if ((dcaps & IEEE80211_C_SHPREAMBLE) != 0)
		scaps |= (0x1 << WlanDriverCaps_shortPreamble);
	if ((dcaps & IEEE80211_C_MONITOR) != 0)
		scaps |= (0x1 << WlanDriverCaps_monitor);
	if ((dcaps & IEEE80211_C_DFS) != 0)
		scaps |= (0x1 << WlanDriverCaps_dfs);
	if ((dcaps & IEEE80211_C_MBSS) != 0)
		scaps |= (0x1 << WlanDriverCaps_mbss);
	if ((dcaps & IEEE80211_C_WPA1) != 0)
		scaps |= (0x1 << WlanDriverCaps_wpa1);
	if ((dcaps & IEEE80211_C_WPA2) != 0)
		scaps |= (0x1 << WlanDriverCaps_wpa2);
	if ((dcaps & IEEE80211_C_BURST) != 0)
		scaps |= (0x1 << WlanDriverCaps_burst);
	if ((dcaps & IEEE80211_C_WME) != 0)
		scaps |= (0x1 << WlanDriverCaps_wme);
	if ((dcaps & IEEE80211_C_WDS) != 0)
		scaps |= (0x1 << WlanDriverCaps_wds);
	if ((dcaps & IEEE80211_C_BGSCAN) != 0)
		scaps |= (0x1 << WlanDriverCaps_bgScan);
	if ((dcaps & IEEE80211_C_TXFRAG) != 0)
		scaps |= (0x1 << WlanDriverCaps_txFrag);
	if ((dcaps & IEEE80211_C_TDMA) != 0)
		scaps |= (0x1 << WlanDriverCaps_tdma);

	return (scaps);
}
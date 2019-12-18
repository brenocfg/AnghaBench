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

/* Variables and functions */
 int IEEE80211_IOC_AMPDU ; 
 int IEEE80211_IOC_AMPDU_DENSITY ; 
 int IEEE80211_IOC_AMPDU_LIMIT ; 
 int IEEE80211_IOC_AMSDU ; 
 int IEEE80211_IOC_AMSDU_LIMIT ; 
 int IEEE80211_IOC_APBRIDGE ; 
 int IEEE80211_IOC_BEACON_INTERVAL ; 
 int IEEE80211_IOC_BGSCAN ; 
 int IEEE80211_IOC_BGSCAN_IDLE ; 
 int IEEE80211_IOC_BGSCAN_INTERVAL ; 
 int IEEE80211_IOC_BMISSTHRESHOLD ; 
 int IEEE80211_IOC_BSSID ; 
 int IEEE80211_IOC_BURST ; 
 int IEEE80211_IOC_CURCHAN ; 
 int IEEE80211_IOC_DFS ; 
 int IEEE80211_IOC_DOTD ; 
 int IEEE80211_IOC_DOTH ; 
 int IEEE80211_IOC_DTIM_PERIOD ; 
 int IEEE80211_IOC_DWDS ; 
 int IEEE80211_IOC_FF ; 
 int IEEE80211_IOC_FRAGTHRESHOLD ; 
 int IEEE80211_IOC_HIDESSID ; 
 int IEEE80211_IOC_HTCOMPAT ; 
 int IEEE80211_IOC_HTCONF ; 
 int IEEE80211_IOC_HTPROTMODE ; 
 int IEEE80211_IOC_INACTIVITY ; 
 int IEEE80211_IOC_POWERSAVE ; 
 int IEEE80211_IOC_PROTMODE ; 
 int IEEE80211_IOC_PUREG ; 
 int IEEE80211_IOC_PUREN ; 
 int IEEE80211_IOC_REGDOMAIN ; 
 int IEEE80211_IOC_RIFS ; 
 int IEEE80211_IOC_ROAMING ; 
 int IEEE80211_IOC_RTSTHRESHOLD ; 
 int IEEE80211_IOC_SHORTGI ; 
 int IEEE80211_IOC_SMPS ; 
 int IEEE80211_IOC_SSID ; 
 int IEEE80211_IOC_TDMA_BINTERVAL ; 
 int IEEE80211_IOC_TDMA_SLOT ; 
 int IEEE80211_IOC_TDMA_SLOTCNT ; 
 int IEEE80211_IOC_TDMA_SLOTLEN ; 
 int IEEE80211_IOC_TURBOP ; 
 int IEEE80211_IOC_TXPOWER ; 
 int IEEE80211_IOC_WPS ; 
#define  LEAF_wlanIfaceApBridge 172 
#define  LEAF_wlanIfaceBeaconInterval 171 
#define  LEAF_wlanIfaceBeaconMissedThreshold 170 
#define  LEAF_wlanIfaceBgScan 169 
#define  LEAF_wlanIfaceBgScanIdle 168 
#define  LEAF_wlanIfaceBgScanInterval 167 
#define  LEAF_wlanIfaceCountryCode 166 
#define  LEAF_wlanIfaceDesiredBssid 165 
#define  LEAF_wlanIfaceDesiredChannel 164 
#define  LEAF_wlanIfaceDesiredSsid 163 
#define  LEAF_wlanIfaceDot11d 162 
#define  LEAF_wlanIfaceDot11gProtMode 161 
#define  LEAF_wlanIfaceDot11gPureMode 160 
#define  LEAF_wlanIfaceDot11h 159 
#define  LEAF_wlanIfaceDot11nAmpdu 158 
#define  LEAF_wlanIfaceDot11nAmpduDensity 157 
#define  LEAF_wlanIfaceDot11nAmpduLimit 156 
#define  LEAF_wlanIfaceDot11nAmsdu 155 
#define  LEAF_wlanIfaceDot11nAmsduLimit 154 
#define  LEAF_wlanIfaceDot11nHTCompatible 153 
#define  LEAF_wlanIfaceDot11nHTProtMode 152 
#define  LEAF_wlanIfaceDot11nHighThroughput 151 
#define  LEAF_wlanIfaceDot11nPureMode 150 
#define  LEAF_wlanIfaceDot11nRIFS 149 
#define  LEAF_wlanIfaceDot11nSMPSMode 148 
#define  LEAF_wlanIfaceDot11nShortGI 147 
#define  LEAF_wlanIfaceDtimPeriod 146 
#define  LEAF_wlanIfaceDturbo 145 
#define  LEAF_wlanIfaceDynamicFreqSelection 144 
#define  LEAF_wlanIfaceDynamicWds 143 
#define  LEAF_wlanIfaceFastFrames 142 
#define  LEAF_wlanIfaceFragmentThreshold 141 
#define  LEAF_wlanIfaceHideSsid 140 
#define  LEAF_wlanIfaceInactivityProccess 139 
#define  LEAF_wlanIfacePacketBurst 138 
#define  LEAF_wlanIfacePowerSave 137 
#define  LEAF_wlanIfaceRTSThreshold 136 
#define  LEAF_wlanIfaceRegDomain 135 
#define  LEAF_wlanIfaceRoamingMode 134 
#define  LEAF_wlanIfaceTdmaBeaconInterval 133 
#define  LEAF_wlanIfaceTdmaSlot 132 
#define  LEAF_wlanIfaceTdmaSlotCount 131 
#define  LEAF_wlanIfaceTdmaSlotLength 130 
#define  LEAF_wlanIfaceTxPower 129 
#define  LEAF_wlanIfaceWlanPrivacySubscribe 128 

__attribute__((used)) static int
wlan_config_snmp2ioctl(int which)
{
	int op;

	switch (which) {
	case LEAF_wlanIfacePacketBurst:
		op = IEEE80211_IOC_BURST;
		break;
	case LEAF_wlanIfaceCountryCode:
		op = IEEE80211_IOC_REGDOMAIN;
		break;
	case LEAF_wlanIfaceRegDomain:
		op = IEEE80211_IOC_REGDOMAIN;
		break;
	case LEAF_wlanIfaceDesiredSsid:
		op = IEEE80211_IOC_SSID;
		break;
	case LEAF_wlanIfaceDesiredChannel:
		op = IEEE80211_IOC_CURCHAN;
		break;
	case LEAF_wlanIfaceDynamicFreqSelection:
		op = IEEE80211_IOC_DFS;
		break;
	case LEAF_wlanIfaceFastFrames:
		op = IEEE80211_IOC_FF;
		break;
	case LEAF_wlanIfaceDturbo:
		op = IEEE80211_IOC_TURBOP;
		break;
	case LEAF_wlanIfaceTxPower:
		op = IEEE80211_IOC_TXPOWER;
		break;
	case LEAF_wlanIfaceFragmentThreshold:
		op = IEEE80211_IOC_FRAGTHRESHOLD;
		break;
	case LEAF_wlanIfaceRTSThreshold:
		op = IEEE80211_IOC_RTSTHRESHOLD;
		break;
	case LEAF_wlanIfaceWlanPrivacySubscribe:
		op = IEEE80211_IOC_WPS;
		break;
	case LEAF_wlanIfaceBgScan:
		op = IEEE80211_IOC_BGSCAN;
		break;
	case LEAF_wlanIfaceBgScanIdle:
		op = IEEE80211_IOC_BGSCAN_IDLE;
		break;
	case LEAF_wlanIfaceBgScanInterval:
		op = IEEE80211_IOC_BGSCAN_INTERVAL;
		break;
	case LEAF_wlanIfaceBeaconMissedThreshold:
		op = IEEE80211_IOC_BMISSTHRESHOLD;
		break;
	case LEAF_wlanIfaceDesiredBssid:
		op = IEEE80211_IOC_BSSID;
		break;
	case LEAF_wlanIfaceRoamingMode:
		op = IEEE80211_IOC_ROAMING;
		break;
	case LEAF_wlanIfaceDot11d:
		op = IEEE80211_IOC_DOTD;
		break;
	case LEAF_wlanIfaceDot11h:
		op = IEEE80211_IOC_DOTH;
		break;
	case LEAF_wlanIfaceDynamicWds:
		op = IEEE80211_IOC_DWDS;
		break;
	case LEAF_wlanIfacePowerSave:
		op = IEEE80211_IOC_POWERSAVE;
		break;
	case LEAF_wlanIfaceApBridge:
		op = IEEE80211_IOC_APBRIDGE;
		break;
	case LEAF_wlanIfaceBeaconInterval:
		op = IEEE80211_IOC_BEACON_INTERVAL;
		break;
	case LEAF_wlanIfaceDtimPeriod:
		op = IEEE80211_IOC_DTIM_PERIOD;
		break;
	case LEAF_wlanIfaceHideSsid:
		op = IEEE80211_IOC_HIDESSID;
		break;
	case LEAF_wlanIfaceInactivityProccess:
		op = IEEE80211_IOC_INACTIVITY;
		break;
	case LEAF_wlanIfaceDot11gProtMode:
		op = IEEE80211_IOC_PROTMODE;
		break;
	case LEAF_wlanIfaceDot11gPureMode:
		op = IEEE80211_IOC_PUREG;
		break;
	case LEAF_wlanIfaceDot11nPureMode:
		op = IEEE80211_IOC_PUREN;
		break;
	case LEAF_wlanIfaceDot11nAmpdu:
		op = IEEE80211_IOC_AMPDU;
		break;
	case LEAF_wlanIfaceDot11nAmpduDensity:
		op = IEEE80211_IOC_AMPDU_DENSITY;
		break;
	case LEAF_wlanIfaceDot11nAmpduLimit:
		op = IEEE80211_IOC_AMPDU_LIMIT;
		break;
	case LEAF_wlanIfaceDot11nAmsdu:
		op = IEEE80211_IOC_AMSDU;
		break;
	case LEAF_wlanIfaceDot11nAmsduLimit:
		op = IEEE80211_IOC_AMSDU_LIMIT;
		break;
	case LEAF_wlanIfaceDot11nHighThroughput:
		op = IEEE80211_IOC_HTCONF;
		break;
	case LEAF_wlanIfaceDot11nHTCompatible:
		op = IEEE80211_IOC_HTCOMPAT;
		break;
	case LEAF_wlanIfaceDot11nHTProtMode:
		op = IEEE80211_IOC_HTPROTMODE;
		break;
	case LEAF_wlanIfaceDot11nRIFS:
		op = IEEE80211_IOC_RIFS;
		break;
	case LEAF_wlanIfaceDot11nShortGI:
		op = IEEE80211_IOC_SHORTGI;
		break;
	case LEAF_wlanIfaceDot11nSMPSMode:
		op = IEEE80211_IOC_SMPS;
		break;
	case LEAF_wlanIfaceTdmaSlot:
		op = IEEE80211_IOC_TDMA_SLOT;
		break;
	case LEAF_wlanIfaceTdmaSlotCount:
		op = IEEE80211_IOC_TDMA_SLOTCNT;
		break;
	case LEAF_wlanIfaceTdmaSlotLength:
		op = IEEE80211_IOC_TDMA_SLOTLEN;
		break;
	case LEAF_wlanIfaceTdmaBeaconInterval:
		op = IEEE80211_IOC_TDMA_BINTERVAL;
		break;
	default:
		op = -1;
	}

	return (op);
}
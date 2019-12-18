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
 int IEEE80211_BINTVAL_MAX ; 
 int IEEE80211_BINTVAL_MIN ; 
 int IEEE80211_DTIM_MAX ; 
 int IEEE80211_DTIM_MIN ; 
 int IEEE80211_FRAG_MAX ; 
 int IEEE80211_FRAG_MIN ; 
 int IEEE80211_HTCAP_MAXAMSDU_3839 ; 
 int IEEE80211_HTCAP_MAXAMSDU_7935 ; 
 int IEEE80211_HTCAP_MAXRXAMPDU_16K ; 
 int IEEE80211_HTCAP_MAXRXAMPDU_32K ; 
 int IEEE80211_HTCAP_MAXRXAMPDU_64K ; 
 int IEEE80211_HTCAP_MAXRXAMPDU_8K ; 
 int IEEE80211_HTCAP_MPDUDENSITY_025 ; 
 int IEEE80211_HTCAP_MPDUDENSITY_05 ; 
 int IEEE80211_HTCAP_MPDUDENSITY_1 ; 
 int IEEE80211_HTCAP_MPDUDENSITY_16 ; 
 int IEEE80211_HTCAP_MPDUDENSITY_2 ; 
 int IEEE80211_HTCAP_MPDUDENSITY_4 ; 
 int IEEE80211_HTCAP_MPDUDENSITY_8 ; 
 int IEEE80211_HTCAP_MPDUDENSITY_NA ; 
 int IEEE80211_HTCAP_SHORTGI20 ; 
 int IEEE80211_HTCAP_SHORTGI40 ; 
 int IEEE80211_HTCAP_SMPS_DYNAMIC ; 
 int IEEE80211_HTCAP_SMPS_ENA ; 
 int IEEE80211_HTCAP_SMPS_OFF ; 
 int IEEE80211_HWBMISS_MAX ; 
 int IEEE80211_HWBMISS_MIN ; 
#define  IEEE80211_IOC_AMPDU 186 
#define  IEEE80211_IOC_AMPDU_DENSITY 185 
#define  IEEE80211_IOC_AMPDU_LIMIT 184 
#define  IEEE80211_IOC_AMSDU 183 
#define  IEEE80211_IOC_AMSDU_LIMIT 182 
#define  IEEE80211_IOC_APBRIDGE 181 
#define  IEEE80211_IOC_BEACON_INTERVAL 180 
#define  IEEE80211_IOC_BGSCAN 179 
#define  IEEE80211_IOC_BGSCAN_IDLE 178 
#define  IEEE80211_IOC_BGSCAN_INTERVAL 177 
#define  IEEE80211_IOC_BMISSTHRESHOLD 176 
#define  IEEE80211_IOC_BSSID 175 
#define  IEEE80211_IOC_BURST 174 
#define  IEEE80211_IOC_CURCHAN 173 
#define  IEEE80211_IOC_DFS 172 
#define  IEEE80211_IOC_DOTD 171 
#define  IEEE80211_IOC_DOTH 170 
#define  IEEE80211_IOC_DTIM_PERIOD 169 
#define  IEEE80211_IOC_DWDS 168 
#define  IEEE80211_IOC_FF 167 
#define  IEEE80211_IOC_FRAGTHRESHOLD 166 
#define  IEEE80211_IOC_HIDESSID 165 
#define  IEEE80211_IOC_HTCOMPAT 164 
#define  IEEE80211_IOC_HTCONF 163 
#define  IEEE80211_IOC_HTPROTMODE 162 
#define  IEEE80211_IOC_INACTIVITY 161 
#define  IEEE80211_IOC_POWERSAVE 160 
#define  IEEE80211_IOC_PROTMODE 159 
#define  IEEE80211_IOC_PUREG 158 
#define  IEEE80211_IOC_PUREN 157 
#define  IEEE80211_IOC_REGDOMAIN 156 
#define  IEEE80211_IOC_RIFS 155 
#define  IEEE80211_IOC_ROAMING 154 
#define  IEEE80211_IOC_RTSTHRESHOLD 153 
#define  IEEE80211_IOC_SHORTGI 152 
#define  IEEE80211_IOC_SMPS 151 
#define  IEEE80211_IOC_SSID 150 
#define  IEEE80211_IOC_TDMA_BINTERVAL 149 
#define  IEEE80211_IOC_TDMA_SLOT 148 
#define  IEEE80211_IOC_TDMA_SLOTCNT 147 
#define  IEEE80211_IOC_TDMA_SLOTLEN 146 
#define  IEEE80211_IOC_TURBOP 145 
#define  IEEE80211_IOC_TXPOWER 144 
#define  IEEE80211_IOC_WPS 143 
 int IEEE80211_PROTMODE_CTS ; 
 int IEEE80211_PROTMODE_OFF ; 
 int IEEE80211_PROTMODE_RTSCTS ; 
 int IEEE80211_ROAMING_AUTO ; 
 int IEEE80211_ROAMING_DEVICE ; 
 int IEEE80211_ROAMING_MANUAL ; 
 int IEEE80211_RTS_MAX ; 
 int IEEE80211_RTS_MIN ; 
 int SNMP_ERR_INCONS_VALUE ; 
 int SNMP_ERR_NOERROR ; 
 int TruthValue_false ; 
 int TruthValue_true ; 
 int WLAN_BGSCAN_IDLE_MIN ; 
 int WLAN_SCAN_VALID_MIN ; 
 int WLAN_TDMA_MAXSLOTS ; 
#define  WlanIfaceDot11nPduType_disabled 142 
#define  WlanIfaceDot11nPduType_rxOnly 141 
#define  WlanIfaceDot11nPduType_txAndRx 140 
#define  WlanIfaceDot11nPduType_txOnly 139 
#define  wlanIfaceDot11gProtMode_cts 138 
#define  wlanIfaceDot11gProtMode_off 137 
#define  wlanIfaceDot11gProtMode_rtscts 136 
#define  wlanIfaceDot11nHTProtMode_off 135 
#define  wlanIfaceDot11nHTProtMode_rts 134 
#define  wlanIfaceDot11nSMPSMode_disabled 133 
#define  wlanIfaceDot11nSMPSMode_dynamic 132 
#define  wlanIfaceDot11nSMPSMode_static 131 
#define  wlanIfaceRoamingMode_auto 130 
#define  wlanIfaceRoamingMode_device 129 
#define  wlanIfaceRoamingMode_manual 128 

__attribute__((used)) static int
wlan_config_snmp2value(int which, int sval, int *value)
{
	*value = 0;

	switch (which) {
	case IEEE80211_IOC_BURST:
	case IEEE80211_IOC_DFS:
	case IEEE80211_IOC_FF:
	case IEEE80211_IOC_TURBOP:
	case IEEE80211_IOC_WPS:
	case IEEE80211_IOC_BGSCAN:
	case IEEE80211_IOC_DOTD:
	case IEEE80211_IOC_DOTH:
	case IEEE80211_IOC_DWDS:
	case IEEE80211_IOC_POWERSAVE:
	case IEEE80211_IOC_APBRIDGE:
	case IEEE80211_IOC_HIDESSID:
	case IEEE80211_IOC_INACTIVITY:
	case IEEE80211_IOC_PUREG:
	case IEEE80211_IOC_PUREN:
	case IEEE80211_IOC_HTCONF:
	case IEEE80211_IOC_HTCOMPAT:
	case IEEE80211_IOC_RIFS:
		if (sval == TruthValue_true)
			*value = 1;
		else if (sval != TruthValue_false)
			return (SNMP_ERR_INCONS_VALUE);
		break;
	case IEEE80211_IOC_REGDOMAIN:
		break;
	case IEEE80211_IOC_SSID:
		break;
	case IEEE80211_IOC_CURCHAN:
		break;
	case IEEE80211_IOC_TXPOWER:
		*value = sval * 2;
		break;
	case IEEE80211_IOC_FRAGTHRESHOLD:
		if (sval < IEEE80211_FRAG_MIN || sval > IEEE80211_FRAG_MAX)
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	case IEEE80211_IOC_RTSTHRESHOLD:
		if (sval < IEEE80211_RTS_MIN || sval > IEEE80211_RTS_MAX)
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	case IEEE80211_IOC_BGSCAN_IDLE:
		if (sval < WLAN_BGSCAN_IDLE_MIN)
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	case IEEE80211_IOC_BGSCAN_INTERVAL:
		if (sval < WLAN_SCAN_VALID_MIN)
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	case IEEE80211_IOC_BMISSTHRESHOLD:
		if (sval < IEEE80211_HWBMISS_MIN || sval > IEEE80211_HWBMISS_MAX)
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	case IEEE80211_IOC_BSSID:
		break;
	case IEEE80211_IOC_ROAMING:
		switch (sval) {
		case wlanIfaceRoamingMode_device:
			*value = IEEE80211_ROAMING_DEVICE;
			break;
		case wlanIfaceRoamingMode_manual:
			*value = IEEE80211_ROAMING_MANUAL;
			break;
		case wlanIfaceRoamingMode_auto:
			*value = IEEE80211_ROAMING_AUTO;
			break;
		default:
			return (SNMP_ERR_INCONS_VALUE);
		}
		break;
	case IEEE80211_IOC_BEACON_INTERVAL:
		if (sval < IEEE80211_BINTVAL_MIN || sval > IEEE80211_BINTVAL_MAX)
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	case IEEE80211_IOC_DTIM_PERIOD:
		if (sval < IEEE80211_DTIM_MIN || sval > IEEE80211_DTIM_MAX)
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	case IEEE80211_IOC_PROTMODE:
		switch (sval) {
		case wlanIfaceDot11gProtMode_cts:
			*value = IEEE80211_PROTMODE_CTS;
			break;
		case wlanIfaceDot11gProtMode_rtscts:
			*value = IEEE80211_PROTMODE_RTSCTS;
			break;
		case wlanIfaceDot11gProtMode_off:
			*value = IEEE80211_PROTMODE_OFF;
			break;
		default:
			return (SNMP_ERR_INCONS_VALUE);
		}
		break;
	case IEEE80211_IOC_AMPDU:
		switch (sval) {
		case WlanIfaceDot11nPduType_disabled:
			break;
		case WlanIfaceDot11nPduType_txOnly:
			*value = 1;
			break;
		case WlanIfaceDot11nPduType_rxOnly:
			*value = 2;
			break;
		case WlanIfaceDot11nPduType_txAndRx:
			*value = 3;
			break;
		default:
			return (SNMP_ERR_INCONS_VALUE);
		}
		break;
	case IEEE80211_IOC_AMPDU_DENSITY:
		switch (sval) {
		case 0:
			*value = IEEE80211_HTCAP_MPDUDENSITY_NA;
			break;
		case 25:
			*value = IEEE80211_HTCAP_MPDUDENSITY_025;
			break;
		case 50:
			*value = IEEE80211_HTCAP_MPDUDENSITY_05;
			break;
		case 100:
			*value = IEEE80211_HTCAP_MPDUDENSITY_1;
			break;
		case 200:
			*value = IEEE80211_HTCAP_MPDUDENSITY_2;
			break;
		case 400:
			*value = IEEE80211_HTCAP_MPDUDENSITY_4;
			break;
		case 800:
			*value = IEEE80211_HTCAP_MPDUDENSITY_8;
			break;
		case 1600:
			*value = IEEE80211_HTCAP_MPDUDENSITY_16;
			break;
		default:
			return (SNMP_ERR_INCONS_VALUE);
		}
		break;
	case IEEE80211_IOC_AMPDU_LIMIT:
		switch (sval) {
		case 8192:
			*value = IEEE80211_HTCAP_MAXRXAMPDU_8K;
			break;
		case 16384:
			*value = IEEE80211_HTCAP_MAXRXAMPDU_16K;
			break;
		case 32768:
			*value = IEEE80211_HTCAP_MAXRXAMPDU_32K;
			break;
		case 65536:
			*value = IEEE80211_HTCAP_MAXRXAMPDU_64K;
			break;
		default:
			return (SNMP_ERR_INCONS_VALUE);
		}
		break;
	case IEEE80211_IOC_AMSDU:
		switch (sval) {
		case WlanIfaceDot11nPduType_disabled:
			break;
		case WlanIfaceDot11nPduType_txOnly:
			*value = 1;
			break;
		case WlanIfaceDot11nPduType_rxOnly:
			*value = 2;
			break;
		case WlanIfaceDot11nPduType_txAndRx:
			*value = 3;
			break;
		default:
			return (SNMP_ERR_INCONS_VALUE);
		}
		break;
	case IEEE80211_IOC_AMSDU_LIMIT:
		if (sval == 3839 || sval == 0)
			*value = IEEE80211_HTCAP_MAXAMSDU_3839;
		else if (sval == 7935)
			*value = IEEE80211_HTCAP_MAXAMSDU_7935;
		else
			return (SNMP_ERR_INCONS_VALUE);
		break;
	case IEEE80211_IOC_HTPROTMODE:
		switch (sval) {
		case wlanIfaceDot11nHTProtMode_rts:
			*value = IEEE80211_PROTMODE_RTSCTS;
			break;
		case wlanIfaceDot11nHTProtMode_off:
			break;
		default:
			return (SNMP_ERR_INCONS_VALUE);
		}
		break;
	case IEEE80211_IOC_SHORTGI:
		if (sval == TruthValue_true)
			*value = IEEE80211_HTCAP_SHORTGI20 |
			    IEEE80211_HTCAP_SHORTGI40;
		else if (sval != TruthValue_false)
			return (SNMP_ERR_INCONS_VALUE);
		break;
	case IEEE80211_IOC_SMPS:
		switch (sval) {
		case wlanIfaceDot11nSMPSMode_disabled:
			*value = IEEE80211_HTCAP_SMPS_OFF;
			break;
		case wlanIfaceDot11nSMPSMode_static:
			*value = IEEE80211_HTCAP_SMPS_ENA;
			break;
		case wlanIfaceDot11nSMPSMode_dynamic:
			*value = IEEE80211_HTCAP_SMPS_DYNAMIC;
			break;
		default:
			return (SNMP_ERR_INCONS_VALUE);
		}
		break;
	case IEEE80211_IOC_TDMA_SLOT:
		if (sval < 0 || sval > WLAN_TDMA_MAXSLOTS) /* XXX */
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	case IEEE80211_IOC_TDMA_SLOTCNT:
		if (sval < 0 || sval > WLAN_TDMA_MAXSLOTS) /* XXX */
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	case IEEE80211_IOC_TDMA_SLOTLEN:
		if (sval < 2*100 || sval > 0xfffff) /* XXX */
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	case IEEE80211_IOC_TDMA_BINTERVAL:
		if (sval < 1) /* XXX */
			return (SNMP_ERR_INCONS_VALUE);
		*value = sval;
		break;
	default:
		return (SNMP_ERR_INCONS_VALUE);
	}

	return (SNMP_ERR_NOERROR);
}
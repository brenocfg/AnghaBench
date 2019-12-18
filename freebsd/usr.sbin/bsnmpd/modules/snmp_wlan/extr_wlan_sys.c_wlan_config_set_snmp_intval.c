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
struct wlan_iface {int tx_power; int frag_threshold; int rts_threshold; int bg_scan_idle; int bg_scan_interval; int beacons_missed; int beacon_interval; int dtim_period; int ampdu_density; int ampdu_limit; int amsdu_limit; int tdma_slot; int tdma_slot_count; int tdma_slot_length; int tdma_binterval; int /*<<< orphan*/  smps_mode; void* short_gi; void* rifs; int /*<<< orphan*/  ht_prot_mode; void* ht_compatible; void* ht_enabled; void* amsdu; void* ampdu; void* dot11n_pure; void* dot11g_pure; int /*<<< orphan*/  do11g_protect; void* inact_process; void* hide_ssid; void* ap_bridge; void* power_save; void* dynamic_wds; void* dot11h; void* dot11d; int /*<<< orphan*/  roam_mode; void* bg_scan; void* priv_subscribe; void* dturbo; void* fast_frames; void* dyn_frequency; void* packet_burst; } ;

/* Variables and functions */
#define  IEEE80211_HTCAP_MAXRXAMPDU_16K 188 
#define  IEEE80211_HTCAP_MAXRXAMPDU_32K 187 
#define  IEEE80211_HTCAP_MAXRXAMPDU_64K 186 
#define  IEEE80211_HTCAP_MAXRXAMPDU_8K 185 
#define  IEEE80211_HTCAP_MPDUDENSITY_025 184 
#define  IEEE80211_HTCAP_MPDUDENSITY_05 183 
#define  IEEE80211_HTCAP_MPDUDENSITY_1 182 
#define  IEEE80211_HTCAP_MPDUDENSITY_16 181 
#define  IEEE80211_HTCAP_MPDUDENSITY_2 180 
#define  IEEE80211_HTCAP_MPDUDENSITY_4 179 
#define  IEEE80211_HTCAP_MPDUDENSITY_8 178 
#define  IEEE80211_HTCAP_MPDUDENSITY_NA 177 
#define  IEEE80211_HTCAP_SMPS_DYNAMIC 176 
#define  IEEE80211_HTCAP_SMPS_ENA 175 
#define  IEEE80211_HTCAP_SMPS_OFF 174 
#define  IEEE80211_IOC_AMPDU 173 
#define  IEEE80211_IOC_AMPDU_DENSITY 172 
#define  IEEE80211_IOC_AMPDU_LIMIT 171 
#define  IEEE80211_IOC_AMSDU 170 
#define  IEEE80211_IOC_AMSDU_LIMIT 169 
#define  IEEE80211_IOC_APBRIDGE 168 
#define  IEEE80211_IOC_BEACON_INTERVAL 167 
#define  IEEE80211_IOC_BGSCAN 166 
#define  IEEE80211_IOC_BGSCAN_IDLE 165 
#define  IEEE80211_IOC_BGSCAN_INTERVAL 164 
#define  IEEE80211_IOC_BMISSTHRESHOLD 163 
#define  IEEE80211_IOC_BURST 162 
#define  IEEE80211_IOC_DFS 161 
#define  IEEE80211_IOC_DOTD 160 
#define  IEEE80211_IOC_DOTH 159 
#define  IEEE80211_IOC_DTIM_PERIOD 158 
#define  IEEE80211_IOC_DWDS 157 
#define  IEEE80211_IOC_FF 156 
#define  IEEE80211_IOC_FRAGTHRESHOLD 155 
#define  IEEE80211_IOC_HIDESSID 154 
#define  IEEE80211_IOC_HTCOMPAT 153 
#define  IEEE80211_IOC_HTCONF 152 
#define  IEEE80211_IOC_HTPROTMODE 151 
#define  IEEE80211_IOC_INACTIVITY 150 
#define  IEEE80211_IOC_POWERSAVE 149 
#define  IEEE80211_IOC_PROTMODE 148 
#define  IEEE80211_IOC_PUREG 147 
#define  IEEE80211_IOC_PUREN 146 
#define  IEEE80211_IOC_RIFS 145 
#define  IEEE80211_IOC_ROAMING 144 
#define  IEEE80211_IOC_RTSTHRESHOLD 143 
#define  IEEE80211_IOC_SHORTGI 142 
#define  IEEE80211_IOC_SMPS 141 
#define  IEEE80211_IOC_TDMA_BINTERVAL 140 
#define  IEEE80211_IOC_TDMA_SLOT 139 
#define  IEEE80211_IOC_TDMA_SLOTCNT 138 
#define  IEEE80211_IOC_TDMA_SLOTLEN 137 
#define  IEEE80211_IOC_TURBOP 136 
#define  IEEE80211_IOC_TXPOWER 135 
#define  IEEE80211_IOC_WPS 134 
#define  IEEE80211_PROTMODE_CTS 133 
#define  IEEE80211_PROTMODE_OFF 132 
#define  IEEE80211_PROTMODE_RTSCTS 131 
#define  IEEE80211_ROAMING_AUTO 130 
#define  IEEE80211_ROAMING_DEVICE 129 
#define  IEEE80211_ROAMING_MANUAL 128 
 void* TruthValue_false ; 
 void* TruthValue_true ; 
 void* WlanIfaceDot11nPduType_disabled ; 
 void* WlanIfaceDot11nPduType_rxOnly ; 
 void* WlanIfaceDot11nPduType_txAndRx ; 
 void* WlanIfaceDot11nPduType_txOnly ; 
 int /*<<< orphan*/  wlanIfaceDot11gProtMode_cts ; 
 int /*<<< orphan*/  wlanIfaceDot11gProtMode_off ; 
 int /*<<< orphan*/  wlanIfaceDot11gProtMode_rtscts ; 
 int /*<<< orphan*/  wlanIfaceDot11nHTProtMode_off ; 
 int /*<<< orphan*/  wlanIfaceDot11nHTProtMode_rts ; 
 int /*<<< orphan*/  wlanIfaceDot11nSMPSMode_disabled ; 
 int /*<<< orphan*/  wlanIfaceDot11nSMPSMode_dynamic ; 
 int /*<<< orphan*/  wlanIfaceDot11nSMPSMode_static ; 
 int /*<<< orphan*/  wlanIfaceRoamingMode_auto ; 
 int /*<<< orphan*/  wlanIfaceRoamingMode_device ; 
 int /*<<< orphan*/  wlanIfaceRoamingMode_manual ; 

__attribute__((used)) static void
wlan_config_set_snmp_intval(struct wlan_iface *wif, int op, int val)
{
	switch (op) {
	case IEEE80211_IOC_BURST:
		if (val == 0)
			wif->packet_burst = TruthValue_false;
		else
			wif->packet_burst = TruthValue_true;
		break;
	case IEEE80211_IOC_DFS:
		if (val == 0)
			wif->dyn_frequency = TruthValue_false;
		else
			wif->dyn_frequency = TruthValue_true;
		break;
	case IEEE80211_IOC_FF:
		if (val == 0)
			wif->fast_frames = TruthValue_false;
		else
			wif->fast_frames = TruthValue_true;
		break;
	case IEEE80211_IOC_TURBOP:
		if (val == 0)
			wif->dturbo = TruthValue_false;
		else
			wif->dturbo = TruthValue_true;
		break;
	case IEEE80211_IOC_TXPOWER:
		wif->tx_power = val / 2;
		break;
	case IEEE80211_IOC_FRAGTHRESHOLD:
		wif->frag_threshold = val;
		break;
	case IEEE80211_IOC_RTSTHRESHOLD:
		wif->rts_threshold = val;
		break;
	case IEEE80211_IOC_WPS:
		if (val == 0)
			wif->priv_subscribe = TruthValue_false;
		else
			wif->priv_subscribe = TruthValue_true;
		break;
	case IEEE80211_IOC_BGSCAN:
		if (val == 0)
			wif->bg_scan = TruthValue_false;
		else
			wif->bg_scan = TruthValue_true;
		break;
	case IEEE80211_IOC_BGSCAN_IDLE:
		wif->bg_scan_idle = val;
		break;
	case IEEE80211_IOC_BGSCAN_INTERVAL:
		wif->bg_scan_interval = val;
		break;
	case IEEE80211_IOC_BMISSTHRESHOLD:
		wif->beacons_missed = val;
		break;
	case IEEE80211_IOC_ROAMING:
		switch (val) {
		case IEEE80211_ROAMING_DEVICE:
			wif->roam_mode = wlanIfaceRoamingMode_device;
			break;
		case IEEE80211_ROAMING_MANUAL:
			wif->roam_mode = wlanIfaceRoamingMode_manual;
			break;
		case IEEE80211_ROAMING_AUTO:
			/* FALTHROUGH */
		default:
			wif->roam_mode = wlanIfaceRoamingMode_auto;
			break;
		}
		break;
	case IEEE80211_IOC_DOTD:
		if (val == 0)
			wif->dot11d = TruthValue_false;
		else
			wif->dot11d = TruthValue_true;
		break;
	case IEEE80211_IOC_DOTH:
		if (val == 0)
			wif->dot11h = TruthValue_false;
		else
			wif->dot11h = TruthValue_true;
		break;
	case IEEE80211_IOC_DWDS:
		if (val == 0)
			wif->dynamic_wds = TruthValue_false;
		else
			wif->dynamic_wds = TruthValue_true;
		break;
	case IEEE80211_IOC_POWERSAVE:
		if (val == 0)
			wif->power_save = TruthValue_false;
		else
			wif->power_save = TruthValue_true;
		break;
	case IEEE80211_IOC_APBRIDGE:
		if (val == 0)
			wif->ap_bridge = TruthValue_false;
		else
			wif->ap_bridge = TruthValue_true;
		break;
	case IEEE80211_IOC_BEACON_INTERVAL:
		wif->beacon_interval = val;
		break;
	case IEEE80211_IOC_DTIM_PERIOD:
		wif->dtim_period = val;
		break;
	case IEEE80211_IOC_HIDESSID:
		if (val == 0)
			wif->hide_ssid = TruthValue_false;
		else
			wif->hide_ssid = TruthValue_true;
		break;
	case IEEE80211_IOC_INACTIVITY:
		if (val == 0)
			wif->inact_process = TruthValue_false;
		else
			wif->inact_process = TruthValue_true;
		break;
	case IEEE80211_IOC_PROTMODE:
		switch (val) {
		case IEEE80211_PROTMODE_CTS:
			wif->do11g_protect = wlanIfaceDot11gProtMode_cts;
			break;
		case IEEE80211_PROTMODE_RTSCTS:
			wif->do11g_protect = wlanIfaceDot11gProtMode_rtscts;
			break;
		case IEEE80211_PROTMODE_OFF:
			/* FALLTHROUGH */
		default:
			wif->do11g_protect = wlanIfaceDot11gProtMode_off;
			break;
		}
		break;
	case IEEE80211_IOC_PUREG:
		if (val == 0)
			wif->dot11g_pure = TruthValue_false;
		else
			wif->dot11g_pure = TruthValue_true;
		break;
	case IEEE80211_IOC_PUREN:
		if (val == 0)
			wif->dot11n_pure = TruthValue_false;
		else
			wif->dot11n_pure = TruthValue_true;
		break;
	case IEEE80211_IOC_AMPDU:
		switch (val) {
		case 0:
			wif->ampdu = WlanIfaceDot11nPduType_disabled;
			break;
		case 1:
			wif->ampdu = WlanIfaceDot11nPduType_txOnly;
			break;
		case 2:
			wif->ampdu = WlanIfaceDot11nPduType_rxOnly;
			break;
		case 3:
			/* FALLTHROUGH */
		default:
			wif->ampdu = WlanIfaceDot11nPduType_txAndRx;
			break;
		}
		break;
	case IEEE80211_IOC_AMPDU_DENSITY:
		switch (val) {
		case IEEE80211_HTCAP_MPDUDENSITY_025:
			wif->ampdu_density = 25;
			break;
		case IEEE80211_HTCAP_MPDUDENSITY_05:
			wif->ampdu_density = 50;
			break;
		case IEEE80211_HTCAP_MPDUDENSITY_1:
			wif->ampdu_density = 100;
			break;
		case IEEE80211_HTCAP_MPDUDENSITY_2:
			wif->ampdu_density = 200;
			break;
		case IEEE80211_HTCAP_MPDUDENSITY_4:
			wif->ampdu_density = 400;
			break;
		case IEEE80211_HTCAP_MPDUDENSITY_8:
			wif->ampdu_density = 800;
			break;
		case IEEE80211_HTCAP_MPDUDENSITY_16:
			wif->ampdu_density = 1600;
			break;
		case IEEE80211_HTCAP_MPDUDENSITY_NA:
		default:
			wif->ampdu_density = 0;
			break;
		}
		break;
	case IEEE80211_IOC_AMPDU_LIMIT:
		switch (val) {
		case IEEE80211_HTCAP_MAXRXAMPDU_8K:
			wif->ampdu_limit = 8192;
			break;
		case IEEE80211_HTCAP_MAXRXAMPDU_16K:
			wif->ampdu_limit = 16384;
			break;
		case IEEE80211_HTCAP_MAXRXAMPDU_32K:
			wif->ampdu_limit = 32768;
			break;
		case IEEE80211_HTCAP_MAXRXAMPDU_64K:
		default:
			wif->ampdu_limit = 65536;
			break;
		}
		break;
	case IEEE80211_IOC_AMSDU:
		switch (val) {
		case 0:
			wif->amsdu = WlanIfaceDot11nPduType_disabled;
			break;
		case 1:
			wif->amsdu = WlanIfaceDot11nPduType_txOnly;
			break;
		case 3:
			wif->amsdu = WlanIfaceDot11nPduType_txAndRx;
			break;
		case 2:
		default:
			/* FALLTHROUGH */
			wif->amsdu = WlanIfaceDot11nPduType_rxOnly;
			break;
		}
		break;
	case IEEE80211_IOC_AMSDU_LIMIT:
		wif->amsdu_limit = val;
		break;
	case IEEE80211_IOC_HTCONF:
		if (val == 0) /* XXX */
			wif->ht_enabled = TruthValue_false;
		else
			wif->ht_enabled = TruthValue_true;
		break;
	case IEEE80211_IOC_HTCOMPAT:
		if (val == 0)
			wif->ht_compatible = TruthValue_false;
		else
			wif->ht_compatible = TruthValue_true;
		break;
	case IEEE80211_IOC_HTPROTMODE:
		if (val == IEEE80211_PROTMODE_RTSCTS)
			wif->ht_prot_mode = wlanIfaceDot11nHTProtMode_rts;
		else
			wif->ht_prot_mode = wlanIfaceDot11nHTProtMode_off;
		break;
	case IEEE80211_IOC_RIFS:
		if (val == 0)
			wif->rifs = TruthValue_false;
		else
			wif->rifs = TruthValue_true;
		break;
	case IEEE80211_IOC_SHORTGI:
		if (val == 0)
			wif->short_gi = TruthValue_false;
		else
			wif->short_gi = TruthValue_true;
		break;
	case IEEE80211_IOC_SMPS:
		switch (val) {
		case IEEE80211_HTCAP_SMPS_DYNAMIC:
			wif->smps_mode = wlanIfaceDot11nSMPSMode_dynamic;
			break;
		case IEEE80211_HTCAP_SMPS_ENA:
			wif->smps_mode = wlanIfaceDot11nSMPSMode_static;
			break;
		case IEEE80211_HTCAP_SMPS_OFF:
			/* FALLTHROUGH */
		default:
			wif->smps_mode = wlanIfaceDot11nSMPSMode_disabled;
			break;
		}
		break;
	case IEEE80211_IOC_TDMA_SLOT:
		wif->tdma_slot = val;
		break;
	case IEEE80211_IOC_TDMA_SLOTCNT:
		wif->tdma_slot_count = val;
		break;
	case IEEE80211_IOC_TDMA_SLOTLEN:
		wif->tdma_slot_length = val;
		break;
	case IEEE80211_IOC_TDMA_BINTERVAL:
		wif->tdma_binterval = val;
		break;
	default:
		break;
	}
}
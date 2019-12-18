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
struct wlan_iface {int drivercaps; int beacon_interval; int dtim_period; int htcaps; int /*<<< orphan*/  tdma_binterval; int /*<<< orphan*/  tdma_slot_length; int /*<<< orphan*/  tdma_slot_count; int /*<<< orphan*/  tdma_slot; int /*<<< orphan*/  smps_mode; void* short_gi; void* rifs; void* amsdu; void* ampdu; void* dot11n_pure; int /*<<< orphan*/  mode; void* power_save; void* dynamic_wds; int /*<<< orphan*/  frag_threshold; int /*<<< orphan*/  tx_power; void* dturbo; void* fast_frames; void* dyn_frequency; void* packet_burst; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_FRAG_MAX ; 
#define  IEEE80211_IOC_AMPDU 147 
#define  IEEE80211_IOC_AMSDU 146 
#define  IEEE80211_IOC_BEACON_INTERVAL 145 
#define  IEEE80211_IOC_BURST 144 
#define  IEEE80211_IOC_DFS 143 
#define  IEEE80211_IOC_DTIM_PERIOD 142 
#define  IEEE80211_IOC_DWDS 141 
#define  IEEE80211_IOC_FF 140 
#define  IEEE80211_IOC_FRAGTHRESHOLD 139 
#define  IEEE80211_IOC_POWERSAVE 138 
#define  IEEE80211_IOC_PUREN 137 
#define  IEEE80211_IOC_RIFS 136 
#define  IEEE80211_IOC_SHORTGI 135 
#define  IEEE80211_IOC_SMPS 134 
#define  IEEE80211_IOC_TDMA_BINTERVAL 133 
#define  IEEE80211_IOC_TDMA_SLOT 132 
#define  IEEE80211_IOC_TDMA_SLOTCNT 131 
#define  IEEE80211_IOC_TDMA_SLOTLEN 130 
#define  IEEE80211_IOC_TURBOP 129 
#define  IEEE80211_IOC_TXPOWER 128 
 void* TruthValue_false ; 
 int WlanDriverCaps_athFastFrames ; 
 int WlanDriverCaps_athTurbo ; 
 int WlanDriverCaps_burst ; 
 int WlanDriverCaps_dfs ; 
 int WlanDriverCaps_pmgt ; 
 int WlanDriverCaps_tdma ; 
 int WlanDriverCaps_txFrag ; 
 int WlanDriverCaps_txPmgt ; 
 int WlanDriverCaps_wds ; 
 int WlanHTCaps_htcAmpdu ; 
 int WlanHTCaps_htcAmsdu ; 
 int WlanHTCaps_htcHt ; 
 int WlanHTCaps_htcRifs ; 
 int WlanHTCaps_htcSmps ; 
 int WlanHTCaps_shortGi20 ; 
 int WlanHTCaps_shortGi40 ; 
 void* WlanIfaceDot11nPduType_disabled ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_hostAp ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_ibss ; 
 int /*<<< orphan*/  WlanIfaceOperatingModeType_meshPoint ; 
 int /*<<< orphan*/  wlanIfaceDot11nSMPSMode_disabled ; 

__attribute__((used)) static int
wlan_config_check(struct wlan_iface *wif, int op)
{
	switch (op) {
	case IEEE80211_IOC_BURST:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_burst)) == 0) {
			wif->packet_burst = TruthValue_false;
			return (-1);
		}
		break;
	case IEEE80211_IOC_DFS:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_dfs)) == 0) {
			wif->dyn_frequency = TruthValue_false;
			return (-1);
		}
		break;
	case IEEE80211_IOC_FF:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_athFastFrames))
		    == 0) {
			wif->fast_frames = TruthValue_false;
			return (-1);
		}
		break;
	case IEEE80211_IOC_TURBOP:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_athTurbo)) == 0) {
			wif->dturbo = TruthValue_false;
			return (-1);
		}
		break;
	case IEEE80211_IOC_TXPOWER:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_txPmgt)) == 0) {
			wif->tx_power = 0;
			return (-1);
		}
		break;
	case IEEE80211_IOC_FRAGTHRESHOLD:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_txFrag)) == 0) {
			wif->frag_threshold = IEEE80211_FRAG_MAX;
			return (-1);
		}
		break;
	case IEEE80211_IOC_DWDS:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_wds)) == 0) {
			wif->dynamic_wds = TruthValue_false;
			return (-1);
		}
		break;
	case IEEE80211_IOC_POWERSAVE:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_pmgt)) == 0) {
			wif->power_save = TruthValue_false;
			return (-1);
		}
		break;
	case IEEE80211_IOC_BEACON_INTERVAL:
		if (wif->mode != WlanIfaceOperatingModeType_hostAp &&
		    wif->mode != WlanIfaceOperatingModeType_meshPoint &&
		    wif->mode != WlanIfaceOperatingModeType_ibss) {
			wif->beacon_interval = 100; /* XXX */
			return (-1);
		}
		break;
	case IEEE80211_IOC_DTIM_PERIOD:
		if (wif->mode != WlanIfaceOperatingModeType_hostAp &&
		    wif->mode != WlanIfaceOperatingModeType_meshPoint &&
		    wif->mode != WlanIfaceOperatingModeType_ibss) {
			wif->dtim_period = 1; /* XXX */
			return (-1);
		}
		break;
	case IEEE80211_IOC_PUREN:
		if ((wif->htcaps & (0x1 << WlanHTCaps_htcHt)) == 0) {
			wif->dot11n_pure = TruthValue_false;
			return (-1);
		}
		break;
	case IEEE80211_IOC_AMPDU:
		if ((wif->htcaps & (0x1 << WlanHTCaps_htcAmpdu)) == 0) {
			wif->ampdu = WlanIfaceDot11nPduType_disabled;
			return (-1);
		}
		break;
	case IEEE80211_IOC_AMSDU:
		if ((wif->htcaps & (0x1 << WlanHTCaps_htcAmsdu)) == 0) {
			wif->amsdu = WlanIfaceDot11nPduType_disabled;
			return (-1);
		}
		break;
	case IEEE80211_IOC_RIFS:
		if ((wif->htcaps & (0x1 << WlanHTCaps_htcRifs)) == 0) {
			wif->rifs = TruthValue_false;
			return (-1);
		}
		break;
	case IEEE80211_IOC_SHORTGI:
		if ((wif->htcaps & (0x1 << WlanHTCaps_shortGi20 |
		    0x1 << WlanHTCaps_shortGi40)) == 0) {
			wif->short_gi = TruthValue_false;
			return (-1);
		}
		break;
	case IEEE80211_IOC_SMPS:
		if ((wif->htcaps & (0x1 << WlanHTCaps_htcSmps)) == 0) {
			wif->smps_mode = wlanIfaceDot11nSMPSMode_disabled;
			return (-1);
		}
		break;
	case IEEE80211_IOC_TDMA_SLOT:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_tdma)) == 0) {
			wif->tdma_slot = 0;
			return (-1);
		}
		break;
	case IEEE80211_IOC_TDMA_SLOTCNT:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_tdma)) == 0) {
			wif->tdma_slot_count = 0;
			return (-1);
		}
		break;
	case IEEE80211_IOC_TDMA_SLOTLEN:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_tdma)) == 0) {
			wif->tdma_slot_length = 0;
			return (-1);
		}
		break;
	case IEEE80211_IOC_TDMA_BINTERVAL:
		if ((wif->drivercaps & (0x1 << WlanDriverCaps_tdma)) == 0) {
			wif->tdma_binterval = 0;
			return (-1);
		}
		break;
	default:
		break;
	}

	return (0);
}
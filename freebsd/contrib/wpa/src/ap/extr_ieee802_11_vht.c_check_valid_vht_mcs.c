#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  tx_map; int /*<<< orphan*/  rx_map; } ;
struct ieee80211_vht_capabilities {TYPE_1__ vht_supported_mcs_set; } ;
struct hostapd_hw_modes {int /*<<< orphan*/  vht_mcs_set; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int VHT_RX_NSS_MAX_STREAMS ; 
 int le_to_host16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int check_valid_vht_mcs(struct hostapd_hw_modes *mode,
			       const u8 *sta_vht_capab)
{
	const struct ieee80211_vht_capabilities *vht_cap;
	struct ieee80211_vht_capabilities ap_vht_cap;
	u16 sta_rx_mcs_set, ap_tx_mcs_set;
	int i;

	if (!mode)
		return 1;

	/*
	 * Disable VHT caps for STAs for which there is not even a single
	 * allowed MCS in any supported number of streams, i.e., STA is
	 * advertising 3 (not supported) as VHT MCS rates for all supported
	 * stream cases.
	 */
	os_memcpy(&ap_vht_cap.vht_supported_mcs_set, mode->vht_mcs_set,
		  sizeof(ap_vht_cap.vht_supported_mcs_set));
	vht_cap = (const struct ieee80211_vht_capabilities *) sta_vht_capab;

	/* AP Tx MCS map vs. STA Rx MCS map */
	sta_rx_mcs_set = le_to_host16(vht_cap->vht_supported_mcs_set.rx_map);
	ap_tx_mcs_set = le_to_host16(ap_vht_cap.vht_supported_mcs_set.tx_map);

	for (i = 0; i < VHT_RX_NSS_MAX_STREAMS; i++) {
		if ((ap_tx_mcs_set & (0x3 << (i * 2))) == 3)
			continue;

		if ((sta_rx_mcs_set & (0x3 << (i * 2))) == 3)
			continue;

		return 1;
	}

	wpa_printf(MSG_DEBUG,
		   "No matching VHT MCS found between AP TX and STA RX");
	return 0;
}
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
struct TYPE_2__ {int /*<<< orphan*/  sim_num; int /*<<< orphan*/  fragment_size; } ;
struct wpa_ssid {int ht; int vht_rx_mcs_nss_1; int vht_rx_mcs_nss_2; int vht_rx_mcs_nss_3; int vht_rx_mcs_nss_4; int vht_rx_mcs_nss_5; int vht_rx_mcs_nss_6; int vht_rx_mcs_nss_7; int vht_rx_mcs_nss_8; int vht_tx_mcs_nss_1; int vht_tx_mcs_nss_2; int vht_tx_mcs_nss_3; int vht_tx_mcs_nss_4; int vht_tx_mcs_nss_5; int vht_tx_mcs_nss_6; int vht_tx_mcs_nss_7; int vht_tx_mcs_nss_8; int proactive_key_caching; int mac_addr; int /*<<< orphan*/  max_oper_chwidth; int /*<<< orphan*/  mka_priority; int /*<<< orphan*/  ieee80211w; int /*<<< orphan*/  ampdu_density; int /*<<< orphan*/  ampdu_factor; int /*<<< orphan*/  disable_max_amsdu; int /*<<< orphan*/  rx_stbc; int /*<<< orphan*/  tx_stbc; int /*<<< orphan*/  disable_ldpc; int /*<<< orphan*/  disable_sgi; int /*<<< orphan*/  disable_ht40; int /*<<< orphan*/  disable_ht; int /*<<< orphan*/  mesh_rssi_threshold; int /*<<< orphan*/  dot11MeshHoldingTimeout; int /*<<< orphan*/  dot11MeshConfirmTimeout; int /*<<< orphan*/  dot11MeshRetryTimeout; int /*<<< orphan*/  dot11MeshMaxRetries; TYPE_1__ eap; int /*<<< orphan*/  eap_workaround; int /*<<< orphan*/  eapol_flags; int /*<<< orphan*/  bg_scan_period; int /*<<< orphan*/  key_mgmt; int /*<<< orphan*/  group_cipher; int /*<<< orphan*/  pairwise_cipher; int /*<<< orphan*/  proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEFAULT_AMPDU_DENSITY ; 
 int /*<<< orphan*/  DEFAULT_AMPDU_FACTOR ; 
 int /*<<< orphan*/  DEFAULT_BG_SCAN_PERIOD ; 
 int /*<<< orphan*/  DEFAULT_DISABLE_HT ; 
 int /*<<< orphan*/  DEFAULT_DISABLE_HT40 ; 
 int /*<<< orphan*/  DEFAULT_DISABLE_LDPC ; 
 int /*<<< orphan*/  DEFAULT_DISABLE_MAX_AMSDU ; 
 int /*<<< orphan*/  DEFAULT_DISABLE_SGI ; 
 int /*<<< orphan*/  DEFAULT_EAPOL_FLAGS ; 
 int /*<<< orphan*/  DEFAULT_EAP_WORKAROUND ; 
 int /*<<< orphan*/  DEFAULT_FRAGMENT_SIZE ; 
 int /*<<< orphan*/  DEFAULT_GROUP ; 
 int /*<<< orphan*/  DEFAULT_KEY_MGMT ; 
 int /*<<< orphan*/  DEFAULT_MAX_OPER_CHWIDTH ; 
 int /*<<< orphan*/  DEFAULT_MESH_CONFIRM_TIMEOUT ; 
 int /*<<< orphan*/  DEFAULT_MESH_HOLDING_TIMEOUT ; 
 int /*<<< orphan*/  DEFAULT_MESH_MAX_RETRIES ; 
 int /*<<< orphan*/  DEFAULT_MESH_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  DEFAULT_MESH_RSSI_THRESHOLD ; 
 int /*<<< orphan*/  DEFAULT_PAIRWISE ; 
 int /*<<< orphan*/  DEFAULT_PRIO_NOT_KEY_SERVER ; 
 int /*<<< orphan*/  DEFAULT_PROTO ; 
 int /*<<< orphan*/  DEFAULT_RX_STBC ; 
 int /*<<< orphan*/  DEFAULT_TX_STBC ; 
 int /*<<< orphan*/  DEFAULT_USER_SELECTED_SIM ; 
 int /*<<< orphan*/  MGMT_FRAME_PROTECTION_DEFAULT ; 

void wpa_config_set_network_defaults(struct wpa_ssid *ssid)
{
	ssid->proto = DEFAULT_PROTO;
	ssid->pairwise_cipher = DEFAULT_PAIRWISE;
	ssid->group_cipher = DEFAULT_GROUP;
	ssid->key_mgmt = DEFAULT_KEY_MGMT;
	ssid->bg_scan_period = DEFAULT_BG_SCAN_PERIOD;
	ssid->ht = 1;
#ifdef IEEE8021X_EAPOL
	ssid->eapol_flags = DEFAULT_EAPOL_FLAGS;
	ssid->eap_workaround = DEFAULT_EAP_WORKAROUND;
	ssid->eap.fragment_size = DEFAULT_FRAGMENT_SIZE;
	ssid->eap.sim_num = DEFAULT_USER_SELECTED_SIM;
#endif /* IEEE8021X_EAPOL */
#ifdef CONFIG_MESH
	ssid->dot11MeshMaxRetries = DEFAULT_MESH_MAX_RETRIES;
	ssid->dot11MeshRetryTimeout = DEFAULT_MESH_RETRY_TIMEOUT;
	ssid->dot11MeshConfirmTimeout = DEFAULT_MESH_CONFIRM_TIMEOUT;
	ssid->dot11MeshHoldingTimeout = DEFAULT_MESH_HOLDING_TIMEOUT;
	ssid->mesh_rssi_threshold = DEFAULT_MESH_RSSI_THRESHOLD;
#endif /* CONFIG_MESH */
#ifdef CONFIG_HT_OVERRIDES
	ssid->disable_ht = DEFAULT_DISABLE_HT;
	ssid->disable_ht40 = DEFAULT_DISABLE_HT40;
	ssid->disable_sgi = DEFAULT_DISABLE_SGI;
	ssid->disable_ldpc = DEFAULT_DISABLE_LDPC;
	ssid->tx_stbc = DEFAULT_TX_STBC;
	ssid->rx_stbc = DEFAULT_RX_STBC;
	ssid->disable_max_amsdu = DEFAULT_DISABLE_MAX_AMSDU;
	ssid->ampdu_factor = DEFAULT_AMPDU_FACTOR;
	ssid->ampdu_density = DEFAULT_AMPDU_DENSITY;
#endif /* CONFIG_HT_OVERRIDES */
#ifdef CONFIG_VHT_OVERRIDES
	ssid->vht_rx_mcs_nss_1 = -1;
	ssid->vht_rx_mcs_nss_2 = -1;
	ssid->vht_rx_mcs_nss_3 = -1;
	ssid->vht_rx_mcs_nss_4 = -1;
	ssid->vht_rx_mcs_nss_5 = -1;
	ssid->vht_rx_mcs_nss_6 = -1;
	ssid->vht_rx_mcs_nss_7 = -1;
	ssid->vht_rx_mcs_nss_8 = -1;
	ssid->vht_tx_mcs_nss_1 = -1;
	ssid->vht_tx_mcs_nss_2 = -1;
	ssid->vht_tx_mcs_nss_3 = -1;
	ssid->vht_tx_mcs_nss_4 = -1;
	ssid->vht_tx_mcs_nss_5 = -1;
	ssid->vht_tx_mcs_nss_6 = -1;
	ssid->vht_tx_mcs_nss_7 = -1;
	ssid->vht_tx_mcs_nss_8 = -1;
#endif /* CONFIG_VHT_OVERRIDES */
	ssid->proactive_key_caching = -1;
#ifdef CONFIG_IEEE80211W
	ssid->ieee80211w = MGMT_FRAME_PROTECTION_DEFAULT;
#endif /* CONFIG_IEEE80211W */
#ifdef CONFIG_MACSEC
	ssid->mka_priority = DEFAULT_PRIO_NOT_KEY_SERVER;
#endif /* CONFIG_MACSEC */
	ssid->mac_addr = -1;
	ssid->max_oper_chwidth = DEFAULT_MAX_OPER_CHWIDTH;
}
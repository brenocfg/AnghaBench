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
struct hostapd_bss_config {unsigned int logger_syslog; unsigned int logger_stdout; int auth_algs; int wep_rekeying_period; int broadcast_key_idx_min; int broadcast_key_idx_max; int eap_reauth_period; int wpa_group_rekey; int wpa_gmk_rekey; int wpa_group_update_count; int wpa_pairwise_update_count; int dtim_period; int radius_server_auth_port; int eap_sim_db_timeout; int eap_sim_id; int max_listen_interval; int pwd_group; int assoc_sa_query_max_timeout; int assoc_sa_query_retry_timeout; int eap_fast_prov; int pac_key_lifetime; int pac_key_refresh_time; int wmm_enabled; int ft_over_ds; int rkh_pos_timeout; int rkh_neg_timeout; int rkh_pull_timeout; int rkh_pull_retries; int r0_key_lifetime; int radius_das_time_window; int sae_anti_clogging_threshold; int sae_sync; int gas_frag_limit; int fils_hlp_wait_time; int broadcast_deauth; int mbo_cell_data_conn_pref; int send_probe_response; int hs20_release; int macsec_port; int check_crl_strict; int /*<<< orphan*/  mka_priority; int /*<<< orphan*/  tls_flags; void* dhcp_relay_port; void* dhcp_server_port; int /*<<< orphan*/  fils_realms; int /*<<< orphan*/  group_mgmt_cipher; int /*<<< orphan*/  eapol_version; int /*<<< orphan*/  ap_max_inactivity; int /*<<< orphan*/  max_num_sta; scalar_t__ rsn_pairwise; void* wpa_group; void* wpa_pairwise; int /*<<< orphan*/  wpa_key_mgmt; int /*<<< orphan*/  wpa_disable_eapol_key_retries; void* logger_stdout_level; void* logger_syslog_level; int /*<<< orphan*/  anqp_elem; } ;

/* Variables and functions */
 int /*<<< orphan*/  AP_MAX_INACTIVITY ; 
 int /*<<< orphan*/  DEFAULT_PRIO_NOT_KEY_SERVER ; 
 int /*<<< orphan*/  DEFAULT_WPA_DISABLE_EAPOL_KEY_RETRIES ; 
 void* DHCP_SERVER_PORT ; 
 int /*<<< orphan*/  EAPOL_VERSION ; 
 void* HOSTAPD_LEVEL_INFO ; 
 int HS20_VERSION ; 
 int /*<<< orphan*/  MAX_STA_COUNT ; 
 int /*<<< orphan*/  TLS_CONN_DISABLE_TLSv1_3 ; 
 int WPA_AUTH_ALG_OPEN ; 
 int WPA_AUTH_ALG_SHARED ; 
 int /*<<< orphan*/  WPA_CIPHER_AES_128_CMAC ; 
 void* WPA_CIPHER_TKIP ; 
 int /*<<< orphan*/  WPA_KEY_MGMT_PSK ; 
 int /*<<< orphan*/  dl_list_init (int /*<<< orphan*/ *) ; 

void hostapd_config_defaults_bss(struct hostapd_bss_config *bss)
{
	dl_list_init(&bss->anqp_elem);

	bss->logger_syslog_level = HOSTAPD_LEVEL_INFO;
	bss->logger_stdout_level = HOSTAPD_LEVEL_INFO;
	bss->logger_syslog = (unsigned int) -1;
	bss->logger_stdout = (unsigned int) -1;

	bss->auth_algs = WPA_AUTH_ALG_OPEN | WPA_AUTH_ALG_SHARED;

	bss->wep_rekeying_period = 300;
	/* use key0 in individual key and key1 in broadcast key */
	bss->broadcast_key_idx_min = 1;
	bss->broadcast_key_idx_max = 2;
	bss->eap_reauth_period = 3600;

	bss->wpa_group_rekey = 600;
	bss->wpa_gmk_rekey = 86400;
	bss->wpa_group_update_count = 4;
	bss->wpa_pairwise_update_count = 4;
	bss->wpa_disable_eapol_key_retries =
		DEFAULT_WPA_DISABLE_EAPOL_KEY_RETRIES;
	bss->wpa_key_mgmt = WPA_KEY_MGMT_PSK;
	bss->wpa_pairwise = WPA_CIPHER_TKIP;
	bss->wpa_group = WPA_CIPHER_TKIP;
	bss->rsn_pairwise = 0;

	bss->max_num_sta = MAX_STA_COUNT;

	bss->dtim_period = 2;

	bss->radius_server_auth_port = 1812;
	bss->eap_sim_db_timeout = 1;
	bss->eap_sim_id = 3;
	bss->ap_max_inactivity = AP_MAX_INACTIVITY;
	bss->eapol_version = EAPOL_VERSION;

	bss->max_listen_interval = 65535;

	bss->pwd_group = 19; /* ECC: GF(p=256) */

#ifdef CONFIG_IEEE80211W
	bss->assoc_sa_query_max_timeout = 1000;
	bss->assoc_sa_query_retry_timeout = 201;
	bss->group_mgmt_cipher = WPA_CIPHER_AES_128_CMAC;
#endif /* CONFIG_IEEE80211W */
#ifdef EAP_SERVER_FAST
	 /* both anonymous and authenticated provisioning */
	bss->eap_fast_prov = 3;
	bss->pac_key_lifetime = 7 * 24 * 60 * 60;
	bss->pac_key_refresh_time = 1 * 24 * 60 * 60;
#endif /* EAP_SERVER_FAST */

	/* Set to -1 as defaults depends on HT in setup */
	bss->wmm_enabled = -1;

#ifdef CONFIG_IEEE80211R_AP
	bss->ft_over_ds = 1;
	bss->rkh_pos_timeout = 86400;
	bss->rkh_neg_timeout = 60;
	bss->rkh_pull_timeout = 1000;
	bss->rkh_pull_retries = 4;
	bss->r0_key_lifetime = 1209600;
#endif /* CONFIG_IEEE80211R_AP */

	bss->radius_das_time_window = 300;

	bss->sae_anti_clogging_threshold = 5;
	bss->sae_sync = 5;

	bss->gas_frag_limit = 1400;

#ifdef CONFIG_FILS
	dl_list_init(&bss->fils_realms);
	bss->fils_hlp_wait_time = 30;
	bss->dhcp_server_port = DHCP_SERVER_PORT;
	bss->dhcp_relay_port = DHCP_SERVER_PORT;
#endif /* CONFIG_FILS */

	bss->broadcast_deauth = 1;

#ifdef CONFIG_MBO
	bss->mbo_cell_data_conn_pref = -1;
#endif /* CONFIG_MBO */

	/* Disable TLS v1.3 by default for now to avoid interoperability issue.
	 * This can be enabled by default once the implementation has been fully
	 * completed and tested with other implementations. */
	bss->tls_flags = TLS_CONN_DISABLE_TLSv1_3;

	bss->send_probe_response = 1;

#ifdef CONFIG_HS20
	bss->hs20_release = (HS20_VERSION >> 4) + 1;
#endif /* CONFIG_HS20 */

#ifdef CONFIG_MACSEC
	bss->mka_priority = DEFAULT_PRIO_NOT_KEY_SERVER;
	bss->macsec_port = 1;
#endif /* CONFIG_MACSEC */

	/* Default to strict CRL checking. */
	bss->check_crl_strict = 1;
}
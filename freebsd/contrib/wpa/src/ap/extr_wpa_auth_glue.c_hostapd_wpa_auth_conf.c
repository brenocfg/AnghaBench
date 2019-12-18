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
struct wpa_auth_config {int eapol_version; int disable_pmksa_caching; int ieee80211w; scalar_t__ ssid_len; int r0_key_holder_len; int disable_gtk; int own_ie_override_len; int /*<<< orphan*/  fils_cache_id; int /*<<< orphan*/  fils_cache_id_set; int /*<<< orphan*/  ip_addr_end; int /*<<< orphan*/  ip_addr_start; int /*<<< orphan*/  ip_addr_mask; int /*<<< orphan*/  ip_addr_go; int /*<<< orphan*/  own_ie_override; int /*<<< orphan*/  corrupt_gtk_rekey_mic_probability; scalar_t__ rsn_preauth; void* rsn_pairwise; void* wpa_group; scalar_t__ wpa_pairwise; int /*<<< orphan*/  wpa_key_mgmt; int /*<<< orphan*/  wpa; int /*<<< orphan*/  ft_psk_generate_local; int /*<<< orphan*/  ft_over_ds; int /*<<< orphan*/  pmk_r1_push; int /*<<< orphan*/ * r1kh_list; int /*<<< orphan*/ * r0kh_list; int /*<<< orphan*/  rkh_pull_retries; int /*<<< orphan*/  rkh_pull_timeout; int /*<<< orphan*/  rkh_neg_timeout; int /*<<< orphan*/  rkh_pos_timeout; int /*<<< orphan*/  reassociation_deadline; int /*<<< orphan*/  r1_max_key_lifetime; int /*<<< orphan*/  r0_key_lifetime; int /*<<< orphan*/  r1_key_holder; int /*<<< orphan*/  r0_key_holder; int /*<<< orphan*/  mobility_domain; int /*<<< orphan*/  ssid; int /*<<< orphan*/  sae_require_mfp; int /*<<< orphan*/  group_mgmt_cipher; int /*<<< orphan*/  okc; int /*<<< orphan*/  ocv; int /*<<< orphan*/  wmm_uapsd; int /*<<< orphan*/  wmm_enabled; int /*<<< orphan*/  wpa_pairwise_update_count; int /*<<< orphan*/  wpa_disable_eapol_key_retries; int /*<<< orphan*/  wpa_group_update_count; int /*<<< orphan*/  wpa_ptk_rekey; int /*<<< orphan*/  wpa_gmk_rekey; int /*<<< orphan*/  wpa_strict_rekey; int /*<<< orphan*/  wpa_group_rekey; } ;
struct hostapd_config {int /*<<< orphan*/  corrupt_gtk_rekey_mic_probability; } ;
struct TYPE_2__ {scalar_t__ ssid_len; scalar_t__ ssid; } ;
struct hostapd_bss_config {int eapol_version; int disable_pmksa_caching; int ieee80211w; int disable_dgaf; scalar_t__ fils_cache_id; int /*<<< orphan*/  fils_cache_id_set; scalar_t__ ip_addr_end; scalar_t__ ip_addr_start; scalar_t__ ip_addr_mask; scalar_t__ ip_addr_go; scalar_t__ own_ie_override; scalar_t__ osen; int /*<<< orphan*/  ft_psk_generate_local; int /*<<< orphan*/  ft_over_ds; int /*<<< orphan*/  pmk_r1_push; int /*<<< orphan*/  r1kh_list; int /*<<< orphan*/  r0kh_list; int /*<<< orphan*/  rkh_pull_retries; int /*<<< orphan*/  rkh_pull_timeout; int /*<<< orphan*/  rkh_neg_timeout; int /*<<< orphan*/  rkh_pos_timeout; int /*<<< orphan*/  reassociation_deadline; int /*<<< orphan*/  r1_max_key_lifetime; int /*<<< orphan*/  r0_key_lifetime; scalar_t__ r1_key_holder; scalar_t__ nas_identifier; scalar_t__ mobility_domain; TYPE_1__ ssid; int /*<<< orphan*/  sae_require_mfp; int /*<<< orphan*/  group_mgmt_cipher; int /*<<< orphan*/  okc; int /*<<< orphan*/  ocv; int /*<<< orphan*/  wmm_uapsd; int /*<<< orphan*/  wmm_enabled; scalar_t__ rsn_preauth; void* rsn_pairwise; int /*<<< orphan*/  wpa_pairwise_update_count; int /*<<< orphan*/  wpa_disable_eapol_key_retries; int /*<<< orphan*/  wpa_group_update_count; int /*<<< orphan*/  wpa_ptk_rekey; int /*<<< orphan*/  wpa_gmk_rekey; int /*<<< orphan*/  wpa_strict_rekey; int /*<<< orphan*/  wpa_group_rekey; void* wpa_group; scalar_t__ wpa_pairwise; int /*<<< orphan*/  wpa_key_mgmt; int /*<<< orphan*/  wpa; } ;

/* Variables and functions */
 int FILS_CACHE_ID_LEN ; 
 scalar_t__ FT_R0KH_ID_MAX_LEN ; 
 int FT_R1KH_ID_LEN ; 
 scalar_t__ MAX_OWN_IE_OVERRIDE ; 
 int MOBILITY_DOMAIN_ID_LEN ; 
 scalar_t__ SSID_MAX_LEN ; 
 void* WPA_CIPHER_CCMP ; 
 int /*<<< orphan*/  WPA_KEY_MGMT_OSEN ; 
 int /*<<< orphan*/  WPA_PROTO_OSEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  os_memset (struct wpa_auth_config*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ os_strlen (scalar_t__) ; 
 scalar_t__ wpabuf_head (scalar_t__) ; 
 scalar_t__ wpabuf_len (scalar_t__) ; 

__attribute__((used)) static void hostapd_wpa_auth_conf(struct hostapd_bss_config *conf,
				  struct hostapd_config *iconf,
				  struct wpa_auth_config *wconf)
{
	os_memset(wconf, 0, sizeof(*wconf));
	wconf->wpa = conf->wpa;
	wconf->wpa_key_mgmt = conf->wpa_key_mgmt;
	wconf->wpa_pairwise = conf->wpa_pairwise;
	wconf->wpa_group = conf->wpa_group;
	wconf->wpa_group_rekey = conf->wpa_group_rekey;
	wconf->wpa_strict_rekey = conf->wpa_strict_rekey;
	wconf->wpa_gmk_rekey = conf->wpa_gmk_rekey;
	wconf->wpa_ptk_rekey = conf->wpa_ptk_rekey;
	wconf->wpa_group_update_count = conf->wpa_group_update_count;
	wconf->wpa_disable_eapol_key_retries =
		conf->wpa_disable_eapol_key_retries;
	wconf->wpa_pairwise_update_count = conf->wpa_pairwise_update_count;
	wconf->rsn_pairwise = conf->rsn_pairwise;
	wconf->rsn_preauth = conf->rsn_preauth;
	wconf->eapol_version = conf->eapol_version;
#ifdef CONFIG_MACSEC
	if (wconf->eapol_version > 2)
		wconf->eapol_version = 2;
#endif /* CONFIG_MACSEC */
	wconf->wmm_enabled = conf->wmm_enabled;
	wconf->wmm_uapsd = conf->wmm_uapsd;
	wconf->disable_pmksa_caching = conf->disable_pmksa_caching;
#ifdef CONFIG_OCV
	wconf->ocv = conf->ocv;
#endif /* CONFIG_OCV */
	wconf->okc = conf->okc;
#ifdef CONFIG_IEEE80211W
	wconf->ieee80211w = conf->ieee80211w;
	wconf->group_mgmt_cipher = conf->group_mgmt_cipher;
	wconf->sae_require_mfp = conf->sae_require_mfp;
#endif /* CONFIG_IEEE80211W */
#ifdef CONFIG_IEEE80211R_AP
	wconf->ssid_len = conf->ssid.ssid_len;
	if (wconf->ssid_len > SSID_MAX_LEN)
		wconf->ssid_len = SSID_MAX_LEN;
	os_memcpy(wconf->ssid, conf->ssid.ssid, wconf->ssid_len);
	os_memcpy(wconf->mobility_domain, conf->mobility_domain,
		  MOBILITY_DOMAIN_ID_LEN);
	if (conf->nas_identifier &&
	    os_strlen(conf->nas_identifier) <= FT_R0KH_ID_MAX_LEN) {
		wconf->r0_key_holder_len = os_strlen(conf->nas_identifier);
		os_memcpy(wconf->r0_key_holder, conf->nas_identifier,
			  wconf->r0_key_holder_len);
	}
	os_memcpy(wconf->r1_key_holder, conf->r1_key_holder, FT_R1KH_ID_LEN);
	wconf->r0_key_lifetime = conf->r0_key_lifetime;
	wconf->r1_max_key_lifetime = conf->r1_max_key_lifetime;
	wconf->reassociation_deadline = conf->reassociation_deadline;
	wconf->rkh_pos_timeout = conf->rkh_pos_timeout;
	wconf->rkh_neg_timeout = conf->rkh_neg_timeout;
	wconf->rkh_pull_timeout = conf->rkh_pull_timeout;
	wconf->rkh_pull_retries = conf->rkh_pull_retries;
	wconf->r0kh_list = &conf->r0kh_list;
	wconf->r1kh_list = &conf->r1kh_list;
	wconf->pmk_r1_push = conf->pmk_r1_push;
	wconf->ft_over_ds = conf->ft_over_ds;
	wconf->ft_psk_generate_local = conf->ft_psk_generate_local;
#endif /* CONFIG_IEEE80211R_AP */
#ifdef CONFIG_HS20
	wconf->disable_gtk = conf->disable_dgaf;
	if (conf->osen) {
		wconf->disable_gtk = 1;
		wconf->wpa = WPA_PROTO_OSEN;
		wconf->wpa_key_mgmt = WPA_KEY_MGMT_OSEN;
		wconf->wpa_pairwise = 0;
		wconf->wpa_group = WPA_CIPHER_CCMP;
		wconf->rsn_pairwise = WPA_CIPHER_CCMP;
		wconf->rsn_preauth = 0;
		wconf->disable_pmksa_caching = 1;
#ifdef CONFIG_IEEE80211W
		wconf->ieee80211w = 1;
#endif /* CONFIG_IEEE80211W */
	}
#endif /* CONFIG_HS20 */
#ifdef CONFIG_TESTING_OPTIONS
	wconf->corrupt_gtk_rekey_mic_probability =
		iconf->corrupt_gtk_rekey_mic_probability;
	if (conf->own_ie_override &&
	    wpabuf_len(conf->own_ie_override) <= MAX_OWN_IE_OVERRIDE) {
		wconf->own_ie_override_len = wpabuf_len(conf->own_ie_override);
		os_memcpy(wconf->own_ie_override,
			  wpabuf_head(conf->own_ie_override),
			  wconf->own_ie_override_len);
	}
#endif /* CONFIG_TESTING_OPTIONS */
#ifdef CONFIG_P2P
	os_memcpy(wconf->ip_addr_go, conf->ip_addr_go, 4);
	os_memcpy(wconf->ip_addr_mask, conf->ip_addr_mask, 4);
	os_memcpy(wconf->ip_addr_start, conf->ip_addr_start, 4);
	os_memcpy(wconf->ip_addr_end, conf->ip_addr_end, 4);
#endif /* CONFIG_P2P */
#ifdef CONFIG_FILS
	wconf->fils_cache_id_set = conf->fils_cache_id_set;
	os_memcpy(wconf->fils_cache_id, conf->fils_cache_id,
		  FILS_CACHE_ID_LEN);
#endif /* CONFIG_FILS */
}
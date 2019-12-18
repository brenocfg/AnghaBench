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
typedef  int u8 ;
struct wpabuf {int dummy; } ;
struct wpa_supplicant {int /*<<< orphan*/  wpa; scalar_t__ current_bss; int /*<<< orphan*/  key_mgmt; TYPE_1__* conf; int /*<<< orphan*/  p2p_disable_ip_addr_req; } ;
struct wpa_ssid {scalar_t__ proactive_key_caching; scalar_t__ p2p_group; int /*<<< orphan*/  wpa_ptk_rekey; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/  eap; int /*<<< orphan*/  eap_workaround; int /*<<< orphan*/  pairwise_cipher; } ;
struct rsn_supp_config {scalar_t__ proactive_key_caching; int p2p; int /*<<< orphan*/  fils_cache_id; int /*<<< orphan*/  wpa_rsc_relaxation; int /*<<< orphan*/  wpa_ptk_rekey; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; int /*<<< orphan*/ * eap_conf_ctx; int /*<<< orphan*/  eap_workaround; int /*<<< orphan*/  allowed_pairwise_cipher; struct wpa_ssid* network_ctx; } ;
typedef  int /*<<< orphan*/  conf ;
struct TYPE_2__ {scalar_t__ okc; int /*<<< orphan*/  wpa_rsc_relaxation; } ;

/* Variables and functions */
 int P2P_GROUP_CAPAB_IP_ADDR_ALLOCATION ; 
 int /*<<< orphan*/  P2P_IE_VENDOR_TYPE ; 
 int /*<<< orphan*/  os_memset (struct rsn_supp_config*,int /*<<< orphan*/ ,int) ; 
 int p2p_get_group_capab (struct wpabuf*) ; 
 int /*<<< orphan*/  wpa_bss_get_fils_cache_id (scalar_t__) ; 
 struct wpabuf* wpa_bss_get_vendor_ie_multi (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_key_mgmt_fils (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_set_config (int /*<<< orphan*/ ,struct rsn_supp_config*) ; 
 int /*<<< orphan*/  wpabuf_free (struct wpabuf*) ; 

void wpa_supplicant_rsn_supp_set_config(struct wpa_supplicant *wpa_s,
					struct wpa_ssid *ssid)
{
	struct rsn_supp_config conf;
	if (ssid) {
		os_memset(&conf, 0, sizeof(conf));
		conf.network_ctx = ssid;
		conf.allowed_pairwise_cipher = ssid->pairwise_cipher;
#ifdef IEEE8021X_EAPOL
		conf.proactive_key_caching = ssid->proactive_key_caching < 0 ?
			wpa_s->conf->okc : ssid->proactive_key_caching;
		conf.eap_workaround = ssid->eap_workaround;
		conf.eap_conf_ctx = &ssid->eap;
#endif /* IEEE8021X_EAPOL */
		conf.ssid = ssid->ssid;
		conf.ssid_len = ssid->ssid_len;
		conf.wpa_ptk_rekey = ssid->wpa_ptk_rekey;
#ifdef CONFIG_P2P
		if (ssid->p2p_group && wpa_s->current_bss &&
		    !wpa_s->p2p_disable_ip_addr_req) {
			struct wpabuf *p2p;
			p2p = wpa_bss_get_vendor_ie_multi(wpa_s->current_bss,
							  P2P_IE_VENDOR_TYPE);
			if (p2p) {
				u8 group_capab;
				group_capab = p2p_get_group_capab(p2p);
				if (group_capab &
				    P2P_GROUP_CAPAB_IP_ADDR_ALLOCATION)
					conf.p2p = 1;
				wpabuf_free(p2p);
			}
		}
#endif /* CONFIG_P2P */
		conf.wpa_rsc_relaxation = wpa_s->conf->wpa_rsc_relaxation;
#ifdef CONFIG_FILS
		if (wpa_key_mgmt_fils(wpa_s->key_mgmt))
			conf.fils_cache_id =
				wpa_bss_get_fils_cache_id(wpa_s->current_bss);
#endif /* CONFIG_FILS */
	}
	wpa_sm_set_config(wpa_s->wpa, ssid ? &conf : NULL);
}
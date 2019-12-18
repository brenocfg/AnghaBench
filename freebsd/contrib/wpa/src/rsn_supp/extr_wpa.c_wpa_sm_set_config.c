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
struct wpa_sm {int fils_cache_id_set; scalar_t__ wpa_rsc_relaxation; scalar_t__ p2p; scalar_t__ wpa_ptk_rekey; scalar_t__ ssid_len; int /*<<< orphan*/ * eap_conf_ctx; scalar_t__ eap_workaround; scalar_t__ proactive_key_caching; scalar_t__ allowed_pairwise_cipher; int /*<<< orphan*/ * network_ctx; int /*<<< orphan*/  fils_cache_id; int /*<<< orphan*/  ssid; } ;
struct rsn_supp_config {scalar_t__ fils_cache_id; scalar_t__ wpa_rsc_relaxation; scalar_t__ p2p; scalar_t__ wpa_ptk_rekey; scalar_t__ ssid_len; scalar_t__ ssid; int /*<<< orphan*/ * eap_conf_ctx; scalar_t__ eap_workaround; scalar_t__ proactive_key_caching; scalar_t__ allowed_pairwise_cipher; int /*<<< orphan*/ * network_ctx; } ;

/* Variables and functions */
 scalar_t__ FILS_CACHE_ID_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

void wpa_sm_set_config(struct wpa_sm *sm, struct rsn_supp_config *config)
{
	if (!sm)
		return;

	if (config) {
		sm->network_ctx = config->network_ctx;
		sm->allowed_pairwise_cipher = config->allowed_pairwise_cipher;
		sm->proactive_key_caching = config->proactive_key_caching;
		sm->eap_workaround = config->eap_workaround;
		sm->eap_conf_ctx = config->eap_conf_ctx;
		if (config->ssid) {
			os_memcpy(sm->ssid, config->ssid, config->ssid_len);
			sm->ssid_len = config->ssid_len;
		} else
			sm->ssid_len = 0;
		sm->wpa_ptk_rekey = config->wpa_ptk_rekey;
		sm->p2p = config->p2p;
		sm->wpa_rsc_relaxation = config->wpa_rsc_relaxation;
#ifdef CONFIG_FILS
		if (config->fils_cache_id) {
			sm->fils_cache_id_set = 1;
			os_memcpy(sm->fils_cache_id, config->fils_cache_id,
				  FILS_CACHE_ID_LEN);
		} else {
			sm->fils_cache_id_set = 0;
		}
#endif /* CONFIG_FILS */
	} else {
		sm->network_ctx = NULL;
		sm->allowed_pairwise_cipher = 0;
		sm->proactive_key_caching = 0;
		sm->eap_workaround = 0;
		sm->eap_conf_ctx = NULL;
		sm->ssid_len = 0;
		sm->wpa_ptk_rekey = 0;
		sm->p2p = 0;
		sm->wpa_rsc_relaxation = 0;
	}
}
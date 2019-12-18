#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const u8 ;
struct sta_info {scalar_t__ auth_alg; size_t owe_pmk_len; struct hostapd_sta_wpa_psk_short* psk; int /*<<< orphan*/  wpa_sm; int /*<<< orphan*/  const* owe_pmk; TYPE_1__* sae; } ;
struct rsn_pmksa_cache_entry {int akmp; size_t pmk_len; int /*<<< orphan*/  const* pmk; } ;
struct hostapd_sta_wpa_psk_short {int /*<<< orphan*/  const* psk; struct hostapd_sta_wpa_psk_short* next; scalar_t__ is_passphrase; int /*<<< orphan*/  passphrase; } ;
struct hostapd_data {TYPE_3__* conf; } ;
struct TYPE_5__ {int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  ssid; } ;
struct TYPE_6__ {int wpa_key_mgmt; TYPE_2__ ssid; } ;
struct TYPE_4__ {int /*<<< orphan*/  const* pmk; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 size_t PMK_LEN ; 
 scalar_t__ WLAN_AUTH_SAE ; 
 int WPA_KEY_MGMT_OWE ; 
 struct sta_info* ap_get_sta (struct hostapd_data*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* hostapd_get_psk (TYPE_3__*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  pbkdf2_sha1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/  const*,size_t) ; 
 struct rsn_pmksa_cache_entry* wpa_auth_sta_get_pmksa (int /*<<< orphan*/ ) ; 
 scalar_t__ wpa_auth_uses_sae (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static const u8 * hostapd_wpa_auth_get_psk(void *ctx, const u8 *addr,
					   const u8 *p2p_dev_addr,
					   const u8 *prev_psk, size_t *psk_len,
					   int *vlan_id)
{
	struct hostapd_data *hapd = ctx;
	struct sta_info *sta = ap_get_sta(hapd, addr);
	const u8 *psk;

	if (vlan_id)
		*vlan_id = 0;
	if (psk_len)
		*psk_len = PMK_LEN;

#ifdef CONFIG_SAE
	if (sta && sta->auth_alg == WLAN_AUTH_SAE) {
		if (!sta->sae || prev_psk)
			return NULL;
		return sta->sae->pmk;
	}
	if (sta && wpa_auth_uses_sae(sta->wpa_sm)) {
		wpa_printf(MSG_DEBUG,
			   "No PSK for STA trying to use SAE with PMKSA caching");
		return NULL;
	}
#endif /* CONFIG_SAE */

#ifdef CONFIG_OWE
	if ((hapd->conf->wpa_key_mgmt & WPA_KEY_MGMT_OWE) &&
	    sta && sta->owe_pmk) {
		if (psk_len)
			*psk_len = sta->owe_pmk_len;
		return sta->owe_pmk;
	}
	if ((hapd->conf->wpa_key_mgmt & WPA_KEY_MGMT_OWE) && sta) {
		struct rsn_pmksa_cache_entry *sa;

		sa = wpa_auth_sta_get_pmksa(sta->wpa_sm);
		if (sa && sa->akmp == WPA_KEY_MGMT_OWE) {
			if (psk_len)
				*psk_len = sa->pmk_len;
			return sa->pmk;
		}
	}
#endif /* CONFIG_OWE */

	psk = hostapd_get_psk(hapd->conf, addr, p2p_dev_addr, prev_psk,
			      vlan_id);
	/*
	 * This is about to iterate over all psks, prev_psk gives the last
	 * returned psk which should not be returned again.
	 * logic list (all hostapd_get_psk; all sta->psk)
	 */
	if (sta && sta->psk && !psk) {
		struct hostapd_sta_wpa_psk_short *pos;

		if (vlan_id)
			*vlan_id = 0;
		psk = sta->psk->psk;
		for (pos = sta->psk; pos; pos = pos->next) {
			if (pos->is_passphrase) {
				pbkdf2_sha1(pos->passphrase,
					    hapd->conf->ssid.ssid,
					    hapd->conf->ssid.ssid_len, 4096,
					    pos->psk, PMK_LEN);
				pos->is_passphrase = 0;
			}
			if (pos->psk == prev_psk) {
				psk = pos->next ? pos->next->psk : NULL;
				break;
			}
		}
	}
	return psk;
}
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
typedef  int /*<<< orphan*/  u8 ;
struct wpa_sm {scalar_t__ key_mgmt; int /*<<< orphan*/  pairwise_cipher; int /*<<< orphan*/  snonce; int /*<<< orphan*/  bssid; int /*<<< orphan*/  own_addr; int /*<<< orphan*/  pmk_len; int /*<<< orphan*/  pmk; scalar_t__ dpp_z; } ;
struct wpa_ptk {int dummy; } ;
struct wpa_eapol_key {int /*<<< orphan*/  key_nonce; } ;

/* Variables and functions */
 scalar_t__ WPA_KEY_MGMT_DPP ; 
 int wpa_derive_ptk_ft (struct wpa_sm*,unsigned char const*,struct wpa_eapol_key const*,struct wpa_ptk*) ; 
 scalar_t__ wpa_key_mgmt_ft (scalar_t__) ; 
 int wpa_pmk_to_ptk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_ptk*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/ * wpabuf_head (scalar_t__) ; 
 size_t wpabuf_len (scalar_t__) ; 

__attribute__((used)) static int wpa_derive_ptk(struct wpa_sm *sm, const unsigned char *src_addr,
			  const struct wpa_eapol_key *key, struct wpa_ptk *ptk)
{
	const u8 *z = NULL;
	size_t z_len = 0;

#ifdef CONFIG_IEEE80211R
	if (wpa_key_mgmt_ft(sm->key_mgmt))
		return wpa_derive_ptk_ft(sm, src_addr, key, ptk);
#endif /* CONFIG_IEEE80211R */

#ifdef CONFIG_DPP2
	if (sm->key_mgmt == WPA_KEY_MGMT_DPP && sm->dpp_z) {
		z = wpabuf_head(sm->dpp_z);
		z_len = wpabuf_len(sm->dpp_z);
	}
#endif /* CONFIG_DPP2 */

	return wpa_pmk_to_ptk(sm->pmk, sm->pmk_len, "Pairwise key expansion",
			      sm->own_addr, sm->bssid, sm->snonce,
			      key->key_nonce, ptk, sm->key_mgmt,
			      sm->pairwise_cipher, z, z_len);
}
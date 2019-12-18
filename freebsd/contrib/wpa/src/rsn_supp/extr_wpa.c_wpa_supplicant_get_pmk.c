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
struct wpa_sm {int pmk_len; int xxkey_len; scalar_t__ key_mgmt; scalar_t__ proto; int /*<<< orphan*/  bssid; TYPE_1__* ctx; struct rsn_pmksa_cache_entry* cur_pmksa; scalar_t__ ft_protocol; int /*<<< orphan*/  pmksa; int /*<<< orphan*/  network_ctx; int /*<<< orphan*/  own_addr; int /*<<< orphan*/ * pmk; int /*<<< orphan*/ * fils_cache_id; scalar_t__ fils_cache_id_set; int /*<<< orphan*/ * xxkey; scalar_t__ eapol; } ;
struct rsn_pmksa_cache_entry {int /*<<< orphan*/  pmkid; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_P_EAPOL ; 
 int /*<<< orphan*/  IEEE802_1X_TYPE_EAPOL_START ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  MSG_INFO ; 
 int /*<<< orphan*/  MSG_WARNING ; 
 int /*<<< orphan*/  PMKID_LEN ; 
 int PMK_LEN ; 
 int PMK_LEN_SUITE_B_192 ; 
 int SHA384_MAC_LEN ; 
 scalar_t__ WPA_KEY_MGMT_FT_SAE ; 
 scalar_t__ WPA_KEY_MGMT_OSEN ; 
 scalar_t__ WPA_PROTO_RSN ; 
 int eapol_sm_get_key (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  eapol_sm_notify_cached (scalar_t__) ; 
 int /*<<< orphan*/  forced_memzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  os_free (int /*<<< orphan*/ *) ; 
 scalar_t__ os_memcmp_const (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct rsn_pmksa_cache_entry* pmksa_cache_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/  const*) ; 
 struct rsn_pmksa_cache_entry* pmksa_cache_get (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_hexdump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_hexdump_key (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ wpa_key_mgmt_ft (scalar_t__) ; 
 scalar_t__ wpa_key_mgmt_sha384 (scalar_t__) ; 
 int /*<<< orphan*/  wpa_key_mgmt_suite_b (scalar_t__) ; 
 scalar_t__ wpa_key_mgmt_wpa_ieee8021x (scalar_t__) ; 
 int /*<<< orphan*/  wpa_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * wpa_sm_alloc_eapol (struct wpa_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_sm_ether_send (struct wpa_sm*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wpa_sm_set_pmk_from_pmksa (struct wpa_sm*) ; 
 int /*<<< orphan*/  wpa_supplicant_key_mgmt_set_pmk (struct wpa_sm*) ; 

__attribute__((used)) static int wpa_supplicant_get_pmk(struct wpa_sm *sm,
				  const unsigned char *src_addr,
				  const u8 *pmkid)
{
	int abort_cached = 0;

	if (pmkid && !sm->cur_pmksa) {
		/* When using drivers that generate RSN IE, wpa_supplicant may
		 * not have enough time to get the association information
		 * event before receiving this 1/4 message, so try to find a
		 * matching PMKSA cache entry here. */
		sm->cur_pmksa = pmksa_cache_get(sm->pmksa, src_addr, pmkid,
						NULL, 0);
		if (sm->cur_pmksa) {
			wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
				"RSN: found matching PMKID from PMKSA cache");
		} else {
			wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
				"RSN: no matching PMKID found");
			abort_cached = 1;
		}
	}

	if (pmkid && sm->cur_pmksa &&
	    os_memcmp_const(pmkid, sm->cur_pmksa->pmkid, PMKID_LEN) == 0) {
		wpa_hexdump(MSG_DEBUG, "RSN: matched PMKID", pmkid, PMKID_LEN);
		wpa_sm_set_pmk_from_pmksa(sm);
		wpa_hexdump_key(MSG_DEBUG, "RSN: PMK from PMKSA cache",
				sm->pmk, sm->pmk_len);
		eapol_sm_notify_cached(sm->eapol);
#ifdef CONFIG_IEEE80211R
		sm->xxkey_len = 0;
#ifdef CONFIG_SAE
		if (sm->key_mgmt == WPA_KEY_MGMT_FT_SAE &&
		    sm->pmk_len == PMK_LEN) {
			/* Need to allow FT key derivation to proceed with
			 * PMK from SAE being used as the XXKey in cases where
			 * the PMKID in msg 1/4 matches the PMKSA entry that was
			 * just added based on SAE authentication for the
			 * initial mobility domain association. */
			os_memcpy(sm->xxkey, sm->pmk, sm->pmk_len);
			sm->xxkey_len = sm->pmk_len;
		}
#endif /* CONFIG_SAE */
#endif /* CONFIG_IEEE80211R */
	} else if (wpa_key_mgmt_wpa_ieee8021x(sm->key_mgmt) && sm->eapol) {
		int res, pmk_len;
#ifdef CONFIG_IEEE80211R
		u8 buf[2 * PMK_LEN];
#endif /* CONFIG_IEEE80211R */

		if (wpa_key_mgmt_sha384(sm->key_mgmt))
			pmk_len = PMK_LEN_SUITE_B_192;
		else
			pmk_len = PMK_LEN;
		res = eapol_sm_get_key(sm->eapol, sm->pmk, pmk_len);
		if (res) {
			if (pmk_len == PMK_LEN) {
				/*
				 * EAP-LEAP is an exception from other EAP
				 * methods: it uses only 16-byte PMK.
				 */
				res = eapol_sm_get_key(sm->eapol, sm->pmk, 16);
				pmk_len = 16;
			}
		}
#ifdef CONFIG_IEEE80211R
		if (res == 0 &&
		    eapol_sm_get_key(sm->eapol, buf, 2 * PMK_LEN) == 0) {
			if (wpa_key_mgmt_sha384(sm->key_mgmt)) {
				os_memcpy(sm->xxkey, buf, SHA384_MAC_LEN);
				sm->xxkey_len = SHA384_MAC_LEN;
			} else {
				os_memcpy(sm->xxkey, buf + PMK_LEN, PMK_LEN);
				sm->xxkey_len = PMK_LEN;
			}
			forced_memzero(buf, sizeof(buf));
			if (sm->proto == WPA_PROTO_RSN &&
			    wpa_key_mgmt_ft(sm->key_mgmt)) {
				struct rsn_pmksa_cache_entry *sa = NULL;
				const u8 *fils_cache_id = NULL;

#ifdef CONFIG_FILS
				if (sm->fils_cache_id_set)
					fils_cache_id = sm->fils_cache_id;
#endif /* CONFIG_FILS */
				wpa_hexdump_key(MSG_DEBUG,
						"FT: Cache XXKey/MPMK",
						sm->xxkey, sm->xxkey_len);
				sa = pmksa_cache_add(sm->pmksa,
						     sm->xxkey, sm->xxkey_len,
						     NULL, NULL, 0,
						     src_addr, sm->own_addr,
						     sm->network_ctx,
						     sm->key_mgmt,
						     fils_cache_id);
				if (!sm->cur_pmksa)
					sm->cur_pmksa = sa;
			}
		}
#endif /* CONFIG_IEEE80211R */
		if (res == 0) {
			struct rsn_pmksa_cache_entry *sa = NULL;
			const u8 *fils_cache_id = NULL;

#ifdef CONFIG_FILS
			if (sm->fils_cache_id_set)
				fils_cache_id = sm->fils_cache_id;
#endif /* CONFIG_FILS */

			wpa_hexdump_key(MSG_DEBUG, "WPA: PMK from EAPOL state "
					"machines", sm->pmk, pmk_len);
			sm->pmk_len = pmk_len;
			wpa_supplicant_key_mgmt_set_pmk(sm);
			if (sm->proto == WPA_PROTO_RSN &&
			    !wpa_key_mgmt_suite_b(sm->key_mgmt) &&
			    !wpa_key_mgmt_ft(sm->key_mgmt)) {
				sa = pmksa_cache_add(sm->pmksa,
						     sm->pmk, pmk_len, NULL,
						     NULL, 0,
						     src_addr, sm->own_addr,
						     sm->network_ctx,
						     sm->key_mgmt,
						     fils_cache_id);
			}
			if (!sm->cur_pmksa && pmkid &&
			    pmksa_cache_get(sm->pmksa, src_addr, pmkid, NULL,
				    0)) {
				wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
					"RSN: the new PMK matches with the "
					"PMKID");
				abort_cached = 0;
			} else if (sa && !sm->cur_pmksa && pmkid) {
				/*
				 * It looks like the authentication server
				 * derived mismatching MSK. This should not
				 * really happen, but bugs happen.. There is not
				 * much we can do here without knowing what
				 * exactly caused the server to misbehave.
				 */
				wpa_msg(sm->ctx->msg_ctx, MSG_INFO,
					"RSN: PMKID mismatch - authentication server may have derived different MSK?!");
				return -1;
			}

			if (!sm->cur_pmksa)
				sm->cur_pmksa = sa;
#ifdef CONFIG_IEEE80211R
		} else if (wpa_key_mgmt_ft(sm->key_mgmt) && sm->ft_protocol) {
			wpa_printf(MSG_DEBUG,
				   "FT: Continue 4-way handshake without PMK/PMKID for association using FT protocol");
#endif /* CONFIG_IEEE80211R */
		} else {
			wpa_msg(sm->ctx->msg_ctx, MSG_WARNING,
				"WPA: Failed to get master session key from "
				"EAPOL state machines - key handshake "
				"aborted");
			if (sm->cur_pmksa) {
				wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
					"RSN: Cancelled PMKSA caching "
					"attempt");
				sm->cur_pmksa = NULL;
				abort_cached = 1;
			} else if (!abort_cached) {
				return -1;
			}
		}
	}

	if (abort_cached && wpa_key_mgmt_wpa_ieee8021x(sm->key_mgmt) &&
	    !wpa_key_mgmt_suite_b(sm->key_mgmt) &&
	    !wpa_key_mgmt_ft(sm->key_mgmt) && sm->key_mgmt != WPA_KEY_MGMT_OSEN)
	{
		/* Send EAPOL-Start to trigger full EAP authentication. */
		u8 *buf;
		size_t buflen;

		wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
			"RSN: no PMKSA entry found - trigger "
			"full EAP authentication");
		buf = wpa_sm_alloc_eapol(sm, IEEE802_1X_TYPE_EAPOL_START,
					 NULL, 0, &buflen, NULL);
		if (buf) {
			wpa_sm_ether_send(sm, sm->bssid, ETH_P_EAPOL,
					  buf, buflen);
			os_free(buf);
			return -2;
		}

		return -1;
	}

	return 0;
}
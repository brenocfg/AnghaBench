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
struct wpa_sm {int renew_snonce; int ft_protocol; int /*<<< orphan*/ * p2p_ip_addr; int /*<<< orphan*/  igtk_wnm_sleep; int /*<<< orphan*/  igtk; int /*<<< orphan*/  gtk_wnm_sleep; int /*<<< orphan*/  gtk; int /*<<< orphan*/  tptk; scalar_t__ tptk_set; int /*<<< orphan*/  ptk; scalar_t__ ptk_set; TYPE_1__* ctx; int /*<<< orphan*/  bssid; scalar_t__ fils_completed; int /*<<< orphan*/  eapol; int /*<<< orphan*/  preauth_bssid; scalar_t__ rx_replay_counter_set; int /*<<< orphan*/ * rx_replay_counter; } ;
struct TYPE_2__ {int /*<<< orphan*/  msg_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MSG_DEBUG ; 
 int WPA_REPLAY_COUNTER_LEN ; 
 int /*<<< orphan*/  eapol_sm_notify_portValid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ os_memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rsn_preauth_deinit (struct wpa_sm*) ; 
 int /*<<< orphan*/  wpa_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ wpa_ft_is_completed (struct wpa_sm*) ; 
 int /*<<< orphan*/  wpa_ft_prepare_auth_request (struct wpa_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wpa_supplicant_key_neg_complete (struct wpa_sm*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_tdls_assoc (struct wpa_sm*) ; 

void wpa_sm_notify_assoc(struct wpa_sm *sm, const u8 *bssid)
{
	int clear_keys = 1;

	if (sm == NULL)
		return;

	wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG,
		"WPA: Association event - clear replay counter");
	os_memcpy(sm->bssid, bssid, ETH_ALEN);
	os_memset(sm->rx_replay_counter, 0, WPA_REPLAY_COUNTER_LEN);
	sm->rx_replay_counter_set = 0;
	sm->renew_snonce = 1;
	if (os_memcmp(sm->preauth_bssid, bssid, ETH_ALEN) == 0)
		rsn_preauth_deinit(sm);

#ifdef CONFIG_IEEE80211R
	if (wpa_ft_is_completed(sm)) {
		/*
		 * Clear portValid to kick EAPOL state machine to re-enter
		 * AUTHENTICATED state to get the EAPOL port Authorized.
		 */
		eapol_sm_notify_portValid(sm->eapol, FALSE);
		wpa_supplicant_key_neg_complete(sm, sm->bssid, 1);

		/* Prepare for the next transition */
		wpa_ft_prepare_auth_request(sm, NULL);

		clear_keys = 0;
		sm->ft_protocol = 1;
	} else {
		sm->ft_protocol = 0;
	}
#endif /* CONFIG_IEEE80211R */
#ifdef CONFIG_FILS
	if (sm->fils_completed) {
		/*
		 * Clear portValid to kick EAPOL state machine to re-enter
		 * AUTHENTICATED state to get the EAPOL port Authorized.
		 */
		wpa_supplicant_key_neg_complete(sm, sm->bssid, 1);
		clear_keys = 0;
	}
#endif /* CONFIG_FILS */

	if (clear_keys) {
		/*
		 * IEEE 802.11, 8.4.10: Delete PTK SA on (re)association if
		 * this is not part of a Fast BSS Transition.
		 */
		wpa_dbg(sm->ctx->msg_ctx, MSG_DEBUG, "WPA: Clear old PTK");
		sm->ptk_set = 0;
		os_memset(&sm->ptk, 0, sizeof(sm->ptk));
		sm->tptk_set = 0;
		os_memset(&sm->tptk, 0, sizeof(sm->tptk));
		os_memset(&sm->gtk, 0, sizeof(sm->gtk));
		os_memset(&sm->gtk_wnm_sleep, 0, sizeof(sm->gtk_wnm_sleep));
#ifdef CONFIG_IEEE80211W
		os_memset(&sm->igtk, 0, sizeof(sm->igtk));
		os_memset(&sm->igtk_wnm_sleep, 0, sizeof(sm->igtk_wnm_sleep));
#endif /* CONFIG_IEEE80211W */
	}

#ifdef CONFIG_TDLS
	wpa_tdls_assoc(sm);
#endif /* CONFIG_TDLS */

#ifdef CONFIG_P2P
	os_memset(sm->p2p_ip_addr, 0, sizeof(sm->p2p_ip_addr));
#endif /* CONFIG_P2P */
}
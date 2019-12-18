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
struct wpa_sm {int /*<<< orphan*/  bssid; scalar_t__ msg_3_of_4_ok; scalar_t__ ft_protocol; scalar_t__ ft_reassoc_completed; scalar_t__ fils_completed; int /*<<< orphan*/  dot11RSNA4WayHandshakeFailures; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 scalar_t__ WPA_4WAY_HANDSHAKE ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmksa_cache_clear_current (struct wpa_sm*) ; 
 int /*<<< orphan*/  rsn_preauth_deinit (struct wpa_sm*) ; 
 int /*<<< orphan*/  wpa_sm_drop_sa (struct wpa_sm*) ; 
 scalar_t__ wpa_sm_get_state (struct wpa_sm*) ; 
 int /*<<< orphan*/  wpa_sm_rekey_ptk ; 
 int /*<<< orphan*/  wpa_sm_start_preauth ; 
 int /*<<< orphan*/  wpa_tdls_disassoc (struct wpa_sm*) ; 

void wpa_sm_notify_disassoc(struct wpa_sm *sm)
{
	eloop_cancel_timeout(wpa_sm_start_preauth, sm, NULL);
	eloop_cancel_timeout(wpa_sm_rekey_ptk, sm, NULL);
	rsn_preauth_deinit(sm);
	pmksa_cache_clear_current(sm);
	if (wpa_sm_get_state(sm) == WPA_4WAY_HANDSHAKE)
		sm->dot11RSNA4WayHandshakeFailures++;
#ifdef CONFIG_TDLS
	wpa_tdls_disassoc(sm);
#endif /* CONFIG_TDLS */
#ifdef CONFIG_FILS
	sm->fils_completed = 0;
#endif /* CONFIG_FILS */
#ifdef CONFIG_IEEE80211R
	sm->ft_reassoc_completed = 0;
	sm->ft_protocol = 0;
#endif /* CONFIG_IEEE80211R */

	/* Keys are not needed in the WPA state machine anymore */
	wpa_sm_drop_sa(sm);

	sm->msg_3_of_4_ok = 0;
	os_memset(sm->bssid, 0, ETH_ALEN);
}
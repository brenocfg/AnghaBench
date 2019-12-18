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
struct wpa_sm {int /*<<< orphan*/  dpp_z; int /*<<< orphan*/  owe_ecdh; int /*<<< orphan*/  fils_ft_ies; int /*<<< orphan*/  fils_ecdh; int /*<<< orphan*/  test_assoc_ie; struct wpa_sm* assoc_resp_ies; struct wpa_sm* ctx; struct wpa_sm* ap_rsn_ie; struct wpa_sm* ap_wpa_ie; struct wpa_sm* assoc_wpa_ie; int /*<<< orphan*/  pmksa; } ;

/* Variables and functions */
 int /*<<< orphan*/  crypto_ecdh_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eloop_cancel_timeout (int /*<<< orphan*/ ,struct wpa_sm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct wpa_sm*) ; 
 int /*<<< orphan*/  pmksa_cache_deinit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpa_sm_drop_sa (struct wpa_sm*) ; 
 int /*<<< orphan*/  wpa_sm_rekey_ptk ; 
 int /*<<< orphan*/  wpa_sm_start_preauth ; 
 int /*<<< orphan*/  wpabuf_clear_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wpabuf_free (int /*<<< orphan*/ ) ; 

void wpa_sm_deinit(struct wpa_sm *sm)
{
	if (sm == NULL)
		return;
	pmksa_cache_deinit(sm->pmksa);
	eloop_cancel_timeout(wpa_sm_start_preauth, sm, NULL);
	eloop_cancel_timeout(wpa_sm_rekey_ptk, sm, NULL);
	os_free(sm->assoc_wpa_ie);
	os_free(sm->ap_wpa_ie);
	os_free(sm->ap_rsn_ie);
	wpa_sm_drop_sa(sm);
	os_free(sm->ctx);
#ifdef CONFIG_IEEE80211R
	os_free(sm->assoc_resp_ies);
#endif /* CONFIG_IEEE80211R */
#ifdef CONFIG_TESTING_OPTIONS
	wpabuf_free(sm->test_assoc_ie);
#endif /* CONFIG_TESTING_OPTIONS */
#ifdef CONFIG_FILS_SK_PFS
	crypto_ecdh_deinit(sm->fils_ecdh);
#endif /* CONFIG_FILS_SK_PFS */
#ifdef CONFIG_FILS
	wpabuf_free(sm->fils_ft_ies);
#endif /* CONFIG_FILS */
#ifdef CONFIG_OWE
	crypto_ecdh_deinit(sm->owe_ecdh);
#endif /* CONFIG_OWE */
#ifdef CONFIG_DPP2
	wpabuf_clear_free(sm->dpp_z);
#endif /* CONFIG_DPP2 */
	os_free(sm);
}
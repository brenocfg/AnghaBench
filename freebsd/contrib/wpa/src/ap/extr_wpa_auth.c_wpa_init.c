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
typedef  struct wpa_auth_config {int /*<<< orphan*/  ip_addr_start; int /*<<< orphan*/  ip_addr_end; } const wpa_auth_config ;
typedef  struct wpa_auth_config u8 ;
struct TYPE_2__ {scalar_t__ wpa_group_rekey; scalar_t__ wpa_gmk_rekey; } ;
struct wpa_authenticator {int /*<<< orphan*/  ip_pool; TYPE_1__ conf; int /*<<< orphan*/ * pmksa; struct wpa_authenticator* wpa_ie; struct wpa_authenticator* group; int /*<<< orphan*/ * ft_pmk_cache; void* cb_ctx; struct wpa_auth_callbacks const* cb; TYPE_1__* addr; } ;
struct wpa_auth_callbacks {int dummy; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 int WPA_GET_BE32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitfield_alloc (int) ; 
 int /*<<< orphan*/  eloop_register_timeout (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wpa_authenticator*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_free (struct wpa_authenticator*) ; 
 int /*<<< orphan*/  os_memcpy (TYPE_1__*,struct wpa_auth_config const*,int) ; 
 struct wpa_authenticator* os_zalloc (int) ; 
 int /*<<< orphan*/  pmksa_cache_auth_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pmksa_cache_auth_init (int /*<<< orphan*/ ,struct wpa_authenticator*) ; 
 scalar_t__ wpa_auth_gen_wpa_ie (struct wpa_authenticator*) ; 
 int /*<<< orphan*/  wpa_auth_pmksa_free_cb ; 
 int /*<<< orphan*/ * wpa_ft_pmk_cache_init () ; 
 struct wpa_authenticator* wpa_group_init (struct wpa_authenticator*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wpa_rekey_gmk ; 
 int /*<<< orphan*/  wpa_rekey_gtk ; 

struct wpa_authenticator * wpa_init(const u8 *addr,
				    struct wpa_auth_config *conf,
				    const struct wpa_auth_callbacks *cb,
				    void *cb_ctx)
{
	struct wpa_authenticator *wpa_auth;

	wpa_auth = os_zalloc(sizeof(struct wpa_authenticator));
	if (wpa_auth == NULL)
		return NULL;
	os_memcpy(wpa_auth->addr, addr, ETH_ALEN);
	os_memcpy(&wpa_auth->conf, conf, sizeof(*conf));
	wpa_auth->cb = cb;
	wpa_auth->cb_ctx = cb_ctx;

	if (wpa_auth_gen_wpa_ie(wpa_auth)) {
		wpa_printf(MSG_ERROR, "Could not generate WPA IE.");
		os_free(wpa_auth);
		return NULL;
	}

	wpa_auth->group = wpa_group_init(wpa_auth, 0, 1);
	if (wpa_auth->group == NULL) {
		os_free(wpa_auth->wpa_ie);
		os_free(wpa_auth);
		return NULL;
	}

	wpa_auth->pmksa = pmksa_cache_auth_init(wpa_auth_pmksa_free_cb,
						wpa_auth);
	if (wpa_auth->pmksa == NULL) {
		wpa_printf(MSG_ERROR, "PMKSA cache initialization failed.");
		os_free(wpa_auth->group);
		os_free(wpa_auth->wpa_ie);
		os_free(wpa_auth);
		return NULL;
	}

#ifdef CONFIG_IEEE80211R_AP
	wpa_auth->ft_pmk_cache = wpa_ft_pmk_cache_init();
	if (wpa_auth->ft_pmk_cache == NULL) {
		wpa_printf(MSG_ERROR, "FT PMK cache initialization failed.");
		os_free(wpa_auth->group);
		os_free(wpa_auth->wpa_ie);
		pmksa_cache_auth_deinit(wpa_auth->pmksa);
		os_free(wpa_auth);
		return NULL;
	}
#endif /* CONFIG_IEEE80211R_AP */

	if (wpa_auth->conf.wpa_gmk_rekey) {
		eloop_register_timeout(wpa_auth->conf.wpa_gmk_rekey, 0,
				       wpa_rekey_gmk, wpa_auth, NULL);
	}

	if (wpa_auth->conf.wpa_group_rekey) {
		eloop_register_timeout(wpa_auth->conf.wpa_group_rekey, 0,
				       wpa_rekey_gtk, wpa_auth, NULL);
	}

#ifdef CONFIG_P2P
	if (WPA_GET_BE32(conf->ip_addr_start)) {
		int count = WPA_GET_BE32(conf->ip_addr_end) -
			WPA_GET_BE32(conf->ip_addr_start) + 1;
		if (count > 1000)
			count = 1000;
		if (count > 0)
			wpa_auth->ip_pool = bitfield_alloc(count);
	}
#endif /* CONFIG_P2P */

	return wpa_auth;
}